#include "barchartmodel.h"

BarChartModel::BarChartModel(QObject *parent) : QObject(parent)
{

}

void BarChartModel::setHistory(int history){
    m_history = history;
    refreshRecords();
    emit chartChanged();
}

void BarChartModel::refreshRecords(){
    QDate from;
    switch(m_history){
    case 0: from = QDate::currentDate();
        break;
    case 1: from = QDate::currentDate().addDays(-7);
        break;
    case 2: from = QDate::currentDate().addMonths(-1);
        break;
    case 3: from = QDate::currentDate().addYears(-1);
        break;
    case 4: from = QDate::currentDate().addYears(-100);

    }
    m_categories.clear();
    m_values.clear();
    m_currentDateRecords = Diary::instance().getRecordsByDates(from,QDate::currentDate());
}

QStringList BarChartModel::getCategories(){

    for(Record* rec : m_currentDateRecords){

        // If case to shorten category length
        if(rec->costCenter().length() > 15){
            m_categories.append(rec->costCenter().mid(0,12).append("..."));
        } else {
            m_categories.append(rec->costCenter());
        }

    }
    return m_categories;
}

QVariantList BarChartModel::getValues(){
    for(Record* rec : m_currentDateRecords){
        m_values.append(rec->minutes());
    }
    return m_values;
}
