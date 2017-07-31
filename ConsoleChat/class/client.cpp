#include "client.h"

Client::Client(QObject *parent) : QObject(parent) {}

void Client::loginRequest() {
    QByteArray array;
    array.append(getPassword());
    QString pass = QCryptographicHash::hash(array,QCryptographicHash::Md5).toHex(); // bad password
    QString message = QString("{\"type\": \"login\",\"login\": \"%1\",\"password\": \"%2\"}").arg(getLogin()).arg(pass);
    sendMessage(message);
}

void Client::registerRequest(){
    QByteArray array;
    array.append(getPassword());
    QString pass = QCryptographicHash::hash(array,QCryptographicHash::Md5).toHex(); // bad password
    QString message = QString("{\"type\": \"register\",\"login\": \"%1\",\"password\": \"%2\"}").arg(getLogin()).arg(pass);
    sendMessage(message);
}

void Client::start(){
    socket = new QUdpSocket(this);
    socket->bind(QHostAddress::LocalHost, port-1);

    connect(socket, SIGNAL(readyRead()), this, SLOT(reciveMessage()));
}

void Client::sendMessage(QString msg){
    postSocket = new QUdpSocket(this);
    postSocket->bind(serverIp, port);
    QByteArray Data;
    Data.append(msg);
    postSocket->writeDatagram(Data, serverIp, port);
}

void Client::reciveMessage(){
    QByteArray buffer;
    buffer.resize(socket->pendingDatagramSize());

    QHostAddress sender;
    quint16 senderPort;

    socket->readDatagram(buffer.data(), buffer.size(),&sender, &senderPort);
    setLastMessageFromServer(buffer);
    qDebug() << "Server: "<<buffer;
    if (buffer == "Access Granted"){
        isLogged = true;
    }
}

// Setters
void Client::setServerIp(const QHostAddress &value){ serverIp = value; }
void Client::setPort(int value){ port = value; }
void Client::setLogin(const QString &value) { login = value; }
void Client::setPassword(const QString &value) { password = value; }
void Client::setIsLogged(bool value) { isLogged = value; }
void Client::setLastMessageFromServer(const QString &value) { lastMessageFromServer = value; }

// Getters
int Client::getPort() const{ return port; }
QString Client::getPassword() const{ return password; }
QString Client::getLogin() const { return login; }
QString Client::getLastMessageFromServer() const { return lastMessageFromServer; }
