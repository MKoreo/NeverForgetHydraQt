#ifndef BARCHARTMODEL_H
#define BARCHARTMODEL_H

#include <QObject>

#include "record.h"
#include "diary.h"

class BarChartModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QStringList categories READ getCategories NOTIFY chartChanged);
    Q_PROPERTY(QVariantList  values READ getValues NOTIFY chartChanged);
    Q_PROPERTY(int history WRITE setHistory NOTIFY chartChanged);
    Q_PROPERTY(int max READ getMax);

public:
    explicit BarChartModel(QObject *parent = nullptr);

    void refreshRecords();

    void generateChart();
    QStringList getCategories();
    QVariantList getValues();
    void setHistory(int history);
    int getMax();

private:
    int totalMinutes();


signals:
    void chartChanged();


private:
    QVector<Record*> m_currentDateRecords;
    QStringList m_categories;
    QVariantList m_values;
    int m_history;
    int m_max;
};

#endif // BARCHARTMODEL_H
