#include "diary.h"
#include <chrono>

Diary& Diary::instance()
{
    // Singleton declared in static memory
    // Will be same instance, everytime method is called
    static Diary singleton;
    return singleton;
}

Diary::~Diary(){

}

void Diary::newDiary(const QString &path) {
    m_path = path;
    m_records = QVector<Record*>();
    m_deletedRecords = QVector<Record*>();
}

bool Diary::loadDiary(const QString &path){
    newDiary(path);
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    DiaryDao::instance().read(path, m_records);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    qDebug() << QString::number(m_records.count()) << " records loaded in " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]";
    return true;
}

bool Diary::saveDiary(const QString &path){
    DiaryDao::instance().write(path, m_records);
    return true;
}

void Diary::addRecord(Record* rec) {
    m_records.append(std::move(rec));
}

bool Diary::removeRecord(const Record* rec){
    // Check if pointer is found and delete that
    for(int i = 0; i < m_records.count(); i++){
        if(m_records.at(i) == rec){
            m_deletedRecords.append(m_records.at(i));
            m_records.remove(i);
            return true;
        }
    }
    return false;
}

Record* Diary::contains(const Record* rec) const {
    for(int i = 0; i < m_records.count() - 1; i++){
        if(m_records.at(i)->compare(*rec) == EqualityGrade::minutes){
            return m_records.at(i);
        }
    }
    return nullptr;
}

QVector<Record*> Diary::getRecordsByDate(const QDate& date){
    QVector<Record*> byDate;

    for(int i = 0; i < m_records.count(); i++){
        if(m_records.at(i)->recordDate() == date){
            byDate.append(m_records.at(i));
        }
    }

    return byDate;
}

QVector<Record*> Diary::getRecordsByDates(const QDate& startDate, const QDate& endDate){
    QVector<Record*> byDate;

    for(int i = 0; i < m_records.count(); i++){
        if(m_records.at(i)->recordDate().daysTo(startDate) <= 0 && m_records.at(i)->recordDate().daysTo(endDate) >= 0 ){
            byDate.append(m_records.at(i));
        }
    }
    return byDate;
}
QVector<Record*> Diary::getRecords() {
    return m_records;
}


int Diary::count(){
    return m_records.count();
}
