#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QUdpSocket>
#include <QCryptographicHash>
#include <string>


class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);
    void loginRequest();
    void registerRequest();
    void start();

    void setServerIp(const QHostAddress &value);
    void setPort(int value);
    void setLogin(const QString &value);
    void setLastMessageFromServer(const QString &value);
    void setPassword(const QString &value);
    void setIsLogged(bool value);

    QString getLastMessageFromServer() const;
    QString getPassword() const;
    QString getLogin() const;
    int getPort() const;
    bool getIsLogged() const;

signals:

public slots:
    void reciveMessage();

private:
    void sendMessage(QString msg);

    // vars
    QString lastMessageFromServer, login, password;
    bool isLogged = false;
    int port;
    QUdpSocket* postSocket, socket;
    QHostAddress serverIp;

};

#endif // CLIENT_H
