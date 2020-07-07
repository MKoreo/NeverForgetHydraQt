#ifndef DatagridViewModel_H
#define DatagridViewModel_H

#include <QAbstractListModel>
#include "diary.h"

class DatagridViewModel : public QAbstractListModel
{
    Q_OBJECT

public:
    // Roles to retreive the different columns
    enum Roles {
        recordRole = Qt::UserRole + 1,
    };

    explicit DatagridViewModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    Q_INVOKABLE QVariant get(const int row, const int column) const;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    // Ask data from certain day
    Q_INVOKABLE void refresh(QString selectedDate);

private:
    QVector<Record*> m_currentDateRecords;
    // Memory optimalisation, we're going to query straight to diary
    //QVector<QString> m_comboEntries;
};

#endif // DatagridViewModel_H
