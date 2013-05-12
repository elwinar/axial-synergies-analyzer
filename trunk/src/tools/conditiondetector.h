#ifndef CONDITION_DETECTOR_H
#define CONDITION_DETECTOR_H

#include <QString>

class Record;

class ConditionDetector
{
public:
	ConditionDetector(Record * record);
	void detectCondition();
	QString condition();

private:
	QString _condition;
	Record * _record;

};

#endif // CONDITION_DETECTOR_H