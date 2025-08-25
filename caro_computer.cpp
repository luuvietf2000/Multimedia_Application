#include "caro_computer.h"
#include "caro_winchecker.h"
#include "caro_viewmodel.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStringList>
#include <QString>
#include <QJsonArray>

CaroComputer::CaroComputer(QObject *parent)
    : QObject{parent}
{
    const QList<QString> key_string= {"attack_score", "defense_score"};
    const QString url = ":/Caro.txt";
    QFile file(url);
    if(!file.open(QIODevice::ReadOnly))
        return;
    QByteArray byte_array = file.readAll();
    QJsonDocument json = QJsonDocument::fromJson(byte_array);
    for(int i = 0; i < key_string.size(); i++){
        QJsonObject object = json[key_string[i]].toObject();
        QStringList list = object.keys();
        for(const auto &key : list){
            QJsonArray array = object[key].toArray();
            for(const auto &value : array){
                switch (i) {
                case attack:
                    map_attackScore[value.toString()] = key.toInt();
                    break;
                case defend:
                    map_defendScore[value.toString()] = key.toInt();
                default:
                    break;
                }
            }
        }
    }
}

void CaroComputer::setPointerBoard(QVector<QVector<pointCaro> > &board)
{
    boardPointer = &board;
}

void CaroComputer::setNumbleCell(const int &cell)
{
    numbleCell = cell;
}

void CaroComputer::getLineParent(const int &x, const int &y, const int &value, const int &direction, QString &line)
{
    bool startRival = false;
    CaroWinChecker win_checker;
    for(int index = 0; index < count; index++){
        int cx = x + index * dx[direction];
        int cy = y + index * dy[direction];
        bool pointValid = win_checker.checkPointValid(cx, cy);
        bool isSameValue = (*boardPointer)[cx][cy].value == value || (*boardPointer)[cx][cy].value == CaroViewModel::NotExist;
        if(pointValid && (isSameValue || startRival)){
            if(startRival && !isSameValue)
                return;
            int range = win_checker.calculatorRange(cx, cy, (*boardPointer)[cx][cy].EndLinePoint[index].x, (*boardPointer)[cx][cy].EndLinePoint[index].y);
            QString content = "";
            for(int i = 0; i < range && index + i < count; i++){
                content += QString(charRole[(*boardPointer)[cx][cy].value]);
            }
            index = range;
            line += content;
        }
        else if(pointValid && index == 0){
            line += QString(charRole[(*boardPointer)[x][y].value]);
            startRival = true;
        }
        else
            return;
    }
}

void CaroComputer::extractParent(const int &x, const int &y, const int &value, const int &direction, QString &line)
{
    const int numbleLine = 7;
    QString prefixLine;
    getLineParent(x, y, value, direction, prefixLine);
    QString afterLine;
    getLineParent(x, y, value, numbleLine - direction, afterLine);
    line = prefixLine + charRole[value] + afterLine;
}

int CaroComputer::convertListToScore(QList<char> &list, QHash<QString, int> &map, int &index)
{
    int score = 0;
    int slow = 0;
    QHash<QString, int> score_map;
    QString key_index = "";
    QString key = "";
    for(int fast = 0; fast < list.size(); fast++){
        addCharForFunctionConvertListToScore(list, fast, key_index, key);
        for(int i = 0; i <= key.size() - count; i++){
            bool isWinner = false;
            if(key.size() == count && fast < index + count && slow > index - count  || key.size() != count)
                isWinner = checkComputerWinner(key, key_index, score_map, map);
            if(isWinner)
                return winner;
            removeCharForFunctionConvertListToScore(list, slow, key_index, key);
        }
    }
    for(auto it = score_map.begin(); it != score_map.end(); it++)
        score += it.value();

    return score;
}

int CaroComputer::max(int one, int two)
{
    return one > two ? one : two;
}

void CaroComputer::removeCharForFunctionConvertListToScore(QList<char> &list, int &slow, QString &key_index, QString &key)
{
    if(key.size() > 5){
        key.removeFirst();
        switch(list[slow]){
            case unknown:
                key_index.removeFirst();
                break;
        }
        slow++;
    }
}

void CaroComputer::addCharForFunctionConvertListToScore(QList<char> &list, int &index, QString &key_index, QString &key)
{
    if(list[index] == charRole[unknown])
        key_index += QString::number(index);
    key += QString(list[index]);
}

bool CaroComputer::checkComputerWinner(QString &key, QString &key_index, QHash<QString, int> &score_map, QHash<QString, int> &map)
{
    if(map.contains(key)){
        int _score = map[key];
        if(_score == winner)
            return true;
        if(score_map.contains(key_index))
            _score = max(score_map[key_index], _score);
        score_map[key_index] = _score;
    }
    return false;
}
