#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QString>
#include <QtSql>

class DataBase : public QObject {
    Q_OBJECT

public:
    explicit DataBase(QObject *parent = nullptr);
    void createAccount(QString login, QString password);
    bool accountExist(QString login);
    QString getPassword(QString login);
private:
    void execute(QString cmd);

signals:

public slots:
};

#endif // DATABASE_H
