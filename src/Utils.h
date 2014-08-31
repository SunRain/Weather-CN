#ifndef UTILS_H
#define UTILS_H


#include <QString>
#include <QJsonObject>
#include <QJsonArray>

class Utils
{
public:
    Utils();
    static long getLong(const QString& key, const QJsonObject& obj);
    static QJsonObject getSubJsonObject(const QString& key, const QJsonObject& obj);

    static QJsonArray getJsonArray(const QString& key, const QJsonObject& obj);
};

#endif // UTILS_H
