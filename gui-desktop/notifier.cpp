#include "notifier.h"
#include "QDebug"
Notifier& Notifier::instance()
{
    // Singleton declared in static memory
    // Will be same instance, everytime method is called
    static Notifier singleton;
    return singleton;
}

Notifier::~Notifier(){

}

void Notifier::requestNotification(QString m_title, QString m_content, bool m_important, bool m_critical) {
    qDebug() << "Notification requested";

    if (m_notificationActive){
        Notification *notification = new Notification();
        notification->m_title = m_title;
        notification->m_content = m_content;
        notification->m_important = m_important;
        notification->m_critical = m_critical;

        m_notifications.append(notification);
    } else {
        m_notificationActive = true;
        emit fireNotification(m_title, m_content, m_important, m_critical);
    }
}

void Notifier::notificationKilled(){
    if(m_notifications.count() != 0){
        emit fireNotification(m_notifications[0]->m_title,m_notifications[0]->m_content, m_notifications[0]->m_important, m_notifications[0]->m_critical);
        delete(m_notifications[0]);
        m_notifications.removeAt(0);
    } else {
        m_notificationActive = false;
    }
}
