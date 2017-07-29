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
    void returnError(QHostAddress targetIp, QString error);
    bool checkIfAccountIsAutorized(QString account, QHostAddress ip);
signals:

public slots:
    void authRequestRecived();

private:
    void addAuthorizedAccount(QString& account, QHostAddress& ip);
    QString getPassword(const QString login);
    int returnPort, requestPort;
    QMap<QString, QString> authorizedAccounts;
    QUdpSocket* socket;
    QUdpSocket* returnSocket;
    QJsonObject objectFromString(const QString& in);
};

#endif // AUTHSERVER_H
