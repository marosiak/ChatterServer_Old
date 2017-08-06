#include "friendsmanager.h"

FriendsManager::FriendsManager(QObject* parent) : QObject(parent) {}

void FriendsManager::addFriend(QString token, QString friendName) {
    QString name = AuthServer::getAuthServer().returnNameFromToken(token);
    if (name != "error") {
        if (name != "accounts") {  // for safety
            DataBase::getDatabase().createFriendListTable(name);
            if (!DataBase::getDatabase().checkIfValueIsInTable(name,
                                                               friendName)) {
                if (DataBase::getDatabase().checkIfValueIsInTable("accounts",
                                                                  friendName)) {
                    DataBase::getDatabase().insertIntoFriendListTable(
                        name, friendName);
                }
            }
        }
    }
}

void FriendsManager::removeFriend(QString token, QString friendName) {
    QString name = AuthServer::getAuthServer().returnNameFromToken(token);
    if (name != "accounts") {  // for safety
        DataBase::getDatabase().removeRecord(name, friendName);
    }
}

QString FriendsManager::getFriends(QString token) {
    QString name = AuthServer::getAuthServer().returnNameFromToken(token);
    QString friends = DataBase::getDatabase().getRecords(name);

    QString output =
        QString("{\"type\": \"friendsListRespond\",\"values\": [%1]}")
            .arg(friends);

    return output;
}
