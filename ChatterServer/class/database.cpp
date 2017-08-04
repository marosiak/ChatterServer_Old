#include "database.h"

DataBase::DataBase() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("accounts");
    if (!db.open()) { qDebug() << "ERROR WHILE OPENING DB"; }
    execute(
        "create table accounts (login varchar(20), password "
        "varchar(45))");
}

DataBase::~DataBase() { db.close(); }

void DataBase::createAccount(QString login, QString password) {
    if (accountExist(login) == false) {
        QString cmd = QString(
                          "insert into accounts "
                          "values('%1', '%2')")
                          .arg(login)
                          .arg(password);
        execute(cmd);
    }
}

bool DataBase::accountExist(const QString& login) const {
    QSqlQuery query;
    QString cmd =
        QString("SELECT * FROM accounts WHERE login=\"%1\"").arg(login);
    query.exec(cmd);
    while (query.next()) {
        if (query.value(0).toString() == login) {
            // exist
            return true;
        }
    }
    return false;
}

void DataBase::createFriendListTable(QString name) {
    QString cmd =
        QString("create table if not exists %1 (login varchar(20))").arg(name);
    execute(cmd);
}

void DataBase::insertIntoFriendListTable(QString targetTable, QString value) {
    QString cmd =
        QString("insert into %1 values('%2')").arg(targetTable).arg(value);
    execute(cmd);
}

bool DataBase::checkIfValueIsInTable(QString table, QString value) {
    QSqlQuery query;
    QString cmd =
        QString("SELECT * FROM %1 WHERE login=\"%2\"").arg(table).arg(value);
    query.exec(cmd);
    while (query.next()) {
        if (query.value(0).toString() == value) {
            // exist
            return true;
        }
    }
    return false;
}

QString DataBase::getPassword(QString login) {
    QSqlQuery query;
    QString cmd =
        QString("SELECT * FROM accounts WHERE login=\"%1\"").arg(login);
    query.exec(cmd);
    while (query.next()) {
        if (query.value(0).toString() == login) {
            // exist
            return query.value(1).toString();
        }
    }
    qDebug() << "Error while getting password of  " << login;
    return "error";  // error
}

QString DataBase::getRecords(QString table) {
    QSqlQuery query;
    QString cmd = QString("SELECT * FROM %1").arg(table);
    query.exec(cmd);
    QString output;
    while (query.next()) {
        QString p = query.value(0).toString();
        QString f = QString("\"%1\",").arg(p);
        output.append(f);
    }
    QString newOut;
    for (int i = 0; i < output.length() - 1; i++) {  // remove last char ,
        newOut.append(output[i]);
    }
    return newOut;
}

void DataBase::removeRecord(QString table, QString value) {
    QString cmd =
        QString("DELETE FROM %1 WHERE login=\"%2\"").arg(table).arg(value);
    execute(cmd);
}

void DataBase::execute(QString cmd) {
    QSqlQuery query;
    query.exec(cmd);
}
