#ifndef PROVINCELISTMODEL_H
#define PROVINCELISTMODEL_H

#include <QAbstractListModel>
#include <QQuickItem>

class ProvinceListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum PROVINCE_ROLE {
        ID_ROLE,
        DIAPLAY_NAME_ROLE
    };

    explicit ProvinceListModel(QObject *parent = 0);

    // QAbstractItemModel interface
public:
    //QModelIndex index(int row, int column, QModelIndex &parent);
    int rowCount(QModelIndex &parent);
    QVariant data(QModelIndex &index, int role);
signals:

public slots:
};

#endif // PROVINCELISTMODEL_H
