#ifndef NOTIFICATIONMANAGER_H
#define NOTIFICATIONMANAGER_H

#include "libda_global.h"
#include <QObject>

LDA_BEGIN_NAMESPACE

class LIBDA_SHARED_EXPORT NotificationObject : public QObject
{
    Q_OBJECT
public:
    explicit NotificationObject(QObject *parent = nullptr);
    ~NotificationObject();

    NotificationObject *setSummary(QString sum); //
    NotificationObject *setBody(QString body);
    NotificationObject *setApp(QString appName);
    NotificationObject *setAppIcon(QString iconName);
    NotificationObject *setActions(QStringList actions);
    NotificationObject *setActionIDs(QStringList actIDs);
    NotificationObject *setRawActions(QStringList rawActions);
    NotificationObject *setTimeout(int t);

    NotificationObject *addAction(QString identifier = "", QString text = "action");
    NotificationObject *addAction(QString text);
    NotificationObject *addActionIdentifier(QString id);

    NotificationManager *manager() const;
    uint id();
    int timeout();
    QString summary();
    QString body();
    QString appName();
    QString appIcon();
    QStringList rawActions();
    QStringList actions();
    QStringList actionIDs();

    void close();

Q_SIGNALS:
    void actionTriggered(QString identifier);
    void closed();

private:
    NotificationManager *m_manager;
    uint m_id = 0;
    int m_timeout = -1;
    QString m_summary = "";
    QString m_body = "";
    QString m_app = "";
    QString m_appIcon = "";
    QStringList m_actions;
    QStringList m_actionIDs;

    QStringList mergeAAI();
    void unMergeRaw(QStringList raw);

    friend class NotificationManager;
};

class LIBDA_SHARED_EXPORT NotificationManager : public QObject
{
    Q_OBJECT
public:
    explicit NotificationManager(QObject *parent = nullptr);
    inline static NotificationManager *instance() {
        static NotificationManager *inst = new NotificationManager;
        return inst;
    }
    NotificationObject *notify(QString appName, QString appIcon, QString summary, QString body, QStringList actions, QStringList actionIDs, int timeout) const;
    NotificationObject *notify(QString appName, QString appIcon, QString summary, QString body, QStringList rawActions, int timeout) const;
    NotificationObject *notify(NotificationObject *o) const;

    void handleCloseRequest(uint id);

Q_SIGNALS:
    void dataTriggered(QString ID);

protected:
    QList<NotificationObject *> *internList;
    NotificationsInterface *interface;

private Q_SLOTS:
    void handleClosed(uint a, uint b);
    void handleActionTriggered(uint id, QString ID);
};

LDA_END_NAMESPACE

#endif // NOTIFICATIONMANAGER_H
