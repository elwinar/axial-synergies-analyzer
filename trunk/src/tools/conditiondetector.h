#ifndef CONDITION_DETECTOR_H
#define CONDITION_DETECTOR_H

#include <QString>

class Record;

/**
 * A tool which detects the experimental condition of a given record.
 */
class ConditionDetector
{
public:
    /**
	 * Detects the experimental condition.
     * @return the detected condition, or an explicit string if none has been detected.
     */
	static QString detect(Record * record);	
};

#endif // CONDITION_DETECTOR_H