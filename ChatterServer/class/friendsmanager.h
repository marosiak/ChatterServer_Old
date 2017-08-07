#ifndef FRIENDSMANAGER_H
#define FRIENDSMANAGER_H

#include <./class/authserver.h>
#include <QObject>

class FriendsManager : public QObject {
    Q_OBJECT
public:
    explicit FriendsManager(QObject* parent = nullptr);
    void addFriend(QString token, QString friendName);
    void removeFriend(QString token, QString friendName);
    QString getFriendsResult(QString token, QString part);
    QString getFriends(QString token);
signals:

public slots:
};

#endif  // FRIENDSMANAGER_H
