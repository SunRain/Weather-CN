
#include <QtDebug>
#include <QJsonArray>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonValue>

#include "WeatherProvider.h"
#include "Utils.h"

WeatherProvider::WeatherProvider(QObject *parent) :
    QObject(parent)
{
    m_network = new QNetworkAccessManager(this);
    m_replay = 0;
    m_weatherModel = 0;
}

//天气查询接口
//http://tq.360.cn/api/weatherquery/query?code=101190501&app=tq360&_jsonp=renderData
void WeatherProvider::startFetchWeatherData(const QString &cityID)
{
    qDebug()<<"===== start startFetchWeatherData" <<cityID;

    if (m_replay) {
        m_replay->disconnect();
        m_replay->abort();
        m_replay->deleteLater();
    }
    QUrl url (QString("http://tq.360.cn/api/weatherquery/query?code=%1&app=tq360&_jsonp=renderData").arg(cityID));
    m_replay = m_network->get(QNetworkRequest(url));
    connect(m_replay, SIGNAL(finished()),this, SLOT(slotFinishFetchWeatherData()));
}

QObject *WeatherProvider::getWeatherModel() const
{
    QObject *o = m_weatherModel;
    return o;
    //return m_weatherModel;
}

QString WeatherProvider::getAQIString(int aqi)
{
    QString s;
    if (aqi >= 0 && aqi <= 50) {
        s = tr("aqi2to50");//tr("空气优");
    } else if (aqi > 50 && aqi <= 100) {
        s = tr("aqi50to100");//tr("空气良");
    } else if (aqi > 100 && aqi <= 150) {
        s = tr("aqi100to150");//tr("轻度污染");
    } else if (aqi > 150 && aqi <= 200) {
        s = tr("aqi150to200");//tr("中度污染");
    } else if (aqi > 200 && aqi <= 300) {
        s = tr("aqi200to300");//tr("重度污染");
    } else if (aqi > 300) {
        s = tr("aqi300to400");//tr("严重污染");
    }
    return s;
}

void WeatherProvider::parseToWeaterObjList(const QJsonArray &array)
{
    if (!m_WeatherObjectModelList.isEmpty()) {
        m_WeatherObjectModelList.clear();
    }

    qDebug()<<"start parseToWeaterObjList "<<array;

    //start parse
    QString typeSun,typeMoon,
            date,wcSun, wcMoon,
            tempH, tempL,
            windSun, windMoon,
            windPowerSun, windPowerMoon;

    for (int i=0; i<array.size();i++) {
        //WeatherObjectModel *model = new WeatherModel()
        QJsonValue value = array.at(i);
        QJsonObject obj = value.toObject();
        QJsonObject subObj = Utils::getSubJsonObject("info", obj);
        //白天天气信息
        QJsonArray sunArray = Utils::getJsonArray("day", subObj);\
        //夜间天气信息
        QJsonArray moonArray = Utils::getJsonArray("night", subObj);
        //设置时间
        date = obj.value("date").toString();
        //白天天气类型
        typeSun = sunArray.at(0).toString();
        //夜间天气类型
        typeMoon = moonArray.at(0).toString();
        //白天天气情况
        wcSun = sunArray.at(1).toString();
        //夜间天气情况
        wcMoon = moonArray.at(1).toString();
        //最高温度
        tempH = QString("%1℃").arg(sunArray.at(2).toString());
        //最低温度
        tempL = QString("%1℃").arg(moonArray.at(2).toString());
        //白天风向
        windSun = sunArray.at(3).toString();
        //夜间风向
        windMoon = moonArray.at(3).toString();
        //白天风力
        windPowerSun = sunArray.at(4).toString();
        //夜间风力
        windPowerMoon = moonArray.at(4).toString();

        qDebug()<<"parse to values ["
               <<typeSun<<","
               <<typeMoon<<","
               <<date<<","
               <<wcSun<<","
               <<wcMoon<<","
               <<tempH<<","
               <<tempL<<","
               <<windSun<<","
               <<windMoon<<","
               <<windPowerSun<<","
               <<windPowerMoon
               <<"]";

        WeatherObjectModel *model =
                WeatherObjectModel::create(typeSun,typeMoon,
                                           date,wcSun, wcMoon,
                                           tempH, tempL,
                                           windSun, windMoon,
                                           windPowerSun, windPowerMoon,
                                           this);
        m_WeatherObjectModelList.append(model);
    }

    m_weatherModel->setWeatherObjectList(m_WeatherObjectModelList);
}

void WeatherProvider::parseToCurrenWeatherModel(const QJsonObject &obj)
{
    qDebug()<<"start parseToCurrenWeatherModel "<<obj;

    QString dataUptime, date, humidity, direct,
            power, temperature,
            info, img;

    dataUptime = obj.value("dataUptime").toString();
    date = obj.value("date").toString();
    humidity = Utils::getSubJsonObject("weather", obj).value("humidity").toString();
    direct = Utils::getSubJsonObject("wind", obj).value("direct").toString();
    power = Utils::getSubJsonObject("wind", obj).value("power").toString();
    temperature = Utils::getSubJsonObject("weather", obj).value("temperature").toString();
    info = Utils::getSubJsonObject("weather", obj).value("info").toString();
    img = Utils::getSubJsonObject("weather", obj).value("img").toString();

    qDebug()<<"parse to value ["
            <<dataUptime<<","
            <<date<<","
            <<humidity<<","
            <<direct<<","
            <<power<<","
            <<temperature<<","
            <<info<<","
            <<img
            <<"]";

    CurrentWeatherModel *model =
            CurrentWeatherModel::create(dataUptime, date, humidity, direct, power, temperature, info, img);
    m_weatherModel->setCurrentWeatherModel(model);
}


void WeatherProvider::slotFinishFetchWeatherData()
{
    qDebug()<<"===== slotFinishFetchWeatherData";


    if (m_replay->error() != QNetworkReply::NoError) {
        m_replay->deleteLater();
        m_replay = 0;
        emit fetchWeatherDataFailed();
        return;
    }

    QByteArray array = m_replay->readAll();

    array = array.mid(array.indexOf("(")+1);
    array = array.mid(0, array.indexOf(")"));

    m_replay->deleteLater();
    m_replay = 0;

    qDebug() <<array;

    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(array, &error);
    if (error.error == QJsonParseError::NoError) {
        if (m_weatherModel != 0) {
            delete m_weatherModel;
            m_weatherModel = 0;
        }
        m_weatherModel = new WeatherModel(this);

        if (doc.isObject()) {
            qDebug() <<"=== paser json object";
            QJsonObject jsonObject = doc.object();

            //获取时间
            m_weatherModel->setTime(Utils::getLong("dataUptime", Utils::getSubJsonObject("realtime", jsonObject)));

            qDebug()<<"dataUptime is "<<m_weatherModel->time();

            //获取天气详情列表
            parseToWeaterObjList(Utils::getJsonArray("weather", jsonObject));
            //获取实时天气
            parseToCurrenWeatherModel(Utils::getSubJsonObject("realtime", jsonObject));
        }
    } else {
        qDebug() <<"===error  paser json array";
        emit fetchWeatherDataFailed();
        return;
    }

    qDebug()<<"===== finish slotFinishFetch city";

    emit fetchWeatherDataSucceed();
}
