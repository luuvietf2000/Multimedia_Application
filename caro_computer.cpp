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

point CaroComputer::requestComputerMove(const int &value)
{   const int line = 7;
    const int max_range = 2;
    point result;
    QMap<int, point> score_map;
    QVector<QVector<bool>> visit_map;
    for(int x = 0; x < numbleCell; x++){
        QVector<bool> row;
        for(int y = 0; y < numbleCell; y++)
            row.push_back(false);
        visit_map.push_back(row);
    }
    if(point_exsit.empty())
        result = point(numbleCell / 2, numbleCell / 2);
    else{
        for(auto it = point_exsit.begin(); it != point_exsit.end(); it++){
            for(int range = 1; range <= max_range; range++){
                for(int i = 0; i < line; i++){
                    point _point = *it;
                    int x = _point.x + range * dx[i];
                    int y = _point.y + range * dy[i];
                    if(point_valid(x, y) && ((*boardPointer)[x][y] == CaroViewModel::NotExist) && !visit_map[x][y]){
                        visit_map[x][y] = true;
                        (*boardPointer)[x][y] = value;
                        int score = caculatorScore(x, y);
                        if(score == winner)
                            return point(x, y);
                        score_map.insert(score, point(x, y));
                        (*boardPointer)[x][y] = CaroViewModel::NotExist;
                    }
                }
            }
        }
        result = *(--score_map.end());
    }
    point_exsit.push_back(result);
    return result;
}

void CaroComputer::setNumbleCell(const int &cell)
{
    numbleCell = cell;
}

void CaroComputer::getLineParent(QList<char> &list, const int &x, const int &y, const int &index, const bool &isPrepend)
{
    int current_value = (*boardPointer)[x][y];
    for(int i = 1; i <= count; i++){
        int cx = x + i * dx[index];
        int cy = y + i * dy[index];
        if(point_valid(cx, cy)){
            int next_value = (*boardPointer)[cx][cy];
            int index_role = current_value == next_value || next_value == CaroViewModel::NotExist ? current_value == next_value : rival;
            char value_insert = charRole[index_role];
            if(next_value != CaroViewModel::NotExist && next_value != (*boardPointer)[x + dx[index]][y + dy[index]])
                return;
            if(isPrepend)
                list.prepend(value_insert);
            else
                list.push_back(value_insert);
        }
    }
}

QList<char> CaroComputer::extractParent(const int &x, const int &y, int &index, int &line)
{
    const int maxLine = 7;
    QList<char> list;
    getLineParent(list, x, y, line, true);
    index = list.size();
    list.push_back(charRole[partner]);
    getLineParent(list, x, y, maxLine - line, false);
    return list;
}

int CaroComputer::convertListToScore(QList<char> &list, QHash<QString, int> &map, int &index)
{
    int score = 0;
    int slow = 0;
    QString key = "";
    for(int fast = 0; fast < list.size(); fast++){
        addCharForFunctionConvertListToScore(list, fast, key);
        int loop = key.size() - count;
        for(int i = 0; i <= loop; i++){
            bool isWinner = false;
            if(key.size() == count && fast < index + count && slow > index - count  || key.size() != count)
                isWinner = checkComputerWinner(key, score, map);
            if(isWinner)
                return winner;
            removeCharForFunctionConvertListToScore(list, key, slow);
        }
    }
    return score;
}

bool CaroComputer::point_valid(const int &x, const int &y)
{
    return x > -1 && y > -1 && x < numbleCell && y < numbleCell;
}

void CaroComputer::requestRetry()
{
    point_exsit.clear();
}

void CaroComputer::setBoard(QVector<QVector<int>> &board)
{
    boardPointer = &board;
}

void CaroComputer::setPixel(const int &x, const int &y)
{
    point_exsit.push_back(point(x, y));
}

int CaroComputer::caculatorScore(int &x, int &y)
{
    const int line = 7;
    int sum_score = 0;
    for(int i = 0; i < (line + 1) / 2; i++){
        int index = 0;
        QList list = extractParent(x, y, index, i);
        int score_attack = convertListToScore(list, map_attackScore, index);
        if(score_attack == winner)
            return winner;
        int score_defendMin = convertListToScore(list, map_defendScore, index);
        list[index] = charRole[rival];
        int score_defendMax = convertListToScore(list, map_defendScore, index);
        int score = score_attack + score_defendMax - score_defendMin;
        sum_score += score;
    }
    return sum_score;
}

int CaroComputer::max(int &one, int &two)
{
    return one > two ? one : two;
}

void CaroComputer::removeCharForFunctionConvertListToScore(QList<char> &list, QString &key, int &index)
{
    if(key.size() > 5){
        key.removeFirst();
        index++;
    }
}

void CaroComputer::addCharForFunctionConvertListToScore(QList<char> &list, int &index, QString &key)
{
    key += QString(list[index]);
}

bool CaroComputer::checkComputerWinner(QString &key, int &max_score, QHash<QString, int> &map)
{
    if(map.contains(key)){
        int _score = map[key];
        if(_score == winner)
            return true;
        max_score = max(max_score, _score);
    }
    return false;
}
