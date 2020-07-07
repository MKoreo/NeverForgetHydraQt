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

void Diary::sort(){

    // Bounds are a records
    QList<Record*> toBeDeleted = { new Record(), new Record(), new Record(), new Record()};
    Record* earliest = toBeDeleted.at(0);
    Record* earlier = toBeDeleted.at(1);
    int earlierSpot;
    int laterSpot;
    Record* latest = toBeDeleted.at(2);
    Record* later = toBeDeleted.at(3);
    int recordsCount = m_records.count();

    // Set values out of possible bounds of diary's records creationdates
    earliest->setCreationDate(QDate::currentDate().addYears(-50));         // Impossible to set earlier date
    earlier->setCreationDate(QDate::currentDate().addDays(1));          // Idem, but a little later
    later->setCreationDate(QDate::currentDate().addYears(-49));               // Latest possible date created
    latest->setCreationDate(QDate::currentDate().addDays(1));   // Later than latest possible date

    // iterate untill all is sorted
    int boundsModifier = 0;     // Make for loop shorter and shorter, by closing the bounds

    while (boundsModifier < recordsCount / 2){

        // By determining earliest and latest record we can work from both bounds at once
        for(int i = boundsModifier; i < recordsCount - boundsModifier; i++){
            Record* currentRec = m_records.at(i);

            if(currentRec->creationDate().daysTo(earliest->creationDate()) <= 0 && currentRec->creationDate().daysTo(earlier->creationDate()) >= 0 ) {
                // Found an earlier record than the previous
                earlier = currentRec;
                earlierSpot = i;
            }

            if (currentRec->creationDate().daysTo(latest->creationDate()) >= 0 && currentRec->creationDate().daysTo(later->creationDate()) <= 0 ) {
                // Found a later record than the previous
                later = currentRec;
                laterSpot = i;
            }
        }

        // Optimalisation: Prevents reverse order if only 1 day is in Diary + speeds up by skipping all bounds
        if(earlierSpot == laterSpot) {
            break;
        }

        // Simply by flipping record positions we can keep working in m_records
        // Boundsmodifier determines spot in endresult
        // i from for loop determines original spot
        Record* moving = m_records.at(boundsModifier);
        m_records[boundsModifier] = m_records.at(earlierSpot);
        m_records[earlierSpot] = moving;

        moving = m_records.at(recordsCount - 1 - boundsModifier);
        m_records[recordsCount - 1 - boundsModifier] = m_records.at(laterSpot);
        m_records[laterSpot] = moving;

        // Adjust bound records
        earliest = earlier;     // Adjust inner bound
        latest = later;         // Adjust inner bound
        Record* temp = earlier;
        earlier = later;        // Must be later than earliest and must guarantee a record -> use later
        later = temp;           // Must be ealier than latest and must guarantee a record -> use earlier

        // Adjust bound modifier
        boundsModifier++;
    }

    foreach(Record* dummyRec, toBeDeleted){
        delete(dummyRec);
    }
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
