#ifndef POPUPTIMER_H
#define POPUPTIMER_H

#include <QDebug>
#include <QBasicTimer>

class PopupTimer : public QObject
{
    Q_OBJECT

public:
    PopupTimer();
    ~PopupTimer();

signals:
    void timerPassed();
    void minutePassed(QString minutesPassed);

public:
    void start();
    void setTimer(const int seconds);
    void changeTimer(const int seconds);
    bool isRunning() const;
    void stop();

    int minutesLeft() const;

    int inline sToMs(int s);
    int inline mToMs(int m);

protected:
    void timerEvent(QTimerEvent *event) override;


private:
    int m_minutesPassed = 0;
    int m_minutesLeft = 0;


    QBasicTimer m_timer;

};

#endif // POPUPTIMER_H
