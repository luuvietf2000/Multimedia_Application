#ifndef MODEL_MAP_H
#define MODEL_MAP_H

#include <QObject>
#include <QtQml>
#include <QGeoCoordinate>
#include <functional>
#include "api_osmmap.h"
#include <QMutex>
#include <QMutexLocker>
using std::function;
enum rolesMap{
    name = Qt::UserRole + 1,
    address,
    location,
    coordinate
};
enum itemRequest{
    toBox,
    fromBox
};
struct itemMap{
    QString name;
    QString address;
    QVariant location;
    QVariantList coordiante;
};
enum indexCoordinate{
    longitude,
    latitude
};
class Model_Map : public QAbstractListModel
{
    Q_OBJECT
    QML_NAMED_ELEMENT(MapParameter)
public:
    enum transportations{
        drving,
        cyling,
        walk
    };
    Q_ENUM(transportations);
    explicit Model_Map(QObject *parent = nullptr);
    ~Model_Map();

    Q_INVOKABLE void requestSearchItem(const int &item, const QString &keyword);
    Q_INVOKABLE void requestCheckLocation(const QGeoCoordinate &coordinate);
    Q_INVOKABLE void requestRoutingAllTransportation(const QGeoCoordinate &start, const QGeoCoordinate &stop);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    void requestRoutting(const QGeoCoordinate &toLocation, const QGeoCoordinate &fromLocation, const QString &transportation, const int &indexVaribleResult);
    QList<itemMap> filterDataLocation(QByteArray &data);
    QList<itemMap> filterDataName(QByteArray &data);
    API_OSMMap osm;
    QList<itemMap> listLocation;
    QGeoCoordinate isLocationValid(const QString &keyword);
    void requestSearch(const QString &keyword, const int &itemRequestSearch);
    void resetQAbstractListModel(const QList<itemMap> &list);
    void emitSignalSearch(int _itemRequest);
    //mutable QMutex roadParameterLocker;
    QVariantList m_listParameter;
    const QString codeSuccessfully = "Ok";
    QString convertDistance(double &distance);
    QString convertDuration(double &duration);
    void addNewKeyandValueInVariantMap(const QString &key, const QVariant &variant, QVariantList &list);
    void handleParameterRoutting(const QByteArray &byteArray, const int &indexVaribleResult);
    QGeoCoordinate ConvertArrayToCoordinate(const QJsonArray &array);
signals:
    void finishRequestCheckLocation(const QString &address, const QGeoCoordinate &coordinate);
    void listItemMapByToBoxSearchChanged(QAbstractListModel *model);
    void listItemMapByFromBoxSearchChanged(QAbstractListModel *model);
    void listParameterChanged(const QVariantList &object);
};

#endif // MODEL_MAP_H
