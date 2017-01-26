#ifndef VARIABLES_H
#define VARIABLES_H

#include <QString>
#include <QObject>

class Variables
{
public:
    Variables();

    static QString token;

    static int getRandom();
};

#endif // VARIABLES_H
