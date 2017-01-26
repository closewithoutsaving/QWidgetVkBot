#ifndef PARSER_H
#define PARSER_H

#include "request.h"
#include "video.h"
#include "doc.h"
#include "gif.h"

class Parser
{
public:
    Parser();

    void parseMassege(QString message);
};

#endif // PARSER_H
