#include "backend.h"

BackEnd::BackEnd(QObject *parent, Settings *settings) :
    QObject(parent)
{
    // Upon creating, fill in current date
    setCurrentDate();

    // Pointer to created/loaded settings
    m_settings = settings;

    // Start timer with current timer settings
    m_popupTimer = new PopupTimer();
    m_popupTimer->setTimer(m_settings->timer());
    m_popupTimer->start();

    // Pass popuptimer signals to route it to qml
    connect(m_popupTimer,   &PopupTimer::timerPassed,           this, &BackEnd::s_timerPassed);
    connect(m_popupTimer,   &PopupTimer::minutePassed,          this, &BackEnd::s_minutePassed);

    // Connect signals from setting that can change
    connect(m_settings,     &Settings::s_timerChanged,          this, &BackEnd::timerChanged);
    connect(m_settings,     &Settings::s_timerReset,            this, &BackEnd::timerReset);
    connect(m_settings,     &Settings::s_filterTypeChanged,     this, &BackEnd::filterTypeChanged);
    connect(m_settings,     &Settings::s_filterDropdownChanged, this, &BackEnd::filterDropdownChanged);
    connect(m_settings,     &Settings::s_historyTicksChanged,   this, &BackEnd::historyTicksChanged);
    connect(m_settings,     &Settings::s_startWithOsChanged,    this, &BackEnd::startWithOsChanged);
}

void BackEnd::timerReset(){
    m_popupTimer->setTimer(m_settings->timer());
    Notifier::instance().requestNotification("Timer Reset", "Timer has been reset to " + QString::number(m_settings->timer()) + " minutes", false, false);
}
void BackEnd::timerChanged(){
    m_popupTimer->changeTimer(m_settings->timer());
    Notifier::instance().requestNotification("Timer Changed", "Timer has been set to " + QString::number(m_settings->timer()) + " minutes, currently " + QString::number(m_popupTimer->minutesLeft()) + " minutes left.", false, false);

}

void BackEnd::filterDropdownChanged(){

}
void BackEnd::filterTypeChanged(){

}
void BackEnd::historyTicksChanged(){

}

void BackEnd::startWithOsChanged(){

}

Settings* BackEnd::settings(){
    return m_settings;
}

// ---- MenuItems
void BackEnd::newDiary(QString path){
    // TODO: comfirmation that you will delete the old one
    if(path.contains("file:")){
        m_path = path.remove(0, 7);
    } else {
        m_path = path;
    }

    Diary::instance().newDiary(m_path);
}

void BackEnd::loadDiary(){
    newDiary(m_path);
    Diary::instance().loadDiary(m_path);
    Notifier::instance().requestNotification("Diary succesfully loaded", "Location: " + m_path +"\nNumber of records: " + QString::number(Diary::instance().count()), true, false);
}

void BackEnd::saveDiary(){
    Diary::instance().saveDiary(m_path);
    Notifier::instance().requestNotification("Diary Saved", "Succesfully saved diary: " + m_path, true, false);
}

void BackEnd::openHydra() const{
    // TODO: Change url to realy HYDRA Url
    QDesktopServices::openUrl(QUrl("/home", QUrl::TolerantMode));
    Notifier::instance().requestNotification("Never Forget Hydra opened", "Please check your webbrowser.", true, false);
}

// ---- Methods
void BackEnd::addRecord(){
    QString params[] = {m_date, m_minutes, m_costCenter, m_project, m_subject };
    if (Record::validateParameters(params)){
        Diary::instance().addRecord(new Record(QDate::currentDate().toString("yyyy-MM-dd"), m_date, m_costCenter, m_project, m_subject, m_minutes));
        Diary::instance().saveDiary(m_path);
        Notifier::instance().requestNotification("SUCCESS", "Record has been added to the Diary.", false, false);
    } else {
        Notifier::instance().requestNotification("FAILED", "One of the required fields is incorrect/empty. Please check.", false, true);
    }
}

void BackEnd::setCurrentDate(){
    // Set m_date to current date in yyyy-MM-dd format
    setDate(QDate::currentDate().toString("yyyy-MM-dd"));
}

void BackEnd::increaseDate(const int &type){
    QDate qdate = QDate::fromString(m_date, "yyyy-MM-dd");

    switch(type){
    case 1: m_date = qdate.addYears(1).toString("yyyy-MM-dd");
        break;
    case 2:
        m_date = qdate.addMonths(1).toString("yyyy-MM-dd");
        break;
    default: m_date = qdate.addDays(1).toString("yyyy-MM-dd");
        break;
    }
}
void BackEnd::decreaseDate(const int &type){
    QDate qdate = QDate::fromString(m_date, "yyyy-MM-dd");
    switch(type){
    case 1: m_date = qdate.addYears(-1).toString("yyyy-MM-dd");
        break;
    case 2:
        m_date = qdate.addMonths(-1).toString("yyyy-MM-dd");
        break;
    default: m_date = qdate.addDays(-1).toString("yyyy-MM-dd");
        break;
    }
}

// Setters
void BackEnd::setCostCenter(const QString costCenter){
    m_costCenter = costCenter;
}
void BackEnd::setProject(const QString project){
    m_project = project;
}
void BackEnd::setSubject(const QString subject){
    m_subject = subject;
}
void BackEnd::setMinutes(const QString minutes){
    m_minutes = minutes;
}
void BackEnd::setPath(const QString path){
    m_path = path;
}
void BackEnd::setDate(const QString date){
    m_date = date;
}

// Getters
QString BackEnd::getDate() const{
    return m_date;
}
QString BackEnd::getPath() const{
    return m_path;
}
