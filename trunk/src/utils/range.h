#ifndef RANGE_H
#define RANGE_H

#include <QMap>

#include "analogdata.h"

/**
 * Represents a portion of an emg record.
 */
class Range
{
public:
	/**
	 * Creates a Range in the EMG map between position begin and position end. The level is calculated from EMG.
	 */
	Range(AnalogData * emg, int begin, int end);
	
	/**
	 * @return the current level value, corresponding to the mean signal within the range
	 */
	double level() const;
	
private:
	int _begin;
	int _end;
	double _level;
};

#endif // RANGE_H
