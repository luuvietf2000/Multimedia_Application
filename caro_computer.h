#ifndef CARO_COMPUTER_H
#define CARO_COMPUTER_H

#include <QObject>
#include <QVector>
#include <caro_winchecker.h>
#include <QList>
#include <QHash>
#include "caro_winchecker.h"

class CaroComputer : public QObject
{
    Q_OBJECT
public:
    enum role {
        unknown,
        partner,
        rival
    };
    enum key_mapString{
        attack,
        defend
    };
    explicit CaroComputer(QObject *parent = nullptr);
    point requestComputerMove(const int &value);
    void requestRetry();
    void setNumbleCell(const int &cell);
    void setBoard(QVector<QVector<int>> &board);
    void setPixel(const int &x, const int &y);
signals:
private:
    void getLineParent(QList<char> &list, const int &x, const int &y, const int &index, const bool &isPrepend);
    QList<char> extractParent(const int &x, const int &y, int &index, int &line);
    int convertListToScore(QList<char> &list, QHash<QString, int> &map, int &index);
    QHash<QString, int> map_attackScore;
    QHash<QString, int> map_defendScore;
    QList<point> point_exsit;
    QVector<QVector<int>> *boardPointer;
    int numbleCell;
    inline static int winner = -1;
    inline static int count = 5;
    inline static char charRole[] = {'.', '*', '~'};
    inline static int dx[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    inline static int dy[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    bool point_valid(const int &x, const int &y);
    int caculatorScore(int &x, int &y);
    int max(int &one, int &two);
    void addCharForFunctionConvertListToScore(QList<char> &list, int &index, QString &key_index, QString &key);
    bool checkComputerWinner(QString &key, QString &key_index, QHash<QString, int> &score_map, QHash<QString, int> &map);
    void removeCharForFunctionConvertListToScore(QList<char> &list, int &slow, QString &key_index, QString &key);
};

#endif // CARO_COMPUTER_H
