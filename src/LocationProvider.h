#ifndef LOCATIONPROVIDER_H
#define LOCATIONPROVIDER_H

#include <QObject>

#include <QList>
#include <QNetworkAccessManager>
#include <QNetworkReply>

static const char* QUERY_URL = "http://cdn.weather.hao.360.cn/sed_api_area_query.php?";

//省
//http://cdn.weather.hao.360.cn/sed_api_area_query.php?grade=province&_jsonp=loadProvince
//市
//http://cdn.weather.hao.360.cn/sed_api_area_query.php?grade=city&_jsonp=loadCity&code=08
//县
//http://cdn.weather.hao.360.cn/sed_api_area_query.php?grade=town&_jsonp=loadTown&code=0804

//天气查询接口
//http://tq.360.cn/api/weatherquery/query?code=101190501&app=tq360&_jsonp=renderData

class LocationResult : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString id READ id CONSTANT)
    Q_PROPERTY(QString displayText READ displayText CONSTANT)

public:
    explicit LocationResult (QObject *parent = 0)
        : QObject(parent) {}

    static LocationResult *create(const QString& id, const QString& displayText, QObject *parent = 0){
        LocationResult *node = new LocationResult(parent);
        node->m_id = id;
        node->m_displayText = displayText;
        return node;
    }

    QString id() const              {return m_id;}
    QString displayText() const     {return m_displayText;}
private:
    QString m_id;
    QString m_displayText;
};

class LocationProvider : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<QObject *> getProvinceList READ getProvinceList)
    Q_PROPERTY(QList<QObject *> getCityList READ getCityList)
    Q_PROPERTY(QList<QObject *> getTownList READ getTownList)
public:
    explicit LocationProvider(QObject *parent = 0);


    Q_INVOKABLE void startFetchProvince();
    Q_INVOKABLE void startFetchCity(const QString& id, const QString& displayName);
    Q_INVOKABLE void startFetchTown(const QString& id, const QString& displayName);

    //Q_INVOKABLE void setCityId(const QString& id);

    QList<QObject *> getProvinceList() const;
    QList<QObject *> getCityList() const;
    QList<QObject *> getTownList() const;

signals:
    void fetchProvinceSucceed();
    void fetchProvinceFailed();

    void fetchCitySucceed();
    void fetchCityFailed();

    void fetchTownSucceed();
    void fetchTownFailed();

public slots:
    void slotFinishFetchProvince();
    void slotFinishFetchCity();
    void slotFinishFetchTown();

private:
    QString m_cityDisplayName;
    QString m_townDisplayName;

    QString m_cityId;

    QList<LocationResult *> m_provinceList;
    QList<LocationResult *> m_cityList;
    QList<LocationResult *> m_townList;

    QNetworkAccessManager *m_network;
    QNetworkReply *m_provinceReply;
    QNetworkReply *m_cityReply;
    QNetworkReply *m_townReply;
};

#endif // LOCATIONPROVIDER_H
