#ifndef CARO_COMPUTER_H
#define CARO_COMPUTER_H

#include <QObject>
#include <QVector>
#include <caro_winchecker.h>
#include <QList>
#include <QHash>

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
    void setPointerBoard(QVector<QVector<pointCaro>> &board);
    void setNumbleCell(const int &cell);
    void getLineParent(const int &x, const int &y, const int &value, const int &direction, QString &line);
    void extractParent(const int &x, const int &y, const int &value, const int &direction, QString &line);
    int convertListToScore(QList<char> &list, QHash<QString, int> &map, int &index);
    QHash<QString, int> map_attackScore;
    QHash<QString, int> map_defendScore;
signals:
private:
    QVector<QVector<pointCaro>> *boardPointer;
    int numbleCell;
    inline static int winner = -1;
    inline static int count = 5;
    inline static char charRole[] = {'.', '*', '~'};
    inline static int dx[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    inline static int dy[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int max(int one, int two);
    void addCharForFunctionConvertListToScore(QList<char> &list, int &index, QString &key_index, QString &key);
    bool checkComputerWinner(QString &key, QString &key_index, QHash<QString, int> &score_map, QHash<QString, int> &map);
    void removeCharForFunctionConvertListToScore(QList<char> &list, int &slow, QString &key_index, QString &key);
};

#endif // CARO_COMPUTER_H
