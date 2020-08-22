#include "popuptimer.h"

PopupTimer::PopupTimer()
{

}

PopupTimer::~PopupTimer(){

}

void PopupTimer::setTimer(const int minutes){
    m_minutesLeft = minutes;
    m_minutesPassed = 0;
}

void PopupTimer::changeTimer(const int minutes){
    m_minutesLeft = minutes - m_minutesPassed;
}

void PopupTimer::start(){
    // Time one minute
    if (m_minutesLeft > 0){
        m_timer.start(sToMs(1), this);
    }
}

void PopupTimer::stop(){
    m_timer.stop();
}
int inline PopupTimer::sToMs(int s){
    return s*1000;
}

int inline PopupTimer::mToMs(int m){
    return m*60*1000;
}

int PopupTimer::minutesLeft() const{
    qDebug() << "AGAIN:" << m_minutesLeft;
    return m_minutesLeft;
}

void PopupTimer::timerEvent(QTimerEvent *event){
    Q_UNUSED(event);

    m_minutesLeft -= 1;
    m_minutesPassed += 1;

    qDebug() << "Minute Passed" << m_minutesLeft;

    // Gets called every minute
    if (m_minutesLeft <= 0) {
        stop();
        emit timerPassed();
        qDebug() << "Timer done";

        m_minutesLeft = m_minutesPassed;
        m_minutesPassed = 0;
        start();
    }

    emit minutePassed(QString::number(m_minutesLeft));
}

bool PopupTimer::isRunning() const{
    return m_timer.isActive();
}
