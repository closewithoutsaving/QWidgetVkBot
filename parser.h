#ifndef PARSER_H
#define PARSER_H

#include "request.h"
#include "VkModules/video.h"
#include "VkModules/doc.h"
#include "VkModules/gif.h"

class Parser
{
public:
    Parser();
    void parseMassege(QString message);
};

#endif // PARSER_H
