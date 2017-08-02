#include "database.h"

DataBase::DataBase(){
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("accounts");
    if (!db.open()) {
        qDebug() << "ERROR WHILE OPENING DB";
    }
    execute("create table accounts (login varchar(20), password varchar(45))");

}

DataBase::~DataBase(){
    db.close();
}

void DataBase::createAccount(QString login, QString password) {
    if (accountExist(login) == false) {
        QString cmd = QString("insert into accounts values('%1', '%2')").arg(login).arg(password);
        execute(cmd);
    }
}

bool DataBase::accountExist(const QString& login) const {
    QSqlQuery query;
    QString cmd = QString("SELECT * FROM accounts WHERE login=\"%1\"").arg(login);
    query.exec(cmd);
        while (query.next()){
            if(query.value(0).toString() == login){
                // exist
                qDebug() << "[Database] "<<login<<" account exist.";
                return true;
            }
        }
        return false;
}

QString DataBase::getPassword(QString login) {
    QSqlQuery query;
    QString cmd = QString("SELECT * FROM accounts WHERE login=\"%1\"").arg(login);
    query.exec(cmd);
        while (query.next()){
            if(query.value(0).toString() == login){
                // exist
                return query.value(1).toString();
            }
        }
        qDebug() << "Error while getting password of  "<<login;
        return "error"; // error
}

void DataBase::execute(QString cmd) {
    QSqlQuery query;
    query.exec(cmd);
}
