#ifndef FRIENDSMANAGER_H
#define FRIENDSMANAGER_H

#include <QObject>

class FriendsManager : public QObject {
    Q_OBJECT
public:
    explicit FriendsManager(QObject* parent = nullptr);

signals:

public slots:
};

#endif  // FRIENDSMANAGER_H
