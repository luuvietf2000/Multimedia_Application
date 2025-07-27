#include "API_ZingMp3.h"
#include <QFile>
#include <QJsonDocument>
#include <QCryptographicHash>
#include <QMessageAuthenticationCode>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QVariant>
#include <QJsonValue>
#include <QNetworkCookie>
#include <functional>
 #include <QUrlQuery>

API_ZingMp3::API_ZingMp3(QObject *parent)
    : QObject{parent}
{
    QFile file(":/Zing_mp3.txt");
    if(!file.open(QIODevice::ReadOnly)){
        return;
    }
    manger = new QNetworkAccessManager(this);
    this->URL = new QUrl();
    QByteArray byteArray = file.readAll();
    QJsonDocument json = QJsonDocument::fromJson(byteArray);
    this->API_key = json["Api_Key"].toString();
    QString host = json["Url"].toString();
    this->URL->setUrl(host);
    this->Secret_key = json["Secret_Key"].toString();
    this->Version = json["Version"].toString();
    this->path_Home = json["Path_Home"].toString();
    this->path_Search = json["Path_Search"].toString();
    this->path_Stream = json["Path_Stream"].toString();
    this->path_Info = json["Path_Info"].toString();
    file.close();
    this->Get_Cookie(this->Get_CTime(), [=](QString new_cookie){
        this->cookie = new_cookie;
    });
}

void API_ZingMp3::Get_Cookie(const qint64 &cTime, function<void(QString&)> func){
    if(!this->cookie.isEmpty()){
        func(this->cookie);
        return;
    }
    QNetworkRequest request;
    request.setUrl(*this->URL);
    QNetworkReply *reply = this->manger->get(request);
    connect(reply, &QNetworkReply::finished, this, [=]{
        this->handle_cookie(reply, func);
    });
}

void API_ZingMp3::Get_LinkStreamAudio(QString &id_Song, function<void(QByteArray&)>func)
{
    QMap<QString, QString> parameter;
    parameter["id"] = id_Song;
    qint64 cTime = this->Get_CTime();
    parameter["sig"] = this->Get_ParameterStream(cTime, id_Song, this->path_Stream);
    this->request_ZingMp3(cTime, this->path_Stream, parameter, [=](QNetworkReply *reply){
        QByteArray array;
        if(reply->error() == QNetworkReply::NoError){
            array = reply->readAll();
        }
        reply->deleteLater();
        func(array);
    });

}


QString API_ZingMp3::Get_Hash256(const QString &content){
    QByteArray hash = QCryptographicHash::hash(content.toUtf8(), QCryptographicHash::Sha256);
    return hash.toHex();
}

QString API_ZingMp3::Get_Hash512(const QString &content, const QString &key){
    QByteArray result = QMessageAuthenticationCode::hash(
        content.toUtf8(),
        key.toUtf8(),
        QCryptographicHash::Sha512
        );
    return result.toHex();
}

void API_ZingMp3::Get_Home(const int &count, const int &page, function<void(QByteArray&)>func){
    QMap<QString, QString> parameter;
    parameter["count"] = QString::number(count);
    parameter["segmentId"] = "-1";
    parameter["page"] = QString::number(page);
    qint64 cTime = this->Get_CTime();
    parameter["sig"] = this->Get_ParameterHome(cTime, this->path_Home, count, page);
    this->request_ZingMp3(cTime, this->path_Home, parameter, [=](QNetworkReply *reply){
        QByteArray array;
        if(reply->error() == QNetworkReply::NoError){
            array = reply->readAll();
        }
        reply->deleteLater();
        func(array);
    });
}

void API_ZingMp3::Get_InfoSong(QString &id_Song, function<void(QByteArray&)> func)
{
    QMap<QString, QString> parameter;
    parameter["id"] = id_Song;
    qint64 cTime = this->Get_CTime();
    parameter["sig"] = this->Get_ParameterStream(cTime, id_Song, this->path_Info);
    this->request_ZingMp3(cTime, this->path_Info, parameter, [=](QNetworkReply *reply){
        QByteArray array;
        if(reply->error() == QNetworkReply::NoError){
            array = reply->readAll();
        }
        reply->deleteLater();
        func(array);
    });
}

void API_ZingMp3::Get_ResultSearch(QString &keyWord, function<void(QByteArray&)> func)
{
    QMap<QString, QString> parameter;
    parameter["q"] = keyWord;
    qint64 cTime = this->Get_CTime();
    parameter["sig"] = this->Get_ParameterSearch(cTime, this->path_Search);
    this->request_ZingMp3(cTime, this->path_Search, parameter, [=](QNetworkReply *reply){
        QByteArray array;
        if(reply->error() == QNetworkReply::NoError){
            array = reply->readAll();
        }
        reply->deleteLater();
        func(array);
    });
}

void API_ZingMp3::Get_DataSong(QString source, function<void (QByteArray &)> func)
{
    QNetworkRequest request;
    request.setUrl(source);
    QNetworkReply *reply = this->manger->get(request);
    connect(reply, &QNetworkReply::finished, this, [=]{
        this->handle_dataSong(reply, func);
    });
}

QString API_ZingMp3::Get_ParameterStream(qint64 &cTime, QString &id_Song ,QString &path)
{
    QString content = QString("ctime=%1id=%2version=%3")
                          .arg(cTime)
                          .arg(id_Song)
                          .arg(this->Version);
    return this->Convert_ParameterformString(content, path);
}

QString API_ZingMp3::Convert_ParameterformString(QString &content, QString &path)
{
    QString hash256 = this->Get_Hash256(content);
    QString pathPlusHash = path + hash256;
    QString hash512 = this->Get_Hash512(pathPlusHash, this->Secret_key);
    return hash512;
}

QString API_ZingMp3::Get_ParameterSearch(qint64 &cTime, QString &path){
    QString content = QString("ctime=%1version=%2")
        .arg(cTime)
        .arg(this->Version);
    return this->Convert_ParameterformString(content, path);
}

QString API_ZingMp3::Get_ParameterHome(qint64 &cTime, QString &path, const int &count, const int &page){
    QString content = QString("count=%1ctime=%2page=%3version=%4")
        .arg(count)
        .arg(cTime)
        .arg(page)
        .arg(this->Version);
    return this->Convert_ParameterformString(content, path);
}

void API_ZingMp3::request_ZingMp3(qint64 &cTime, QString &path, QMap<QString, QString> &paranmeter, function<void (QNetworkReply *)> func)
{
    this->Get_Cookie(cTime, [=](QString cookie){
        QUrl new_url;
        new_url.setUrl(this->URL->toString() + path);
        QUrlQuery query;
        QString time = QString::number(cTime);
        query.addQueryItem("ctime", time);
        query.addQueryItem("version", this->Version);
        query.addQueryItem("apiKey", this->API_key);

        for (auto it = paranmeter.begin(); it != paranmeter.end(); it++)
            query.addQueryItem(it.key(), it.value());

        new_url.setQuery(query);

        QNetworkRequest request(new_url);
        request.setHeader(QNetworkRequest::UserAgentHeader, "Mozilla/5.0");
        request.setRawHeader("Cookie", cookie.toUtf8());
        QNetworkReply *reply = this->manger->get(request);
        connect(reply, &QNetworkReply::finished, this, [=]{
            func(reply);
        });
    });
}

qint64 API_ZingMp3::Get_CTime(){
    return QDateTime::currentSecsSinceEpoch();
}

void API_ZingMp3::handle_cookie(QNetworkReply *reply, function<void(QString&)> func){
    QString new_cookie;
    QList<QByteArray> array = reply->headers().values(QHttpHeaders::WellKnownHeader::SetCookie);
    foreach (QByteArray value, array) {
        QString content(value);
        if(content.startsWith("zmp3_rqid")){
            new_cookie = content;
            break;
        }
    }
    reply->deleteLater();
    this->cookie = new_cookie;
    func(cookie);
}

void API_ZingMp3::handle_dataSong(QNetworkReply *reply, function<void (QByteArray &)> func)
{
    QByteArray data = reply->readAll();
    func(data);
    reply->deleteLater();
}


