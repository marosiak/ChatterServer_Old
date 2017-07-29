#ifndef AUTHSERVER_H
#define AUTHSERVER_H

#include <QObject>
#include <QUdpSocket>
#include <QJsonObject>
#include <QJsonDocument>
#include <./class/database.h>

class AuthServer : public QObject {
    Q_OBJECT

public:
    explicit AuthServer(QObject *parent = nullptr);
    int returnPort = 3432;
    int requestPort = 3433;
    void returnError(QHostAddress targetIp, QString error);
    void addAuthorizedAccount(QString account, QHostAddress ip);
    bool checkIfAccountIsAutorized(QString account, QHostAddress ip);
signals:

public slots:
    void authRequestRecived();

private:
    QMap<QString, QString> authorizedAccounts;
    //authorizedAccounts["Nickname"] = "ip";
    QUdpSocket *socket;
    QUdpSocket *returnSocket;
    QJsonObject objectFromString(const QString& in);
};

#endif // AUTHSERVER_H
