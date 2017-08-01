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
    void start();
    void returnError(QHostAddress targetIp, QString error);
    void returnMessage(QHostAddress targetIp, QString msg);
    bool checkIfAccountIsAutorized(QString account, QHostAddress ip);

    int getPort() const;
    void setPort(int value);

signals:

public slots:
    void authRequestRecived();

private:
    QUdpSocket* socket;
    QUdpSocket* returnSocket;
    int port;
    void addAuthorizedAccount(QString& account, QHostAddress& ip);
    QString getPassword(const QString login);
    int returnPort, requestPort;
    QMap<QString, QString> authorizedAccounts;
    QJsonObject objectFromString(const QString& in);
    DataBase* database;
};

#endif // AUTHSERVER_H
