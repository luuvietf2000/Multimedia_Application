#include "model_map.h"

Model_Map::Model_Map(QObject *parent)
    : QAbstractListModel(parent)
{
    QVariant initVariant;
    for(int i = 0; i < 3; i++)
        m_listParameter.append(initVariant);
}

Model_Map::~Model_Map()
{
}

void Model_Map::requestSearchItem(const int &item, const QString &keyword)
{
    requestSearch(keyword, item);
}

void Model_Map::requestCheckLocation(const QGeoCoordinate &coordinate)
{
    osm.requestSearchName(coordinate.longitude(), coordinate.latitude(), [=](QByteArray value){
        QList<itemMap> newModel = filterDataName(value);
        itemMap map = newModel.first();
        finishRequestCheckLocation(map.address, coordinate);
    });
}

void Model_Map::requestRoutingAllTransportation(const QGeoCoordinate &start, const QGeoCoordinate &stop)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<transportations>();
    int limitApiTransportation = 1;
    //for(int i = 0; i < metaEnum.keyCount(); i++){
    for(int i = 0; i < limitApiTransportation; i++){
        QString transportation = metaEnum.key(i);
        requestRoutting(start, stop, transportation, i);
    }
}


void Model_Map::requestRoutting(const QGeoCoordinate &toLocation, const QGeoCoordinate &fromLocation, const QString &transportation, const int &indexVaribleResult)
{
    QString overview = "full";
    QString geometries = "geojson";
    osm.requestRoute(toLocation.longitude(), toLocation.latitude(), fromLocation.longitude(), fromLocation.latitude(),  transportation, overview, geometries, [=](QByteArray byte){
        handleParameterRoutting(byte, indexVaribleResult);
    });
}


int Model_Map::rowCount(const QModelIndex &parent) const
{
    return listLocation.count();
}

QVariant Model_Map::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || index.row() >= listLocation.count())
        return {};
    const itemMap &item = listLocation[index.row()];
    switch (role){
        case name: return item.name;
        case address: return item.address;
        case location: return item.location;
        case coordinate: return item.coordiante;
    }
        return {};
}

QHash<int, QByteArray> Model_Map::roleNames() const
{
    QHash<int, QByteArray> role;
    role[name] = "name";
    role[address] = "address";
    role[location] = "location";
    role[coordinate] = "coordinate";
    return role;
}

QList<itemMap> Model_Map::filterDataLocation(QByteArray &data)
{
    QJsonDocument json = QJsonDocument::fromJson(data);
    QList<itemMap> result;
    QJsonArray array = json.array();
    for(int i = 0; i < array.count(); i++){
        QJsonObject object = array[i].toObject();
        itemMap newItem;
        newItem.name = object["name"].toString();
        newItem.address = object["display_name"].toString();
        double lat = object["lat"].toString().toDouble();
        double lon = object["lon"].toString().toDouble();
        QGeoCoordinate coordinate(lat, lon);
        QVariant variant = QVariant::fromValue(coordinate);
        newItem.location = variant;
        QJsonArray arrayCoordinate = (object["geojson"].toObject())["coordinates"].toArray();
        for(int i = 0; i < arrayCoordinate.count(); i++){
            QJsonArray arrayPartTwo = arrayCoordinate[i].toArray();
            QVariantList listCoordinate;
            for(int j = 0; j < arrayPartTwo.count(); j++){
                QJsonArray arrayData = arrayPartTwo[j].toArray();
                QGeoCoordinate coor = ConvertArrayToCoordinate(arrayData);
                QVariant var = QVariant::fromValue(coor);
                listCoordinate.append(var);
            }
            QVariant variantList = QVariant::fromValue(listCoordinate);
            newItem.coordiante.append(variantList);
        }
        result.append(newItem);
    }
    return result;
}

QList<itemMap> Model_Map::filterDataName(QByteArray &data)
{
    QJsonDocument json = QJsonDocument::fromJson(data);
    QJsonObject object = json.object();
    QList<itemMap> result;
    itemMap newItem;
    newItem.name = object["name"].toString();
    newItem.address = object["display_name"].toString();
    double lat = object["lat"].toDouble();
    double lon = object["lon"].toDouble();
    QGeoCoordinate coordinate(lat, lon);
    QVariant variant = QVariant::fromValue(coordinate);
    newItem.location = variant;
    result.append(newItem);
    return result;
}

QGeoCoordinate Model_Map::isLocationValid(const QString &keyword)
{
    QGeoCoordinate coordinate;
    QStringList array = keyword.split(",");
    if(array.count() != 2) return coordinate;
    bool isLongitudeValid, isLatiudeValid;
    double longitude = array[0].toDouble(&isLongitudeValid);
    double latitude = array[1].toDouble(&isLatiudeValid);

    if(isLongitudeValid && isLatiudeValid){
        coordinate.setLongitude(longitude);
        coordinate.setLatitude(latitude);
        return coordinate;
    }
    return coordinate;
}

void Model_Map::requestSearch(const QString &keyword, const int &itemRequestSearch)
{
    QGeoCoordinate coordinate = isLocationValid(keyword);
    if(coordinate.isValid()){
        osm.requestSearchName(coordinate.longitude(), coordinate.latitude(), [=](QByteArray value){
            QList<itemMap> newModel = filterDataName(value);
            resetQAbstractListModel(newModel);
            emitSignalSearch(itemRequestSearch);
        });
    }
    else{
        osm.requestSearchLocation(keyword, [=](QByteArray value){
            QList<itemMap> newModel = filterDataLocation(value);
            resetQAbstractListModel(newModel);
            emitSignalSearch(itemRequestSearch);
        });
    }
}

void Model_Map::resetQAbstractListModel(const QList<itemMap> &list)
{
    beginResetModel();
    listLocation = list;
    endResetModel();
}

void Model_Map::emitSignalSearch(int _itemRequest)
{
    switch(_itemRequest){
        case toBox:
            emit listItemMapByToBoxSearchChanged(this);
            break;
        case fromBox:
            emit listItemMapByFromBoxSearchChanged(this);
            break;
    }
}

QString Model_Map::convertDistance(double &distance)
{
    bool isformatKm = distance >= 1000;
    int length = distance;
    QString result = QString::number((int) isformatKm ? length / 1000 : length) + (isformatKm ? " Km" : " m");
    return result;
}

QString Model_Map::convertDuration(double &duration)
{
    int length = duration;
    QString result;
    if(length > 3600){
        result += QString::number((int) length / 3600) + "Giờ";
        length %= 3600;
    }
    if(length > 60){
        result += QString::number((int) length / 60) + "Phút";
        length %= 60;
    }
    if(length > 0){
        result += QString:: number(length) + "Giây";
    }
    return result;
}

void Model_Map::addNewKeyandValueInVariantMap(const QString &key, const QVariant &variant, QVariantList &list)
{
    QVariantMap map;
    map["key"] = key;
    map["value"] = variant;
    list.append(map);
}

QGeoCoordinate Model_Map::ConvertArrayToCoordinate(const QJsonArray &array)
{
    double lon = array[longitude].toDouble();
    double lat = array[latitude].toDouble();
    return QGeoCoordinate(lat, lon);
}

void Model_Map::handleParameterRoutting(const QByteArray &byteArray, const int &indexVaribleResult)
{
    QJsonDocument json = QJsonDocument::fromJson(byteArray);
    QJsonObject objectData = json.object();
    QString result = objectData["code"].toString();
    if(result != codeSuccessfully)
        return;
    QJsonObject routes = objectData["routes"].toArray().first().toObject();
    double distance = routes["distance"].toDouble();
    double duration = routes["duration"].toDouble();
    QJsonObject geometry = routes["geometry"].toObject();
    QJsonArray coordinates = geometry["coordinates"].toArray();
    QVariantList listCoordinate;
    for(int i = 0; i < coordinates.count(); i++){
        QJsonArray array = coordinates[i].toArray();
        QGeoCoordinate coordinate = ConvertArrayToCoordinate(array);
        QVariant variant = QVariant::fromValue(coordinate);
        listCoordinate.append(variant);
    }
    QVariantMap map;
    QVariantList listHash;
    map["coordinate"] = QVariant::fromValue(listCoordinate);

    QVariant object = QVariant::fromValue(convertDistance(distance));
    addNewKeyandValueInVariantMap("Distance", object, listHash);
    object = QVariant::fromValue(convertDuration(duration));
    addNewKeyandValueInVariantMap("Duration", object, listHash);
    map["data"] = QVariant::fromValue(listHash);
    //QMutexLocker locker(&roadParameterLocker);
    m_listParameter[indexVaribleResult] = QVariant::fromValue(map);
    emit listParameterChanged(m_listParameter);
}

