#ifndef COMBOBOXNAMESMODEL_H
#define COMBOBOXNAMESMODEL_H

#include <QAbstractListModel>
#include "diary.h"

class ComboBoxNamesModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QString role READ role WRITE setRole);

public:
    enum comboRoles {
        costCenterRole = Qt::UserRole + 1,
        projectRole,
        subjectRole
    };

    explicit ComboBoxNamesModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void insert(QString value);
    Q_INVOKABLE void renew();

    QString role();
    void setRole(QString role);

private:
    QVector<QString> m_items;

public:
    int g_MAX_HISTORY = 100;
    QString g_role;
};

#endif // COMBOBOXNAMESMODEL_H
