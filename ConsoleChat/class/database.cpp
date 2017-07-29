#include "database.h"

DataBase::DataBase(QObject *parent) : QObject(parent){
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("accounts");
    if (!db.open()) {
        qDebug() << "ERROR WHILE OPENING DB";
    }
    execute("create table accounts (login varchar(20), password varchar(45))");
}

void DataBase::createAccount(QString login, QString password) {
    QString cmd = QString("insert into accounts values('%1', '%2')").arg(login).arg(password);
    execute(cmd);
}

bool DataBase::accountExist(QString login){
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
        qDebug() << "[Database] Unknow account called "<<login;
        return false;
}

QString DataBase::getPassword(QString login) {
    QSqlQuery query;
    QString cmd = QString("SELECT * FROM accounts WHERE login=\"%1\"").arg(login);
    query.exec(cmd);
        while (query.next()){
            if(query.value(0).toString() == login){
                // exist
                qDebug() << "[Database] "<<login<<" account pass is "<<query.value(1).toString();
                return query.value(1).toString();
            }
        }
        qDebug() << "Error while getting password of  "<<login;
        return "error"; // error
}

void DataBase::execute(QString cmd){
    QSqlQuery query;
    query.exec(cmd);
}
