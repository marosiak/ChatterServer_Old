#include "authserver.h"

AuthServer::AuthServer(QObject *parent) : QObject(parent){}

void AuthServer::start(){
    socket = new QUdpSocket(this);
    socket->bind(QHostAddress::LocalHost, port); // wait for request for auth

    connect(socket, SIGNAL(readyRead()), this, SLOT(authRequestRecived()));
    qDebug() << "Server started";
}

void AuthServer::returnError(QHostAddress targetIp, QString error){
    returnSocket = new QUdpSocket(this);
    returnSocket->bind(targetIp, port-1);
    QByteArray Data;
    Data.append(error);
    returnSocket->writeDatagram(Data, targetIp, port-1);
    qDebug() << "[Auth Error] "<<error<<" to "<<targetIp.toString();
}

void AuthServer::returnMessage(QHostAddress targetIp, QString msg){
    returnSocket = new QUdpSocket(this);
    returnSocket->bind(targetIp, port-1);
    QByteArray Data;
    Data.append(msg);
    returnSocket->writeDatagram(Data, targetIp, port-1);
    qDebug() << "[Auth Message] "<<msg<<" to "<<targetIp.toString();
}

void AuthServer::addAuthorizedAccount(QString& account, QHostAddress& ip) {
    authorizedAccounts.insert(account, ip.toString());
}


bool AuthServer::checkIfAccountIsAutorized(QString account, QHostAddress ip){
    for(const auto& e : authorizedAccounts.toStdMap()) {
        if (account == e.first && ip.toString() == e.second) {
            return true; // authorized
        }
    }
    return false;
}

QJsonObject AuthServer::objectFromString(const QString& in){
    QJsonObject obj;
    QJsonDocument doc = QJsonDocument::fromJson(in.toUtf8());

    // check validity of the document
    if(!doc.isNull()){
        if(doc.isObject()){
            obj = doc.object();
        }
        else {
            qDebug() << "Document is not an object" << endl;
        }
    }
    else{
        qDebug() << "Invalid JSON...\n" << in << endl;
    }
    return obj;
}

void AuthServer::authRequestRecived(){
    qDebug() << "[Auth] Recived auth request";
    QByteArray buffer;
    buffer.resize(socket->pendingDatagramSize());

    QHostAddress sender;
    quint16 senderPort;

    socket->readDatagram(buffer.data(), buffer.size(),&sender, &senderPort);

    QString m = buffer;
    QJsonObject obj = objectFromString(m);
    QString type = obj["type"].toString();
    QString login = obj["login"].toString();
    QString password = obj["password"].toString();

    qDebug() << "[Auth] Request from: " << sender.toString();
    qDebug() << "[Auth] Type of request: "<<type;
    qDebug() << "[Auth] Login: "<<login;
    qDebug() << "[Auth] Password: " << password;
    database = new DataBase;
    if(type == "register"){
        // make account
        if (database->accountExist(login) == false) {
            if(login.length() >= 6){
                if(password.length() >= 6){
                    database->createAccount(login, password);
                    returnMessage(sender, "Account created succesfully");
                } else {
                    returnError(sender, "Password must be at least 6 characters length");
                }
            } else {
                returnError(sender, "Login must be at least 6 characters length");
            }
        } else {
            returnError(sender,"This name is already in use.");
        }
    }
    if(type == "login"){
        // login
        if(database->accountExist(login)){
            QString realPassword = database->getPassword(login);
            if (password == realPassword) {
                //login
                qDebug() << "[Auth] password for "<<login<<" is correct";
                addAuthorizedAccount(login, sender);
                returnMessage(sender, "Access Granted");
            } else {
                qDebug() << "[Auth Error] password for "<<login<<" is incorret";
                returnError(sender, "Wrong password");
            }
        }
    }
    if (type != "login" && type !="register"){
        returnError(sender,"Wrong type of request Please report it to orzel1244@gmail.com");
    }
    delete database;
}

int AuthServer::getPort() const { return port; }
void AuthServer::setPort(int value) { port = value; }
