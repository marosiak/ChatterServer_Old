#ifndef AUTHORIZEDUSER_H
#define AUTHORIZEDUSER_H

#include <QString>

class AuthorizedUser {
public:
    QString getToken() const;
    void setToken(const QString& value);

    QString getName() const;
    void setName(const QString& value);

    short getTime() const;
    void setTime(short value);

private:
    QString token, name;
    short int time;
};

#endif  // AUTHORIZEDUSER_H
