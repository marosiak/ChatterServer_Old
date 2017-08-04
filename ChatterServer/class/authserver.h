#ifndef AUTHSERVER_H
#define AUTHSERVER_H

#include <./class/database.h>
#include <QCryptographicHash>
#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>
#include <QTimer>
#include <QUdpSocket>
#include <cstdlib>
#include <ctime>

class AuthServer : public QObject {
    Q_OBJECT

public:
    explicit AuthServer(QObject* parent = nullptr);
    void start();
    void returnError(QHostAddress targetIp,
                     QString error);  // TODO zrobić porządne zwracanie
    void returnMessage(QHostAddress targetIp, QString type, QString msg);
    bool checkIfAccountIsAutorized(QString token);
    int getPort() const;
    void setPort(int value);
    QString generateToken();
    int getTimeOut() const;
    void setTimeOut(int value);
    void updateTokenTime(QString token);
    void logOff(QString token);
signals:

public slots:
    void removeTimeOutHashes();
    void addOneMinToHashes();
    void authRequestRecived();

private:
    int timeOut;
    QUdpSocket* socket;
    QUdpSocket* returnSocket;
    int port;
    void addAuthorizedAccount(QString token);
    QString getPassword(const QString login);
    int returnPort, requestPort;
    QMap<QString, int> authorizedAccounts;
    QJsonObject objectFromString(const QString& in);
    DataBase* database;
};

#endif  // AUTHSERVER_H
