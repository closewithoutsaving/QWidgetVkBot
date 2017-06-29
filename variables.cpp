#include "variables.h"

Variables::Variables()
{

}

int Variables::getRandom()
{
    return qrand() % ((20000 + 2) - 2) + 2;
}

QString Variables::token = "";
