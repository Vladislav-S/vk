#ifndef CRYPT_H
#define CRYPT_H

#include <QObject>
#include <QString>
#include <QDebug>
#include <botan/botan.h>
#include <botan/pipe.h>
#include <botan/aes.h>
#include <botan/filters.h>

class crypt
{
   // Q_OBJECT
public:
    explicit crypt();
    std::string myCrypt(std::string text, std::string log, std::string pas, bool mode);
    std::string genKey(QString str);
signals:

public slots:
};

#endif // CRYPT_H
