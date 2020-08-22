#ifndef COMBOBOXNAMESMODEL_H
#define COMBOBOXNAMESMODEL_H

#include <QAbstractListModel>
#include "diary.h"
#include "settings.h"

class ComboBoxNamesModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QString role READ role WRITE setRole);
    Q_PROPERTY(Settings* settings READ settings WRITE setSettings);

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
    Q_INVOKABLE void setCurrentCostCenter(QString value);
    Q_INVOKABLE void setCurrentProject(QString value);
    Q_INVOKABLE void setCurrentSubject(QString value);

    QString role();
    void setRole(QString role);


    void setSettings(Settings* settings);
    Settings* settings();

private:
    QVector<QString> m_items;

public:
    Settings *m_settings;
    QString currentCostCenter;
    QString currentProject;
    QString currentSubject;

    QString g_role;
};

#endif // COMBOBOXNAMESMODEL_H
