#ifndef RANGE_H
#define RANGE_H

#include <QMap>

class Range
{
public:
	Range(QMap * emg, int begin, int end);
	double air(Range * baseRange);
	double level();
	
private:
	int _begin;
	int _end;
	int _level;
};

#endin // RANGE_H
