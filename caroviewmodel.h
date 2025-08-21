#ifndef CAROVIEWMODEL_H
#define CAROVIEWMODEL_H

#include <QObject>
#include <QVariant>
#include <QVariantList>
#include <QVector>
#include "carowinchecker.h"

class CaroViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int maxLine READ maxLine WRITE setMaxLine NOTIFY maxLineChanged FINAL)
    Q_PROPERTY(QVariantList board READ board NOTIFY boardChanged FINAL)
    Q_PROPERTY(QVariantList player READ player WRITE setPlayer NOTIFY playerChanged FINAL)
    Q_PROPERTY(int turn READ turn WRITE setTurn NOTIFY turnChanged FINAL)
    Q_PROPERTY(int modeGame READ modeGame WRITE setModeGame NOTIFY modeGameChanged FINAL)
public:
    enum mapCaro{
        NotExist,
        X,
        O
    };
    enum turn{
        turnOne,
        turnTwo
    };
    enum caroMode{
        playerVSComputer,
        playerVsPlayer,
        NoneMode
    };
    Q_INVOKABLE void setPixelBoard(const int &x, const int &y);
    Q_INVOKABLE void setBoardDefault();
    Q_INVOKABLE void requestRetry();

    explicit CaroViewModel(QObject *parent = nullptr);
    QVariantList board() const;

    int maxLine() const;
    void setMaxLine(int newMaxLine);

    int turn() const;
    void setTurn(int newTurn);

    int modeGame() const;
    void setModeGame(int newModeGame);

    QVariantList player() const;
    void setPlayer(const QVariantList &newPlayer);

signals:
    void boardChanged();
    void maxLineChanged();
    void turnChanged();
    void modeGameChanged();
    void playerChanged();

private:
    CaroWinChecker check;
    int getPixel();
    QVector<QVector<int>> m_board;
    int m_maxLine;
    int m_turn;
    int m_modeGame;
    QVariantList m_player;
    QVariantList setInfoPlayer();
    QVariant createInfoPlayer(const int &player, const bool &isComputer);
};

#endif // CAROVIEWMODEL_H
