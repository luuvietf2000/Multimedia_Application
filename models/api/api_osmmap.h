#ifndef API_OSMMAP_H
#define API_OSMMAP_H

#include <QObject>
#include <functional>
#include <QByteArray>
#include <QUrlQuery>
#include <QNetworkAccessManager>
using std::function;

class API_OSMMap : public QObject
{
    Q_OBJECT
public:
    explicit API_OSMMap(QObject *parent = nullptr);
    ~API_OSMMap();
    void requestSearchLocation(const QString &name, function <void(QByteArray&)> func);
    void requestSearchName(double longitude, double latitude, function <void(QByteArray&)> func);
    void requestRoute(double longitude_x, double latitude_x, double longitude_y, double latitude_y, QString driving, QString overview, QString geometries, function <void(QByteArray&)> func);
private:
    void request(QUrl &host, QMap<QString, QString> &map, function<void(QByteArray&)> func);
    QNetworkRequest getNetWorkRequest(QUrl &host);
    QNetworkAccessManager *manager;
    QUrlQuery getQuery(QMap<QString, QString> &map);
signals:
};

#endif // API_OSMMAP_H
