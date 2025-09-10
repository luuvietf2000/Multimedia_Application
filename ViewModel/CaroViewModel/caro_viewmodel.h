#ifndef CARO_VIEWMODEL_H
#define CARO_VIEWMODEL_H

#include <QObject>
#include <QVariant>
#include <QVariantList>
#include <QVector>
#include "core/CaroGame/caro_winchecker.h"
#include "core/CaroGame/caro_computer.h"

class CaroComputer;

class CaroViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int maxLine READ maxLine WRITE setMaxLine NOTIFY maxLineChanged FINAL)
    Q_PROPERTY(QVariantList board READ board NOTIFY boardChanged FINAL)
    Q_PROPERTY(QVariantList player READ player WRITE setPlayer NOTIFY playerChanged FINAL)
    Q_PROPERTY(int turn READ turn WRITE setTurn NOTIFY turnChanged FINAL)
    Q_PROPERTY(int modeGame READ modeGame WRITE setModeGame NOTIFY modeGameChanged FINAL)
    Q_PROPERTY(int playerWinner READ playerWinner WRITE setPlayerWinner NOTIFY playerWinnerChanged FINAL)
    Q_PROPERTY(QVariantList pointLineWinner READ pointLineWinner WRITE setPointLineWinner NOTIFY pointLineWinnerChanged FINAL)
public:
    enum mapCaro{
        NotExist,
        X,
        O
    };
    Q_ENUM(mapCaro)
    enum turnEnum{
        turnOne,
        turnTwo,
        NoneTurn
    };
    Q_ENUM(turnEnum)

    enum caroMode{
        playerVSComputer,
        playerVsPlayer,
        NoneMode
    };
    Q_ENUM(caroMode)

    Q_INVOKABLE void setPixelBoard(const int &x, const int &y);
    Q_INVOKABLE void setBoardDefault();
    Q_INVOKABLE void requestRetry();

    explicit CaroViewModel(QObject *parent = nullptr);
    ~CaroViewModel();
    QVariantList board() const;

    int maxLine() const;
    void setMaxLine(int newMaxLine);

    int turn() const;
    void setTurn(int newTurn);

    int modeGame() const;
    void setModeGame(int newModeGame);

    QVariantList player() const;
    void setPlayer(const QVariantList &newPlayer);

    QVariantList pointLineWinner() const;
    void setPointLineWinner(const QVariantList &newPointLineWinner);

    int playerWinner() const;
    void setPlayerWinner(int newPlayerWinner);

    void requestComputerAction();
signals:
    void boardChanged();
    void maxLineChanged();
    void turnChanged();
    void modeGameChanged();
    void playerChanged();

    void pointLineWinnerChanged();

    void playerWinnerChanged();

private:
    inline static QString name_computer = "Computer";
    void setWinner(int &_turn, point &start, point &end);
    CaroWinChecker check;
    int getPixel();
    QVector<QVector<int>> m_board;
    int m_maxLine;
    int m_turn;
    int m_modeGame;
    QVariantList m_player;
    QVariantList setInfoPlayer();
    QVariant createInfoPlayer(const int &player, const bool &isComputer);
    QVariantList m_pointLineWinner;
    int m_playerWinner;
    CaroComputer *computer;
};

#endif // CARO_VIEWMODEL_H
