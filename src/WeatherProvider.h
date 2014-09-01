#ifndef WEATHERPROVIDER_H
#define WEATHERPROVIDER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

#include "WeatherInfo.h"

class WeatherProvider : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QObject* weatherModel READ getWeatherModel)
public:
    explicit WeatherProvider(QObject *parent = 0);

    Q_INVOKABLE void startFetchWeatherData(const QString& cityID);
    QObject *getWeatherModel() const;

protected:
    QString getAQIString(int aqi);
    void parseToWeaterObjList(const QJsonArray& array);
    void parseToCurrenWeatherModel(const QJsonObject& obj);

signals:
    void fetchWeatherDataSucceed();
    void fetchWeatherDataFailed();
public slots:
    void slotFinishFetchWeatherData();

private:
    QNetworkAccessManager *m_network;
    QNetworkReply *m_replay;

    WeatherModel *m_weatherModel;
    QList<WeatherObjectModel *> m_WeatherObjectModelList;

};

#endif // WEATHERPROVIDER_H
