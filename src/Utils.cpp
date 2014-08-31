#include "Utils.h"

#include <QJsonValue>
#include <QJsonArray>

Utils::Utils()
{
}

long Utils::getLong(const QString &key, const QJsonObject &obj)
{
    if(obj.isEmpty() || key.isEmpty()) {
        return -1;
    }
    if (obj.contains(key)) {
        QJsonValue value = obj.value(key);
        if (value.isDouble() || value.isString()) {
            return value.toString().toLong();
        }
    }
    return -1;
}

QJsonObject Utils::getSubJsonObject(const QString &key, const QJsonObject &obj)
{
    QJsonObject o;
    if (obj.contains(key)) {
        QJsonValue value = obj.value(key);
        if (value.isObject()) {
            o = value.toObject();
        }
    }
    return o;
}

QJsonArray Utils::getJsonArray(const QString &key, const QJsonObject &obj)
{
    QJsonArray array;
    if (obj.contains(key)) {
        QJsonValue value = obj.value(key);
        if (value.isArray()) {
            array = value.toArray();
        }
    }
    return array;
}


