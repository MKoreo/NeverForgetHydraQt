#ifndef COSTCENTERNAMESMODEL_H
#define COSTCENTERNAMESMODEL_H

#include <QAbstractListModel>
#include "diary.h"

class CostCenterNamesModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum comboRoles {
        defaultRole = Qt::UserRole + 1,
    };

    explicit CostCenterNamesModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void insert(QString value);

private:
    QVector<QString> m_comboEntries;

};

#endif // COSTCENTERNAMESMODEL_H
