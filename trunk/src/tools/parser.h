#ifndef PARSER_H
#define PARSER_H

#include <QFile>
#include "utils/record.h"

/**
 * A parser able to load VICON files.
 */
class Parser
{
public:
    static Record * parse(QFile & file);
};

#endif // PARSER_H
