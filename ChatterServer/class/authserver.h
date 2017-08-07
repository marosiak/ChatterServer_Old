#ifndef AUTHSERVER_H
#define AUTHSERVER_H

#include <./class/authorizeduser.h>
#include <./class/database.h>
#include <./class/friendsmanager.h>
#include <QCryptographicHash>
#include <QJsonDocument>
#include <QJsonObject>
#include <QList>
#include <QObject>
#include <QTimer>
#include <QUdpSocket>
#include <cstdlib>
#include <ctime>

class AuthServer : public QObject {
    Q_OBJECT

private:
    AuthServer(const AuthServer&);

public:
    AuthServer();
    static AuthServer& getAuthServer() {
        static AuthServer authS;
        return authS;
    }

    QVector<AuthorizedUser> authUsers;
    QString getSearchResult(QString token, QString part);
    void start();
    void returnError(QHostAddress targetIp, QString error);
    void returnMessage(QHostAddress targetIp, QString type, QString msg);
    bool checkIfAccountIsAutorized(QString token);
    quint16 getPort() const;
    void setPort(quint16 value);
    QString generateToken();
    int getTimeOut() const;
    void setTimeOut(int value);
    void updateTokenTime(QString token);
    void logOff(QString token);
    QString returnNameFromToken(QString token);
signals:

public slots:
    void removeTimeOutHashes();
    void addOneMinToHashes();
    void authRequestRecived();

private:
    int timeOut;
    QUdpSocket* socket;
    QUdpSocket* returnSocket;
    quint16 port;
    void sendToClient(QHostAddress targetIp, QString msg);
    void addAuthorizedAccount(QString token, QString name);
    QString getPassword(const QString login);
    int returnPort, requestPort;
    QJsonObject objectFromString(const QString& in);
    // DataBase* database;
};

#endif  // AUTHSERVER_H
