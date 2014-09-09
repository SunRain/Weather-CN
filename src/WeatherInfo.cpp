
#include "WeatherInfo.h"
/*
WeatherInfo::WeatherInfo(QObject *parent)
    : QObject(parent)
{

}


WeatherInfo *WeatherInfo::creat(const QString &city, const QString &date,
                                const QString &tempCurrent, const QString &tempHigh, const QString &tempLow, const QString &tempUnit,
                                const QString &weatherConditionStr, const QString &weatherConditionCode,
                                const QString &windSpeed, const QString &windSpeedUnit,
                                const QString &humidity,
                                const QString &syncTimestamp,
                                const QString &PM2Dot5Data, const QString &AQIData,
                                const QString &sunRiseTime, const QString &sunSetTime, QObject *parent)
{
    WeatherInfo *info = new WeatherInfo(parent);
    info->m_city = city;
    info->m_date = date;
    info->m_temperature = tempCurrent;
    info->m_temphigh = tempHigh;
    info->m_templow = tempLow;
    info->m_tempUnit = tempUnit;
    info->m_condition = weatherConditionStr;
    info->m_conditionCode = weatherConditionCode;
    info->m_windSpeed = windSpeed;
    info->m_windSpeedUnit = windSpeedUnit;
    info->m_humidity = humidity;
    info->m_synctimestamp = syncTimestamp;
    info->m_PM2Dot5Data = PM2Dot5Data;
    info->m_AQIData = AQIData;
    info->m_sunrise = sunRiseTime;
    info->m_sunset = sunSetTime;
    return info;
}
*/

CurrentWeatherModel *CurrentWeatherModel::create(const QString &dataUptime, const QString &date,
                                                const QString &humidity,
                                                const QString &direct, const QString &power,
                                                const QString &temperature,
                                                const QString &info, const QString &img, QObject *parent)
{
    CurrentWeatherModel *model = new CurrentWeatherModel(parent);
    model->m_dataUptime = dataUptime;
    model->m_date = date;
    model->m_humidity = humidity;
    model->m_direct = direct;
    model->m_power = power;
    model->m_temperature = temperature;
    model->m_info = info;
    model->m_img = img;
    return model;
}

WeatherObjectModel *WeatherObjectModel::create(const QString &typeSun, const QString &typeMoon,
                                               const QString &date,
                                               const QString &wcSun, const QString &wcMoon,
                                               const QString &tempH, const QString &tempL,
                                               const QString &windSun, const QString &windMoon,
                                               const QString &windPowerSun, const QString &windPowerMoon,
                                               QObject *parent)
{
    WeatherObjectModel *model = new WeatherObjectModel(parent);
    model->m_typeSun = typeSun;
    model->m_typeMoon = typeMoon;
    model->m_date = date;
    model->m_wcSun = wcSun;
    model->m_wcMoon = wcMoon;
    model->m_tempH = tempH;
    model->m_tempL = tempL;
    model->m_windSun = windSun;
    model->m_windMoon = windMoon;
    model->m_windPowerSun = windPowerSun;
    model->m_windPowerMoon = windPowerMoon;
    return model;
}



QList<QObject *> WeatherModel::weatherObjectList() const
{
    QList<QObject *> objs;
    foreach (WeatherObjectModel *node, m_weatherObjectList) {
        objs.append(node);
    }
    return objs;
}

void WeatherModel::setWeatherObjectList(const QList<WeatherObjectModel *> &weatherObjectList)
{
        m_weatherObjectList = weatherObjectList;
}

QObject *WeatherModel::currentWeatherModel() const
{
    QObject *obj = m_currentWeatherModel;
    return obj;
}

void WeatherModel::setCurrentWeatherModel(CurrentWeatherModel *currentWeatherModel)
{
    m_currentWeatherModel = currentWeatherModel;
}

QObject *WeatherModel::lifeInfoModel() const
{
    QObject *obj = m_lifeInfoModel;
    return obj;
}

void WeatherModel::setLifeInfoModel(LifeInfoModel *lifeInfoModel)
{
    m_lifeInfoModel = lifeInfoModel;
}

QObject *WeatherModel::getPM25Model() const
{
    QObject *obj = m_pm25Model;
    return obj;
}

void WeatherModel::setPM25Model(PM25Model *model)
{
    m_pm25Model = model;
}


LifeInfoModel *LifeInfoModel::create(const QString &kongtiao,
                                     const QString &yundong,
                                     const QString &ziwaixian, 
                                     const QString &ganmao, 
                                     const QString &xiche,
                                     const QString &wuran, 
                                     const QString &chuanyi,
                                     QObject *parent)
{
    LifeInfoModel *model = new LifeInfoModel(parent);
    model->m_kongtiao = kongtiao;
    model->m_yundong = yundong;
    model->m_ziwaixian = ziwaixian;
    model->m_ganmao = ganmao;
    model->m_xiche = xiche;
    model->m_wuran = wuran;
    model->m_chuanyi = chuanyi;
    return model;
}

PM25Model *PM25Model::create(const QString &quality, const QString &advice, const QString &aqi, const QString &pm25, QObject *parent)
{
    PM25Model *model = new PM25Model(parent);
    model->m_qualityStr = quality;
    model->m_advice = advice;
    model->m_aqi = aqi;
    model->m_pm25 = pm25;
    return model;
}
