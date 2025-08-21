#ifndef MODEL_PLAYLIST_H
#define MODEL_PLAYLIST_H

#include <QObject>
#include <QtQml>
#include <QMap>
#include "API_ZingMp3.h"
#include "string"
#include "QHash"
#include "functional"
using std::string;
using std::function;

class ModelPlayList : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QString Image READ Image WRITE setImage NOTIFY imageChanged FINAL)
    Q_PROPERTY(QString nameSong READ nameSong WRITE setNameSong NOTIFY nameSongChanged FINAL)
    Q_PROPERTY(QString nameAuthor READ nameAuthor WRITE setNameAuthor NOTIFY nameAuthorChanged FINAL)
    Q_PROPERTY(QString source READ source WRITE setSource NOTIFY sourceChanged FINAL)
    Q_PROPERTY(int degree READ degree WRITE setDegree NOTIFY degreeChanged FINAL)
    Q_PROPERTY(int length READ length WRITE setLength NOTIFY lengthChanged FINAL)
    Q_PROPERTY(bool visibleSearch READ visibleSearch WRITE setVisibleSearch NOTIFY visibleSearchChanged FINAL)
    Q_PROPERTY(bool isSearch READ isSearch WRITE setIsSearch NOTIFY isSearchChanged FINAL)
    Q_PROPERTY(bool mediaState READ mediaState WRITE setMediaState NOTIFY mediaStateChanged FINAL)
    Q_PROPERTY(bool download READ download WRITE setDownload NOTIFY downloadChanged FINAL)
    Q_PROPERTY(int nextState READ nextState WRITE setNextState NOTIFY nextStateChanged FINAL)
    Q_PROPERTY(int volume READ volume WRITE setVolume NOTIFY volumeChanged FINAL)

public:

    enum playlistInfo{
        song = Qt::UserRole + 1,
        author,
        id,
        downloadMode,
        streamingStatus,
        resource
    };
    enum resource{
        ZingMp3,
        Local
    };

    enum nextState{
        loopOneSong,
        loopAllSong,
        randomSong
    };
    enum stateHandleRequest{
        None,
        requestSearch,
        requestReadLocal,
        requestHome
    };
    struct itemPlaylist{
        QString song;
        QString author;
        QString id;
        int downloadMode;
        QString resource;
        int streamingStatus;
    };
    explicit ModelPlayList(QObject *parent = nullptr);
    QString Image() const;
    void setImage(const QString &image);
    QString nameSong() const;
    void setNameSong(const QString &name);
    QString nameAuthor() const;
    void setNameAuthor(const QString &name);
    QString source() const;
    void setSource(const QString &source);
    int degree() const;
    void setDegree(const int &degree);
    int length() const;
    void setLength(const int &length);
    bool visibleSearch() const;
    void setVisibleSearch(const bool &visible);
    bool isSearch() const;
    void setIsSearch(const bool &search);
    bool mediaState() const;
    void setMediaState(const bool &state);
    bool download() const;
    void setDownload(const bool &download);
    int nextState() const;
    void setNextState(const int &state);
    int volume() const;
    void setVolume(const int &value);

    Q_INVOKABLE void setPropertyMusic(const QString &name, const QString &author, const QString &source, const bool &downloadState);
    Q_INVOKABLE void requestNextSong();
    Q_INVOKABLE void requestPreviosSong();
    Q_INVOKABLE void requestSelectionPlaylist(QObject *object);
    Q_INVOKABLE void requestHomeZingMp3();
    Q_INVOKABLE void requestStreamingAudioLink(QString id);
    Q_INVOKABLE void requestLocalPlaylist();
    Q_INVOKABLE void requestLoopState();
    Q_INVOKABLE void requestSearchZingMp3(QString keyword);
    Q_INVOKABLE void requestDownload();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
private:
    int stateRequest;
    int currentIndexItem;
    QList<itemPlaylist> playlist;
    API_ZingMp3 zing_mp3;
    QHash<QString, int> type_items;
    QList<function<void(QJsonDocument)>> list_func;
    int _resource;
    QString _image;
    QString _nameSong;
    QString _nameAuthor;
    QString _source;
    int _degree;
    int _length;
    bool _visibleSearch;
    bool _isSearch;
    QList<itemPlaylist> currentPlaylist;
    QMap<QString, bool> localPlaylist;
    bool _mediaState;
    bool _download;
    int _nextState;
    int _volume;

    void handle_nextSong(const int &range);
    void resetPlaylist(QList<itemPlaylist> &listItem);
    void handle_PlaylistHistory(QJsonDocument json);
    void handle_PlaylistRecomment(QJsonDocument json);
    void handle_PlayListNewRelease(QJsonDocument json);
    void handle_playlistRelated(QString id);
    void handle_nextSongModeLoopOne();
    void handle_nextSongModeLoopAll(const int &range);
    void handle_nextSongModeRandom();
    bool findNextSong(const int &start, const int &stop, const int &range);

signals:
    void nextStateChanged();
    void mediaStateChanged();
    void downloadChanged();
    void visibleSearchChanged();
    void isSearchChanged();
    void degreeChanged();
    void imageChanged();
    void nameSongChanged();
    void nameAuthorChanged();
    void sourceChanged();
    void lengthChanged();
    void volumeChanged();
    void loopStateChanged();
    void changedMusicContent();
    void setPositionMediaPlay(const int &pos);

    void playlistChanged(QAbstractListModel* info);
    void playlistHistory(QAbstractListModel* info);
    void playlistRecomment(QAbstractListModel* info);
    void playListNewRelease(QAbstractListModel* info);
};

#endif // MODEL_PLAYLIST_H
