#ifndef PARSER_H
#define PARSER_H

class QFile;
class Record;

/**
 * A parser able to load VICON files.
 */
class Parser
{
public:
    /**
     * Parse a file to get a record
     */
    static Record * parse(QFile * file);
	
    /**
     * Parse a file to get a record of analog datas
     */
	static Record * analogSignal(QFile * file);
};

#endif // PARSER_H
