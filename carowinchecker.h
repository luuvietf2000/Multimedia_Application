#ifndef CAROWINCHECKER_H
#define CAROWINCHECKER_H

#include <QObject>
#include <QVector>

struct point{
    int x;
    int y;
    point(){
    }
    point(int _x, int _y){
        x = _x;
        y = _y;
    }
};

struct pointCaro{
    point EndLinePoint[8];
    int value;
    pointCaro(int x, int y, int _value){
        point default_endLine = point(x, y);
        for(int i = 0; i < 8; i++){
            EndLinePoint[i] = default_endLine;
            value = _value;
        }

    }
};
class CaroWinChecker : public QObject
{
    Q_OBJECT
public:
    explicit CaroWinChecker(QObject *parent = nullptr);
    inline static int dx[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    inline static int dy[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    void setEdge(const int &size);
    bool setPixel(const int &x, const int &y, int &value);
signals:
private:
    int calculatorRange(const int &x1, const int &y1, const int &x2, const int &y2);
    void updateLine(const int &x1, const int &y1, const int &x2, const int &y2, int &line, const int &index);
    bool checkPointValid(const int &x, const int &y);
    void createBoard();
    int abs(const int &x, const int &y);
    point start, end;
    QVector<QVector<pointCaro>> board;
    int edge;
};

#endif // CAROWINCHECKER_H
