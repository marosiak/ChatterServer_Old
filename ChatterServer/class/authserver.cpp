#include "authserver.h"

AuthServer::AuthServer() {}

void AuthServer::start() {
    // removeTimeOutHashes()

    QTimer* appendTimer = new QTimer(this);  // add 1 min every 1 min to hashes
    connect(appendTimer, SIGNAL(timeout()), this, SLOT(addOneMinToHashes()));
    appendTimer->start(60000);

    QTimer* timerIfTimeout = new QTimer(this);  // remove time out accounts
    connect(timerIfTimeout, SIGNAL(timeout()), this,
            SLOT(removeTimeOutHashes()));
    timerIfTimeout->start((getTimeOut() * 1000 * 60) + 1000);

    socket = new QUdpSocket(this);
    socket->bind(QHostAddress::LocalHost,
                 getPort());  // wait for request for auth

    connect(socket, SIGNAL(readyRead()), this, SLOT(authRequestRecived()));
    qDebug() << "Server started";
}

void AuthServer::returnError(QHostAddress targetIp, QString error) {
    returnSocket = new QUdpSocket(this);
    returnSocket->bind(targetIp, getPort() - 1);
    QString msg =
        QString("{\"type\": \"error\",\"values\": [\"%1\"]}").arg(error);
    QByteArray Data;
    Data.append(msg);
    returnSocket->writeDatagram(Data, targetIp, getPort() - 1);
    qDebug() << "[Auth Error] " << error << " to " << targetIp.toString();
}

void AuthServer::returnMessage(QHostAddress targetIp, QString type,
                               QString msg) {
    returnSocket = new QUdpSocket(this);
    returnSocket->bind(targetIp, getPort() - 1);
    QString post =
        QString("{\"type\": \"%1\",\"values\": [\"%2\"]}").arg(type).arg(msg);
    QByteArray Data;
    Data.append(post);
    returnSocket->writeDatagram(Data, targetIp, getPort() - 1);
    qDebug() << "[Auth Message] " << msg << " to " << targetIp.toString();
}

void AuthServer::addAuthorizedAccount(QString token, QString name) {
    AuthorizedUser au;
    au.setName(name);
    au.setTime(0);
    au.setToken(token);
    authUsers.append(au);
}

bool AuthServer::checkIfAccountIsAutorized(QString token) {
    for (int i = 0; i < authUsers.size(); ++i) {
        if (authUsers.at(i).getToken() == token) { return true; }
    }
    return false;
}

QJsonObject AuthServer::objectFromString(const QString& in) {
    QJsonObject obj;
    QJsonDocument doc = QJsonDocument::fromJson(in.toUtf8());

    // check validity of the document
    if (!doc.isNull()) {
        if (doc.isObject()) {
            obj = doc.object();
        } else {
            qDebug() << "Document is not an object" << endl;
        }
    } else {
        qDebug() << "Invalid JSON...\n" << in << endl;
    }
    return obj;
}

void AuthServer::authRequestRecived() {
    QByteArray buffer;
    buffer.resize(socket->pendingDatagramSize());

    QHostAddress sender;
    quint16 senderPort;

    socket->readDatagram(buffer.data(), buffer.size(), &sender, &senderPort);

    QJsonObject obj = objectFromString(QString(buffer));
    QJsonValue val = obj.value("values");
    QJsonArray array = val.toArray();
    QString type = obj.value("type").toString();

    if (type == "register" || type == "login") {
        qDebug() << "[Auth] Recived auth request";
    }

    if (type == "register") {
        QString login = array[0].toString();
        QString password = array[1].toString();
        if (DataBase::getDatabase().accountExist(login) == false) {
            if (login.length() >= 6) {
                if (password.length() >= 6) {
                    DataBase::getDatabase().createAccount(login, password);
                    returnMessage(sender, "message",
                                  "Account created succesfully");
                } else {
                    returnError(
                        sender,
                        "Password must be at least 6 characters length");
                }
            } else {
                returnError(sender,
                            "Login must be at least 6 characters length");
            }
        } else {
            returnError(sender, "This name is already in use.");
        }
    }
    if (type == "login") {
        QString login = array[0].toString();
        QString password = array[1].toString();
        if (login.length() >= 6) {
            if (DataBase::getDatabase().accountExist(login)) {
                QString realPassword =
                    DataBase::getDatabase().getPassword(login);
                if (password == realPassword) {
                    // login
                    qDebug()
                        << "[Auth] password for " << login << " is correct";
                    QString token = generateToken();
                    addAuthorizedAccount(token, login);
                    returnMessage(sender, "message", "Access Granted");
                    returnMessage(sender, "tokenTransfer", token);
                } else {
                    qDebug() << "[Auth Error] password for " << login
                             << " is incorret";
                    returnError(sender, "Wrong password");
                }
            }
        } else {
            returnError(sender, "Login must be at least 6 characters length");
        }
    }
    if (type == "updateToken") { updateTokenTime(array[0].toString()); }
    if (type == "logOff") { logOff(array[0].toString()); }
    if (type == "addFriend") {
        QString token = array[0].toString();
        QString friendName = array[1].toString();
        FriendsManager* frm = new FriendsManager;
        frm->addFriend(token, friendName);
        delete frm;
    }
    if (type == "removeFriend") {
        QString token = array[0].toString();
        QString friendName = array[1].toString();
        FriendsManager* frm = new FriendsManager;
        frm->removeFriend(token, friendName);
        delete frm;
    }
    if (type == "getFriendsList") {
        QString token = array[0].toString();
        FriendsManager* frm = new FriendsManager;
        QString msg = frm->getFriends(token);
        sendToClient(sender, msg);
        delete frm;
    }
}

void AuthServer::sendToClient(QHostAddress targetIp, QString msg) {
    returnSocket = new QUdpSocket(this);
    returnSocket->bind(targetIp, getPort() - 1);
    QByteArray Data;
    Data.append(msg);
    returnSocket->writeDatagram(Data, targetIp, getPort() - 1);
}

int AuthServer::getTimeOut() const { return timeOut; }
void AuthServer::setTimeOut(int value) { timeOut = value; }

void AuthServer::updateTokenTime(QString token) {
    for (int i = 0; i < authUsers.size(); ++i) {
        if (authUsers.at(i).getToken() == token) {
            AuthorizedUser* aut = new AuthorizedUser;
            aut->setName(authUsers.at(i).getName());
            aut->setTime(0);
            aut->setToken(authUsers.at(i).getToken());

            authUsers.replace(i, *aut);
            delete aut;
        }
    }
}

void AuthServer::logOff(QString token) {
    for (int i = 0; i <= authUsers.size(); i++) {
        if (authUsers.at(i).getToken() == token) { authUsers.removeAt(i); }
    }
}

QString AuthServer::returnNameFromToken(QString token) {
    for (const AuthorizedUser& au : authUsers) {
        if (au.getToken() == token) { return au.getName(); }
    }
    return "error";
}

quint16 AuthServer::getPort() const { return port; }
void AuthServer::setPort(quint16 value) { port = value; }

QString AuthServer::generateToken() {
    // TODO secure token google ~ Rafał Pokrywka
    QString token;
    for (int i = 1; i <= 16; i++) {
        int liczba = (std::rand() % 10);
        token.append(QString::number(liczba));
    }
    return token;
}

void AuthServer::removeTimeOutHashes() {
    for (int i = 0; i < authUsers.size(); i++) {
        if (authUsers.at(i).getTime() >= getTimeOut()) {
            authUsers.removeAt(i);
        }
    }

    qDebug() << authUsers.size() << "clients online";
}

void AuthServer::addOneMinToHashes() {
    for (int i = 0; i < authUsers.size(); i++) {
        AuthorizedUser* au = new AuthorizedUser;
        au->setName(authUsers.at(i).getName());

        au->setTime(authUsers.at(i).getTime() + 1);

        au->setToken(authUsers.at(i).getToken());
        authUsers.replace(i, *au);
        delete au;
    }
}
