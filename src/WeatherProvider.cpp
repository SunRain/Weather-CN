
#include <QtDebug>
#include <QJsonArray>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonValue>
#include <QDir>
#include <QStandardPaths>

#include "WeatherProvider.h"
#include "Utils.h"

static const char *CONFIG_PATH = "SunRain/MagicWeather";
static const char *CONFIG_File = "config.json";

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
    if (m_replay) {
        m_replay->disconnect();
        m_replay->abort();
        m_replay->deleteLater();
    }
    
    QString id;
    if (cityID.isEmpty() || cityID.isNull()) {
        id = getLastWeatherCityId();
    } else {
        id = cityID;
        saveLastWeatherCityId(id);
    }
    
    qDebug()<<"===== start startFetchWeatherData" <<id;
    
    QUrl url (QString("http://tq.360.cn/api/weatherquery/query?code=%1&app=tq360&_jsonp=renderData").arg(id));
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
            CurrentWeatherModel::create(dataUptime, date, humidity, direct, power, temperature, info, img, this);
    m_weatherModel->setCurrentWeatherModel(model);
}

void WeatherProvider::parseToLifeInfoModel(const QJsonObject &obj)
{
    QString kongtiao, yundong, ziwaixian, ganmao, xiche, wuran, chuanyi;
    QJsonObject o = obj.value("info").toObject();

    QJsonArray array = o.value("kongtiao").toArray();
    kongtiao = array.at(0).toString() + "\n" + array.at(1).toString("N/A");
    
    array = o.value("yundong").toArray();
    yundong = array.at(0).toString() + "\n" + array.at(1).toString("N/A");
    
    array = o.value("ziwaixian").toArray();
    ziwaixian = array.at(0).toString() + "\n" + array.at(1).toString("N/A");
    
    array = o.value("ganmao").toArray();
    ganmao = array.at(0).toString() + "\n" + array.at(1).toString("N/A");
    
    array = o.value("xiche").toArray();
    xiche = array.at(0).toString() + "\n" + array.at(1).toString("N/A");
    
    array = o.value("wuran").toArray();
    wuran = array.at(0).toString() + "\n" + array.at(1).toString("N/A");
    
    array = o.value("chuanyi").toArray();
    chuanyi = array.at(0).toString() + "\n" + array.at(1).toString("N/A");
    
    qDebug()<<"parset LifeInfoMode to "
           <<kongtiao<<"  "
             <<yundong<<"  "
               <<ziwaixian<<"  "
                 <<ganmao<<"  "
                   <<xiche<<"  "
                     <<wuran<<"  "
                       <<chuanyi;
    
    LifeInfoModel *model = 
            LifeInfoModel::create(kongtiao,yundong,ziwaixian,ganmao,xiche,wuran,chuanyi,this);
    m_weatherModel->setLifeInfoModel(model);
}

void WeatherProvider::parseToPM25Model(const QJsonObject &obj)
{
    qDebug()<<"parset parseToPM25Model to " << obj.toVariantMap();
    
    QString quality,advice, aqi,pm25;
    
    quality = obj.value("quality").toString("N/A");
    advice = obj.value("advice").toString("N/A");
    aqi = obj.value("aqi").toString("N/A");
    pm25 = obj.value("pm25").toString("N/A");
    
    qDebug()<<"parset parseToPM25Model to "
           <<quality<<"  "
             <<advice<<"  "
               <<aqi<<"  "
                 <<pm25;
    
    PM25Model *model = PM25Model::create(quality, advice, aqi, pm25, this);
    m_weatherModel->setPM25Model(model);
}

void WeatherProvider::saveLastWeatherCityId(const QString &cityId)
{
    QDir dir (QStandardPaths::writableLocation(QStandardPaths::ConfigLocation));
    if (!dir.mkpath(QString(CONFIG_PATH))) {
        return;
    }
    if (!dir.cd(QString(CONFIG_PATH))) {
        return;
    }
    
    QString filePath = dir.absoluteFilePath(QString(CONFIG_File));
    
    qDebug()<<"========== save city ID "<<cityId<<"to file "<<filePath;

    QJsonObject obj;
    obj.insert("cityId", cityId);

    QJsonDocument doc (obj);
    QFile file (filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug()<<"======== write file fail";
        return;
    }

    file.write(doc.toJson(QJsonDocument::Compact));
    file.close();
}

QString WeatherProvider::getLastWeatherCityId()
{
    QDir dir (QStandardPaths::writableLocation(QStandardPaths::ConfigLocation));
    if (!dir.mkpath(QString(CONFIG_PATH))) {
        return QString();
    }
    if (!dir.cd(QString(CONFIG_PATH))) {
        return QString();
    }
    
    QString filePath = dir.absoluteFilePath(QString(CONFIG_File));
    
    QFile file (filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug()<<"======== read file fail";
        return QString();
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();

    QJsonObject obj = doc.object();
    QJsonValue value = obj.value("cityId");
    if (value.isUndefined()) {
        return QString();
    }
    return value.toString();
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
            //m_weatherModel->setTime(Utils::getLong("dataUptime", Utils::getSubJsonObject("realtime", jsonObject)));
            m_weatherModel->setTime(Utils::getSubJsonObject("realtime", jsonObject).value("time").toString());
            
            qDebug()<<"dataUptime is "<<m_weatherModel->time();
            
            //获取天气详情列表
            parseToWeaterObjList(Utils::getJsonArray("weather", jsonObject));
            //获取实时天气
            parseToCurrenWeatherModel(Utils::getSubJsonObject("realtime", jsonObject));
            
            parseToLifeInfoModel(Utils::getSubJsonObject("life", jsonObject));
            
            parseToPM25Model(Utils::getSubJsonObject("pm25", jsonObject));
            
            QJsonArray array = Utils::getJsonArray("area", jsonObject);
            QJsonValue value = array.at(array.size()-1);
            m_weatherModel->setAreaName(value.toArray().at(0).toString());
        }
    } else {
        qDebug() <<"===error  paser json array";
        emit fetchWeatherDataFailed();
        return;
    }

    qDebug()<<"===== finish slotFinishFetch city";

    emit fetchWeatherDataSucceed();
}
