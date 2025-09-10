#ifndef API_ZINGMP3_H
#define API_ZINGMP3_H

#include <QObject>
#include <QUrl>
#include <QNetworkReply>
#include <functional>
using std::function;

class API_ZingMp3 : public QObject
{
    Q_OBJECT
public:
    explicit API_ZingMp3(QObject *parent = nullptr);
    void Get_LinkStreamAudio(QString &id_Song, function<void(QByteArray&)>func);
    void Get_Home(const int &count, const int &page, function<void(QByteArray&)> func);
    void Get_InfoSong(QString &id_Song, function<void(QByteArray&)> func);
    void Get_ResultSearch(QString &keyWord, function<void(QByteArray&)> func);
    void Get_DataSong(QString source, function<void(QByteArray&)> func);

private:
    QString Get_Hash256(const QString &content);
    QString Get_Hash512(const QString &content, const QString &key);
    void Get_Cookie(const qint64 &cTime, function<void(QString&)> func);
    QString Get_ParameterStream(qint64 &cTime, QString &id_Song, QString &path);
    QString Convert_ParameterformString(QString &content, QString &path);
    QString Get_ParameterSearch(qint64 &cTime, QString &path);
    QString Get_ParameterHome(qint64 &cTime, QString &path,const int &count, const int &page);
    void request_ZingMp3(qint64 &cTime, QString &path, QMap<QString, QString> &paranmeter, function<void(QNetworkReply*)> func);
    qint64 Get_CTime();
    void handle_LinkStreamSong(QNetworkReply *reply);
    void handle_cookie(QNetworkReply *reply, function<void(QString&)> func);
    void handle_Error(QNetworkReply *reply);
    void handle_dataSong(QNetworkReply *reply, function<void(QByteArray&)> func);
    QNetworkAccessManager *manger;
    QString Version;
    QUrl* URL;
    QString Secret_key;
    QString API_key;
    QString path_Home;
    QString path_Search;
    QString path_Stream;
    QString path_Info;
    QString cookie;
signals:
};

#endif // API_ZINGMP3_H
