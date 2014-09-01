#ifndef WEATHERINFO_H
#define WEATHERINFO_H

#include <QString>
#include <QObject>

#include "LocationProvider.h"

class CurrentWeatherModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString dataUptime READ dataUptime CONSTANT)
    Q_PROPERTY(QString date READ date CONSTANT)
    Q_PROPERTY(QString humidity READ humidity CONSTANT)
    Q_PROPERTY(QString direct READ direct CONSTANT)
    Q_PROPERTY(QString power READ power CONSTANT)
    Q_PROPERTY(QString temperature READ temperature CONSTANT)
    Q_PROPERTY(QString info READ info CONSTANT)
    Q_PROPERTY(QString img READ img CONSTANT)
public:
    explicit CurrentWeatherModel(QObject *parent = 0):QObject(parent) {}
    static CurrentWeatherModel *create(const QString& dataUptime,
                                       const QString& date, const QString& humidity, const QString& direct,
                                       const QString& power, const QString& temperature,
                                       const QString& info, const QString& img,
                                       QObject *parent = 0);

    QString dataUptime() const      {return m_dataUptime;}
    QString date() const         {return m_date;}
    QString humidity() const     {return m_humidity;}
    QString direct() const       {return m_direct;}
    QString power() const        {return m_power;}
    QString temperature() const  {return m_temperature;}
    QString info() const         {return m_info;}
    QString img() const          {return m_img;}

private:
    QString m_dataUptime; //更新时间戳
    QString m_date; //时间
    QString m_humidity; //湿度
    QString m_direct; //风向
    QString m_power; //风力
    QString m_temperature; //当前温度
    QString m_info; //当前天气情况
    QString m_img; //天气图标
};

class WeatherObjectModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString typeSun READ typeSun CONSTANT)
    Q_PROPERTY(QString typeMoon READ typeMoon CONSTANT)
    Q_PROPERTY(QString date READ date CONSTANT)
    Q_PROPERTY(QString wcSun READ wcSun CONSTANT)
    Q_PROPERTY(QString wcMoon READ wcMoon CONSTANT)
    Q_PROPERTY(QString tempH READ tempH CONSTANT)
    Q_PROPERTY(QString tempL READ tempL CONSTANT)
    Q_PROPERTY(QString windSun READ windSun CONSTANT)
    Q_PROPERTY(QString windMoon READ windMoon CONSTANT)
    Q_PROPERTY(QString windPowerSun READ windPowerSun CONSTANT)
    Q_PROPERTY(QString windPowerMoon READ windPowerMoon CONSTANT)
public:
    explicit WeatherObjectModel(QObject *parent = 0):QObject(parent) {}
    static WeatherObjectModel *create(const QString& typeSun, const QString &typeMoon,
                                      const QString& date,
                                      const QString& wcSun, const QString& wcMoon,
                                      const QString& tempH, const QString& tempL,
                                      const QString& windSun, const QString& windMoon,
                                      const QString& windPowerSun, const QString& windPowerMoon,
                                      QObject *parent =0);

    QString typeSun() const        {        return m_typeSun;      }
    QString typeMoon() const       {        return m_typeMoon;     }
    QString date() const           {        return m_date;         }
    QString wcSun() const          {        return m_wcSun;        }
    QString wcMoon() const         {        return m_wcMoon;       }
    QString tempH() const          {        return m_tempH;        }
    QString tempL() const          {        return m_tempL;        }
    QString windSun() const        {        return m_windSun;      }
    QString windMoon() const       {        return m_windMoon;     }
    QString windPowerSun() const   {        return m_windPowerSun; }
    QString windPowerMoon() const  {        return m_windPowerMoon;}

private:
    //sun天气类型
    QString m_typeSun;
    //moon天气类型
    QString m_typeMoon;
    //时间
    QString m_date;
    //sun天气
    QString m_wcSun;
    //moon天气
    QString m_wcMoon;
    //最高温度
    QString m_tempH;
    //最低温度
    QString m_tempL;
    //sun风向
    QString m_windSun;
    //moon风向
    QString m_windMoon;
    //sun风力
    QString m_windPowerSun;
    //moon风力
    QString m_windPowerMoon;
};

//TODO: 暂时不使用这个类
class  LifeInfoModel : public QObject
{
    Q_OBJECT
public:
    explicit LifeInfoModel(QObject *parent = 0) : QObject(parent) {}



private:
    QString m_kongtiao; //空调
    QString m_yundong; //运动
    QString m_ziwaixian; //紫外线
    QString m_ganmao; //感冒
    QString m_xiche; //洗车
    QString m_wuran; //污染
    QString m_chuanyi; //穿衣
};

//TODO: 暂时不使用这个类
class PM25Model : public QObject
{
    Q_OBJECT
public:
    explicit PM25Model(QObject *parent = 0) : QObject(parent) {}

private:
    QString m_qualityStr;
    int m_aqi;
    int m_pm25;
    QString m_advice;
};

class WeatherModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(long time READ time WRITE setTime)
    //Q_PROPERTY(QList<QObject*> locationList READ locationList)
    Q_PROPERTY(QList<QObject*> weatherObjectList READ weatherObjectList)
    Q_PROPERTY(QObject* currentWeatherModel READ currentWeatherModel)
    //Q_PROPERTY(int pm25 READ pm25)

public:
    explicit WeatherModel(QObject *parent = 0) : QObject(parent) {}

    long time() const                                                  {return m_time;}
    void setTime(long time)                                            {m_time = time;}

    //QList<QObject *> locationList() const                       {return m_locationList;}
    //void setLocationList(const QList<LocationResult *> &locationList)  {m_locationList = locationList;  }

    QList<QObject *> weatherObjectList() const;
    void setWeatherObjectList(const QList<WeatherObjectModel *> &weatherObjectList);

    QObject *currentWeatherModel() const;
    void setCurrentWeatherModel(CurrentWeatherModel *currentWeatherModel);

    //int pm25() const                                                   {return m_pm25;}
    //void setPm25(int pm25)                                             {m_pm25 = pm25;}

private:
    long m_time;
    //QList<LocationResult *> m_locationList;
    QList<WeatherObjectModel *> m_weatherObjectList;
    CurrentWeatherModel *m_currentWeatherModel;
    int m_pm25;
};


class WeatherInfo :  public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString city READ city CONSTANT)
    Q_PROPERTY(QString date READ date CONSTANT)
    Q_PROPERTY(QString tempCurrent READ tempCurrent CONSTANT)
    Q_PROPERTY(QString tempHigh READ tempHigh CONSTANT)
    Q_PROPERTY(QString tempLow READ tempLow CONSTANT)
    Q_PROPERTY(QString tempUnit READ tempUnit CONSTANT)
    Q_PROPERTY(QString weatherConditionStr READ weatherConditionStr CONSTANT)
    Q_PROPERTY(QString weatherConditionCode READ weatherConditionCode CONSTANT)
    Q_PROPERTY(QString windSpeed READ windSpeed CONSTANT)
    Q_PROPERTY(QString windSpeedUnit READ windSpeedUnit CONSTANT)
    Q_PROPERTY(QString humidity READ humidity CONSTANT)
    Q_PROPERTY(QString syncTimestamp READ syncTimestamp CONSTANT)
    Q_PROPERTY(QString PM2Dot5Data READ PM2Dot5Data CONSTANT)
    Q_PROPERTY(QString AQIData READ AQIData CONSTANT)
    Q_PROPERTY(QString sunRiseTime READ sunRiseTime CONSTANT)
    Q_PROPERTY(QString sunSetTime READ sunSetTime CONSTANT)

public:
    explicit WeatherInfo(QObject *parent = 0);
    static WeatherInfo *creat(const QString& city, const QString& date,
                              const QString& tempCurrent, const QString& tempHigh, const QString& tempLow, const QString& tempUnit,
                              const QString& weatherConditionStr, const QString& weatherConditionCode,
                              const QString& windSpeed, const QString& windSpeedUnit,
                              const QString& humidity,
                              const QString& syncTimestamp,
                              const QString& PM2Dot5Data, const QString& AQIData,
                              const QString& sunRiseTime, const QString& sunSetTime,
                              QObject *parent = 0);

    QString city() const                  {return m_city;}
    QString date() const                  {return m_date;}
    QString tempCurrent() const           {return m_temperature;}
    QString tempHigh() const              {return m_temphigh;}
    QString tempLow() const               {return m_templow;}
    QString tempUnit() const              {return m_tempUnit;}
    QString weatherConditionStr() const   {return m_condition;}
    QString weatherConditionCode() const  {return m_conditionCode;}
    QString windSpeed() const             {return m_windSpeed;}
    QString windDirection() const         {return m_windDirection;}
    QString windSpeedUnit() const         {return m_windSpeedUnit;}
    QString humidity() const              {return m_humidity;}
    QString syncTimestamp() const         {return m_synctimestamp;}
    QString PM2Dot5Data() const           {return m_PM2Dot5Data;}
    QString AQIData() const               {return m_AQIData;}
    QString sunRiseTime() const           {return m_sunrise;}
    QString sunSetTime() const            {return m_sunset;}
private:
    QString m_city;
    QString m_date; // 天气数据的日期
    QString m_temperature; // 当前温度
    QString m_temphigh; // 最高温度
    QString m_templow; // 最低温度
    QString m_tempUnit; // 温度格式==>摄氏或者华氏
    QString m_condition; // 天气情况=>晴/阴之类
    QString m_conditionCode; //天气对应的图标
    QString m_windSpeed; // 风力
    QString m_windDirection; // 风向
    QString m_windSpeedUnit; // 风速单位,如 km/h
    QString m_humidity; // 湿度
    QString m_synctimestamp; // 同步时间
    QString m_PM2Dot5Data; // PM2.5
    QString m_AQIData; // AQI(空气质量指数)
    QString m_sunrise;
    QString m_sunset;
    
};


#endif // WEATHERINFO_H
