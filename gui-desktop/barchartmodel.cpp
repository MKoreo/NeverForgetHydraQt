#include "barchartmodel.h"

BarChartModel::BarChartModel(QObject *parent) : QObject(parent)
{

}

void BarChartModel::setHistory(int history){
    m_history = history;
    refreshRecords();
    generateChart();
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

void BarChartModel::generateChart(){
    QHash<QString, int> hash;

    for(Record* rec : m_currentDateRecords){
        QString current = rec->costCenter();
        if(hash.contains(current)){
            hash[current] = hash[current] + rec->minutes();
        } else {
            hash.insert(current, rec->minutes());
        }
    }

    QHash<QString, int>::const_iterator i;
    int totalMinutes = 0;
    for (i = hash.constBegin(); i != hash.constEnd(); ++i){
        // If case to shorten category length
        if(i.key().length() > 15){
            m_categories.append(i.key().mid(0,12).append("..."));
        } else {
            m_categories.append(i.key());
        }
        m_values.append(i.value());
        totalMinutes += i.value();
    }
    m_max = 0;

    for(int i = 0; i < m_values.count(); i++){

        m_values[i] = qRound((double)(m_values.at(i).toInt() / (double) totalMinutes) * 100);
        if(m_values.at(i).toInt() > m_max) { m_max = m_values.at(i).toInt(); }
    }

    m_max += 5;
}

QStringList BarChartModel::getCategories(){
    return m_categories;
}

QVariantList BarChartModel::getValues(){
    return m_values;
}

int BarChartModel::getMax(){
    return m_max;
}
