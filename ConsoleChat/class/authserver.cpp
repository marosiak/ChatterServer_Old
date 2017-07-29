#include "authserver.h"

AuthServer::AuthServer(QObject *parent) : QObject(parent), returnPort{3432}, requestPort{3433} {

    socket = new QUdpSocket(this);
    socket->bind(QHostAddress::LocalHost, requestPort); // wait for request for auth

    connect(socket, SIGNAL(readyRead()), this, SLOT(authRequestRecived()));
    qDebug() << "Server started";
}

void AuthServer::returnError(QHostAddress& targetIp, QString& error){
    QPointer<QUdpSocket> udp = new QUdpSocket(this); //wrapped into QPointer, will delete itself after getting out of scope
    udp->bind(targetIp, returnPort);
    QByteArray Data;
    Data.append(error);
    udp->writeDatagram(Data, targetIp, returnPort);
    qDebug() << "[Auth Error] "<<error<<" to "<<targetIp.toString();
}

void AuthServer::addAuthorizedAccount(QString& account, QHostAddress& ip) {
    authorizedAccounts.insert(account, ip.toString());
}

bool AuthServer::checkIfAccountIsAutorized(QString& account, QHostAddress& ip){
    for(const auto& e : authorizedAccounts.toStdMap()) {
        qDebug() << e.first << "," << e.second << '\n';
    }
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
    DataBase database;
    if(type == "register"){
        // make account
        if (database.accountExist(login) == false) {
            database.createAccount(login, password);
        } else {
            // return to error "This name is already in use."
            returnError(sender,"This name is already in use.");
        }
    }
    if(type == "login"){
        // login
        if(database.accountExist(login)){
            QString realPassword = database.getPassword(login);
            if (password == realPassword) {
                //login
                qDebug() << "[Auth] password for "<<login<<" is correct";
                addAuthorizedAccount(login, sender);
                returnError(sender,"Access granted");
            } else {
                qDebug() << "[Auth Error] password for "<<login<<" is incorret";
                returnError(sender, "Wrong password");
            }
        }
    }
    if (type != "login" && type !="register"){
        // return error "Wrong type of request"
        returnError(sender,"Wrong type of request");
    }

}
