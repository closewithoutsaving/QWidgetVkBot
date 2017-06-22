#include "variables.h"

Variables::Variables()
{

}

int Variables::getRandom()
{
    // random number between low and high
    return qrand() % ((20000 + 2) - 2) + 2;
}

QString Variables::token = "";
