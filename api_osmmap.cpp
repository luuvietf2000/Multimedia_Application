#include "api_osmmap.h"
#include <QNetworkReply>
API_OSMMap::API_OSMMap(QObject *parent)
    : QObject{parent}
{
    manager = new QNetworkAccessManager();
}


API_OSMMap::~API_OSMMap()
{
    manager->deleteLater();
}

void API_OSMMap::requestSearchLocation(const QString &name, function<void (QByteArray &)> func)
{
    QUrl host("https://nominatim.openstreetmap.org/search?");
    QMap<QString, QString> map;
    map.insert("q", name);
    map.insert("format", "json");
    map.insert("polygon_geojson", "1");
    map.insert("limit", "20");
    request(host, map, func);
}

void API_OSMMap::requestSearchName(double longitude, double latitude, function<void (QByteArray &)> func)
{
    QUrl host("https://nominatim.openstreetmap.org/reverse?");
    QMap<QString, QString> map;
    map.insert("format", "json");
    map.insert("lon", QString::number(longitude));
    map.insert("lat", QString::number(latitude));
    request(host, map, func);
}

void API_OSMMap::requestRoute(double longitude_x, double latitude_x, double longitude_y, double latitude_y, QString driving, QString overview, QString geometries, function<void (QByteArray &)> func)
{
    QString path = QString("http://router.project-osrm.org/route/v1/%1/%2,%3;%4,%5?")
        .arg(driving, QString::number(longitude_x), QString::number(latitude_x), QString::number(longitude_y), QString::number(latitude_y));
    QUrl host(path);
    QMap<QString, QString> map;
    map.insert("overview", overview);
    map.insert("geometries", geometries);
    request(host, map, func);
}

void API_OSMMap::request(QUrl &host, QMap<QString, QString> &map, function<void (QByteArray &)> func)
{
    QUrlQuery query = getQuery(map);
    host.setQuery(query);
    QNetworkRequest request = getNetWorkRequest(host);
    QNetworkReply * reply = manager->get(request);
    connect(reply, &QNetworkReply::finished, this, [=](){
        QByteArray value = reply->readAll();
        reply->deleteLater();
        func(value);
    });
}

QNetworkRequest API_OSMMap::getNetWorkRequest(QUrl &host)
{
    QNetworkRequest request;
    request.setUrl(host);
    request.setRawHeader("User-Agent", "Display_app/0.1");
    return request;
}

QUrlQuery API_OSMMap::getQuery(QMap<QString, QString> &map)
{
    QUrlQuery query;
    for(auto i = map.begin(); i != map.end(); i++){
        query.addQueryItem(i.key(), i.value());
    }
    return query;
}


