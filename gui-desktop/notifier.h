#ifndef NOTIFIER_H
#define NOTIFIER_H


#include <QObject>
#include <QVector>

struct Notification{
    QString m_title;
    QString m_content;
    bool m_important;
    bool m_critical;
};


class Notifier: public QObject
{
    Q_OBJECT

public:
    static Notifier& instance();
    ~Notifier();

protected:
    Notifier(){};
    Notifier& operator=(const Notifier& rhs);

public:
    void requestNotification(QString m_title, QString m_content, bool m_important, bool m_critical);

signals:
    void fireNotification(QString m_title, QString m_content, bool m_important, bool m_critical) const;

public slots:
    void notificationKilled();

private:
    QVector<Notification*> m_notifications;
    bool m_notificationActive = false;
};

#endif // NOTIFIER_H
