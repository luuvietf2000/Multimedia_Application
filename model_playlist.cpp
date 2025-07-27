#include "model_playlist.h"
#include "QJsonDocument"
#include "QJsonArray"
#include "string"
#include "QJsonObject"
#include "QHash"
using std::string;
using std::function;

ModelPlayList::ModelPlayList(QObject *parent)
    : QAbstractListModel(parent){
    stateRequest = None;
    list_func = {
        [this](QJsonDocument json){handle_PlaylistHistory(json);},
        [this](QJsonDocument json){handle_PlaylistRecomment(json);},
        [this](QJsonDocument json){handle_PlayListNewRelease(json);}
    };
    type_items["recentPlaylist"] = 0;
    type_items["songStation"] = 1;
    type_items["new-release"] = 2;
    currentIndexItem = 0;
    _image = "qrc:/image/zingmp3_big.png";
    _degree = _length = 0;
    _visibleSearch = _isSearch = _download = _mediaState = false;
    _nextState = loopOneSong;
    _nameAuthor = _nameSong = "Not yet available";

    QString path = QDir::currentPath() +"/music";
    QDir dir;
    if(!dir.exists(path)){
        if(dir.mkpath(path))
            qDebug() << "create foler music";
        else
            qDebug() << "not create foler music";
        return;
    }else{
        QStringList filters;
        filters << "*.mp3";
        dir = QDir(path);
        QStringList list = dir.entryList(filters, QDir::Files ,QDir::Name);
        for(int i = 0; i < list.count(); i++){
            localPlaylist[list[i]] = true;
        }
    }
}

QString ModelPlayList::Image() const
{
    return _image;
}

void ModelPlayList::setImage(const QString &image)
{
    if(image != _image){
        _image = image;
        emit imageChanged();
    }
}

QString ModelPlayList::nameSong() const
{
    return _nameSong;
}

void ModelPlayList::setNameSong(const QString &name)
{
    if(name != _nameSong){
        _nameSong = name;
        emit nameSongChanged();
    }
}

QString ModelPlayList::nameAuthor() const
{
    return _nameAuthor;
}

void ModelPlayList::setNameAuthor(const QString &name)
{
    if(name != _nameAuthor){
        _nameAuthor = name;
        emit nameAuthorChanged();
    }
}

QString ModelPlayList::source() const
{
    return _source;
}

void ModelPlayList::setSource(const QString &source)
{
    if(_source != source){
        _source = source;
        emit sourceChanged();
    }
}

int ModelPlayList::degree() const
{
    return _degree;
}

void ModelPlayList::setDegree(const int &degree)
{
    if(degree != _degree){
        _degree = degree;
        emit degreeChanged();
    }
}

int ModelPlayList::length() const
{
    return _length;
}

void ModelPlayList::setLength(const int &length)
{
    if(length != _length){
        _length = length;
        emit lengthChanged();
    }
}

bool ModelPlayList::visibleSearch() const
{
    return _visibleSearch;
}

void ModelPlayList::setVisibleSearch(const bool &visible)
{
    if(visible != _visibleSearch){
        _visibleSearch = visible;
        emit visibleSearchChanged();
    }
}

bool ModelPlayList::isSearch() const
{
    return _isSearch;
}

void ModelPlayList::setIsSearch(const bool &search)
{
    if(search != _isSearch){
        _isSearch = search;
        emit isSearchChanged();
    }
}


bool ModelPlayList::mediaState() const
{
    return _mediaState;
}

void ModelPlayList::setMediaState(const bool &state)
{
    if(state != _mediaState){
        _mediaState = state;
        emit mediaStateChanged();
    }
}

bool ModelPlayList::download() const
{
    return _download;
}

void ModelPlayList::setDownload(const bool &download)
{
    if(download != _download){
        _download = download;
        emit downloadChanged();
    }
}

int ModelPlayList::nextState() const
{
    return _nextState;
}

void ModelPlayList::setNextState(const int &state)
{
    if(state != _nextState){
        _nextState = state > 2 ? 0 : state;
        qDebug() << _nextState;
        emit nextStateChanged();
    }
}

int ModelPlayList::volume() const
{
    return _volume;
}

void ModelPlayList::setVolume(const int &value)
{
    if(value != _volume){
        _volume = value;
        emit volumeChanged();
    }
}

void ModelPlayList::setPropertyMusic(const QString &name, const QString &author, const QString &source, const bool &downloadState)
{
    setNameSong(name);
    setNameAuthor(author);
    setImage(source);
    setDownload(downloadState);
}

void ModelPlayList::requestNextSong()
{
    handle_nextSong(1);
}

void ModelPlayList::requestPreviosSong()
{
    handle_nextSong(-1);
}

void ModelPlayList::requestSelectionPlaylist(QObject *object)
{
    auto *itemModel = qobject_cast<QAbstractItemModel *>(object);
    if (!itemModel) {
        qWarning() << "Model is not a QAbstractItemModel";
        return;
    }
    currentPlaylist.clear();
    int rowCount = itemModel->rowCount();
    for (int row = 0; row < rowCount; ++row) {
        QModelIndex index = itemModel->index(row, 0);
        itemPlaylist item;
        item.song = itemModel->data(index, song).toString();
        item.author = itemModel->data(index, author).toString();
        item.id = itemModel->data(index, id).toString();
        item.downloadMode = itemModel->data(index, downloadMode).toInt();
        item.resource = itemModel->data(index, resource).toString();
        item.streamingStatus = itemModel->data(index, streamingStatus).toInt();
        if(item.streamingStatus != 2){
            if(_nameSong == item.song)
                currentIndexItem = row;
            currentPlaylist.push_back(item);
        }
    }
}

int ModelPlayList::rowCount(const QModelIndex &parent) const{
    Q_UNUSED(parent);
    return playlist.count();
}

QVariant ModelPlayList::data(const QModelIndex &index, int role) const{
    QVariant variant;
    if(!index.isValid())
        return variant;
    const itemPlaylist &item = playlist.at(index.row());
    switch (role) {
        case song:
            return item.song;
        case author:
            return item.author;
        case id:
            return item.id;
        case downloadMode:
            return item.downloadMode;
        case resource:
            return item.resource;
        case streamingStatus:
            return item.streamingStatus;
    }
    return variant;
}

QHash<int, QByteArray> ModelPlayList::roleNames() const{
    QHash<int, QByteArray> roles;
    roles[song] = "song";
    roles[author] = "author";
    roles[id] = "id";
    roles[downloadMode] = "downloadMode";
    roles[resource] = "resource";
    roles[streamingStatus] = "streamingStatus";
    return roles;
}

void ModelPlayList::handle_nextSong(const int &range)
{
    switch (_nextState) {
        case loopOneSong: handle_nextSongModeLoopOne();
            break;
        case loopAllSong: handle_nextSongModeLoopAll(range);
            break;
        case randomSong: handle_nextSongModeRandom();
    }
}

void ModelPlayList::resetPlaylist(QList<itemPlaylist> &listItem)
{
    beginResetModel();
    this->playlist = listItem;
    endResetModel();
}


void ModelPlayList::requestHomeZingMp3()
{
    _resource = ZingMp3;
    stateRequest = requestHome;
    this->zing_mp3.Get_Home(30, 1, [=](QByteArray byteArray){
        QJsonDocument json = QJsonDocument::fromJson(byteArray);
        QJsonValue data = json["data"];
        QJsonDocument items(data.toObject());
        QJsonArray array = items["items"].toArray();
        for(int i = 0; i < array.size(); i++){
            QJsonDocument _item(array[i].toObject());
            QString type = _item["sectionType"].toString();
            if(!type_items.contains(type))
                continue;
            list_func[type_items[type]](_item);
        }
        QFile file("log_result_home.txt");
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << json.toJson(QJsonDocument::Indented);
            file.close();
        } else {
            qWarning() << "Không thể mở file để ghi log!";
        }
    });
}

void ModelPlayList::requestStreamingAudioLink(QString id)
{
    if(_resource == ZingMp3)
        this->zing_mp3.Get_LinkStreamAudio(id, [=](QByteArray byteArray){
            QString link;
            QJsonDocument json = QJsonDocument::fromJson(byteArray);
            QJsonObject object = json.object();
            if(object.contains("data")){
                object = object["data"].toObject();
                if(object.contains("128"))
                    link = object["128"].toString();
            }
            setSource(link);
            bool isDownload = localPlaylist.contains(_nameSong + ".mp3");
            setDownload(isDownload);
        });
    else{
        QString path = QDir::currentPath() + "/music/" + id + ".mp3";
        _download = true;
        setSource(path);
    }
}

void ModelPlayList::requestLocalPlaylist()
{
    _resource = Local;
    stateRequest = requestReadLocal;
    QList<itemPlaylist> newList;
    QString path = QDir::currentPath() +"/music";
    QDir dir;
    if(!dir.exists(path)){
        if(dir.mkpath(path))
            qDebug() << "create foler music";
        else
            qDebug() << "not create foler music";
        return;
    }else{
        QStringList filters;
        filters << "*.mp3";
        dir = QDir(path);
        QStringList list = dir.entryList(filters, QDir::Files ,QDir::Name);
        itemPlaylist newItem;
        newItem.resource = "qrc:/image/zingmp3_big.png";
        for(int i = 0; i < list.count(); i++){
            int index = list[i].lastIndexOf(".");
            QString name = list[i].remove(index, list[i].count() - index);
            newItem.song = newItem.id = name;
            newItem.author = "Not yet available";
            newItem.streamingStatus = 1;
            newList.append(newItem);
        }
    }
    if(stateRequest == requestReadLocal){
        resetPlaylist(newList);
        emit playlistChanged(this);
    }
}

void ModelPlayList::requestLoopState()
{
    emit loopStateChanged();
}



void ModelPlayList::handle_PlaylistHistory(QJsonDocument json)
{

}

void ModelPlayList::handle_PlaylistRecomment(QJsonDocument json)
{

}

void ModelPlayList::handle_PlayListNewRelease(QJsonDocument json)
{
    QList<itemPlaylist> list_object;
    QJsonObject _object = json.object();
    if(_object.contains("items")){
        QJsonObject items = _object["items"].toObject();
        QJsonArray all = items["all"].toArray();
        for(int i = 0; i < all.count(); i++){
            QJsonObject value = all[i].toObject();
            itemPlaylist item;
            item.id = value["encodeId"].toString();
            item.song = value["title"].toString();
            item.resource = value["thumbnailM"].toString();
            item.author = value["artistsNames"].toString();
            item.streamingStatus = value["streamingStatus"].toInt();
            if(value.contains("downloadPrivileges"))
                item.downloadMode = value["downloadPrivileges"].toArray()[0].toInt();
            list_object.append(item);
        }
    }
    if(stateRequest == requestHome){
        resetPlaylist(list_object);
        emit playListNewRelease(this);
    }
}

void ModelPlayList::requestSearchZingMp3(QString keyword)
{
    _resource = ZingMp3;
    stateRequest = requestSearch;
    this->zing_mp3.Get_ResultSearch(keyword, [=](QByteArray byteArray){
        QList<itemPlaylist> newPlaylist;
        QJsonDocument json = QJsonDocument::fromJson(byteArray);
        QJsonObject data = json["data"].toObject();
        QJsonArray array = data["songs"].toArray();
        for(int i = 0; i < array.count(); i++){
            QJsonObject object = array[i].toObject();
            if(!object.contains("title"))
                continue;
            itemPlaylist newItem;
            newItem.song = object["title"].toString();
            newItem.resource = object["thumbnailM"].toString();
            newItem.downloadMode = newItem.streamingStatus = 0;
            newItem.id = object["encodeId"].toString();
            newItem.author = object["artistsNames"].toString();
            newPlaylist.append(newItem);
        }
        if(stateRequest == requestSearch){
            resetPlaylist(newPlaylist);
            emit playlistChanged(this);
        }
    });
}

void ModelPlayList::requestDownload()
{
    this->zing_mp3.Get_DataSong(this->_source, [=](QByteArray data){
        QString path = QDir::currentPath() + "/music/" + this->_nameSong + ".mp3";
        QFile file(path);
        if (file.open(QIODevice::WriteOnly)) {
            file.write(data);
            file.close();
            localPlaylist[_nameSong] = true;
        }
    });
}

void ModelPlayList::handle_playlistRelated(QString id)
{
    this->zing_mp3.Get_InfoSong(id, [=](QByteArray byteArray){
        QJsonDocument json = QJsonDocument::fromJson(byteArray);
        qDebug() << json;
    });
}

void ModelPlayList::handle_nextSongModeLoopOne()
{
    emit setPositionMediaPlay(0);
}

void ModelPlayList::handle_nextSongModeLoopAll(const int &range)
{
    if(!findNextSong(currentIndexItem, (int) currentPlaylist.count(), range))
        if(!findNextSong(-1, currentIndexItem - 1, range))
            handle_nextSongModeLoopOne();
}

void ModelPlayList::handle_nextSongModeRandom()
{
    int index = currentIndexItem;
    QRandomGenerator *random = QRandomGenerator::global();
    while(index == currentIndexItem)
        index = random->bounded(0, (int) currentPlaylist.count());

    requestStreamingAudioLink(currentPlaylist[index].id);
    itemPlaylist item = currentPlaylist[index];
    setPropertyMusic(item.song, item.author, item.resource, item.downloadMode);
}

bool ModelPlayList::findNextSong(const int &start, const int &stop, const int &range)
{
    for(int index = start + 1; index < stop; index++){
        itemPlaylist item = currentPlaylist[index];
        if(item.streamingStatus != 2){
            setPropertyMusic(item.song, item.author, item.resource, item.downloadMode);
            requestStreamingAudioLink(item.id);
            currentIndexItem = index;
            return true;
        }
    }
    return false;
}
