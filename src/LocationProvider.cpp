
#include <QtDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include <QTextCodec>

#include "LocationProvider.h"

LocationProvider::LocationProvider(QObject *parent) :
    QObject(parent)
{
    m_network = new QNetworkAccessManager(this);
    m_provinceReply = 0;
    m_cityReply = 0;
    m_townReply = 0;
}

//省
//http://cdn.weather.hao.360.cn/sed_api_area_query.php?grade=province&_jsonp=loadProvince
void LocationProvider::startFetchProvince()
{
    qDebug()<<"===== start fetch province";

    if (m_provinceReply) {
        m_provinceReply->disconnect();
        m_provinceReply->abort();
        m_provinceReply->deleteLater();
    }
    QUrl url (QString("http://cdn.weather.hao.360.cn/sed_api_area_query.php?grade=province&_jsonp=loadProvince"));
    m_provinceReply = m_network->get(QNetworkRequest(url));
    connect(m_provinceReply, SIGNAL(finished()),this, SLOT(slotFinishFetchProvince()));
}

//市
//http://cdn.weather.hao.360.cn/sed_api_area_query.php?grade=city&_jsonp=loadCity&code=08
void LocationProvider::startFetchCity(const QString &id, const QString &displayName)
{
    qDebug()<<"===== start fetch city for code "<<id<<" " <<displayName;

    m_cityDisplayName = displayName;

    if (m_cityReply) {
        m_cityReply->disconnect();
        m_cityReply->abort();
        m_cityReply->deleteLater();
    }
    QUrl url(QString("http://cdn.weather.hao.360.cn/sed_api_area_query.php?grade=city&_jsonp=loadCity&code=%1").arg(id));
    m_cityReply = m_network->get(QNetworkRequest(url));
    connect(m_cityReply, SIGNAL(finished()),this, SLOT(slotFinishFetchCity()));
}

//县
//http://cdn.weather.hao.360.cn/sed_api_area_query.php?grade=town&_jsonp=loadTown&code=0804
void LocationProvider::startFetchTown(const QString &id, const QString &displayName)
{
    qDebug()<<"===== start fetch town for code "<<id<<" " <<displayName;

    m_townDisplayName = displayName;

    if (m_townReply) {
        m_townReply->disconnect();
        m_townReply->abort();
        m_townReply->deleteLater();
    }
    QUrl url(QString("http://cdn.weather.hao.360.cn/sed_api_area_query.php?grade=town&_jsonp=loadTown&code=%1").arg(id));
    m_townReply = m_network->get(QNetworkRequest(url));
    connect(m_townReply, SIGNAL(finished()),this, SLOT(slotFinishFetchTown()));
}

QList<QObject *> LocationProvider::getProvinceList() const
{
    //return m_provinceList;
    QList<QObject *> objs;
    foreach (LocationResult *node, m_provinceList) {
        objs.append(node);
    }
    /*for(int i=0;i<20;i++) {
        LocationResult *node = LocationResult::create(QString(i), QString("this is item %1").arg(i));
        objs.append(node);
    }*/
    return objs;
}

QList<QObject *> LocationProvider::getCityList() const
{
    QList<QObject *> objs;
    foreach (LocationResult *node, m_cityList) {
        objs.append(node);
    }
    return objs;
}

QList<QObject *> LocationProvider::getTownList() const
{
    QList<QObject *> objs;
    foreach (LocationResult *node, m_townList) {
        objs.append(node);
    }
    return objs;
}

void LocationProvider::slotFinishFetchProvince()
{
    qDebug()<<"===== slotFinishFetchProvince";

    m_provinceList.clear();

    if (m_provinceReply->error() != QNetworkReply::NoError) {
        m_provinceReply->deleteLater();
        m_provinceReply = 0;
        emit fetchProvinceFailed();
        return;
    }

    QByteArray array = m_provinceReply->readAll();

    array = array.mid(array.indexOf("(")+1);
    array = array.mid(0, array.indexOf(")"));

    m_provinceReply->deleteLater();
    m_provinceReply = 0;

    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(array, &error);
    if (error.error == QJsonParseError::NoError) {
        if (doc.isArray()) {
            qDebug() <<"=== paser json array";
            QJsonArray jsonArray = doc.array();

            for (int i=0;i<jsonArray.size();i++) {
                QJsonValue value = jsonArray.at(i);
                if (value.isArray()) {
                    //qDebug()<<"paser sub item"<<value.toVariant();//value.toArray();
                    QJsonArray ar = value.toArray();

                    LocationResult *obj = LocationResult::create(ar.at(1).toString(), ar.at(0).toString(), this);
                    m_provinceList.append(obj);
                }
            }
        }
    } else {
        qDebug() <<"===error  paser json array";
        emit fetchProvinceFailed();
        return;
    }

    qDebug()<<"===== finish slotFinishFetchProvince";

    emit fetchProvinceSucceed();
}

void LocationProvider::slotFinishFetchCity()
{
    qDebug()<<"===== slotFinishFetch city";

    m_cityList.clear();

    if (m_cityReply->error() != QNetworkReply::NoError) {
        m_cityReply->deleteLater();
        m_cityReply = 0;
        emit fetchCityFailed();
        return;
    }

    QByteArray array = m_cityReply->readAll();

    array = array.mid(array.indexOf("(")+1);
    array = array.mid(0, array.indexOf(")"));

    m_cityReply->deleteLater();
    m_cityReply = 0;

    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(array, &error);
    if (error.error == QJsonParseError::NoError) {
        if (doc.isArray()) {
            qDebug() <<"=== paser json array";
            QJsonArray jsonArray = doc.array();

            for (int i=0;i<jsonArray.size();i++) {
                QJsonValue value = jsonArray.at(i);
                if (value.isArray()) {
                    //qDebug()<<"paser sub item"<<value.toVariant();//value.toArray();
                    QJsonArray ar = value.toArray();

                    LocationResult *obj = LocationResult::create(ar.at(1).toString(), ar.at(0).toString(), this);
                    m_cityList.append(obj);
                }
            }
        }
    } else {
        qDebug() <<"===error  paser json array";
        emit fetchCityFailed();
        return;
    }

    qDebug()<<"===== finish slotFinishFetch city";

    emit fetchCitySucceed();
}

void LocationProvider::slotFinishFetchTown()
{
    qDebug()<<"===== slotFinishFetch town";

    m_townList.clear();

    if (m_townReply->error() != QNetworkReply::NoError) {
        m_townReply->deleteLater();
        m_townReply = 0;
        emit fetchTownFailed();
        return;
    }

    QByteArray array = m_townReply->readAll();

    array = array.mid(array.indexOf("(")+1);
    array = array.mid(0, array.indexOf(")"));

    m_townReply->deleteLater();
    m_townReply = 0;

    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(array, &error);
    if (error.error == QJsonParseError::NoError) {
        if (doc.isArray()) {
            qDebug() <<"=== paser json array";
            QJsonArray jsonArray = doc.array();

            for (int i=0;i<jsonArray.size();i++) {
                QJsonValue value = jsonArray.at(i);
                if (value.isArray()) {
                    //qDebug()<<"paser sub item"<<value.toVariant();//value.toArray();
                    QJsonArray ar = value.toArray();

                    LocationResult *obj = LocationResult::create(ar.at(1).toString(), ar.at(0).toString(), this);
                    m_townList.append(obj);
                }
            }
        }
    } else {
        qDebug() <<"===error  paser json array";
        emit fetchTownFailed();
        return;
    }

    qDebug()<<"===== finish slotFinishFetch town";

    emit fetchTownSucceed();
}


