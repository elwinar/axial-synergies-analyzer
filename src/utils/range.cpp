#include "range.h"

Range::Range(QMap * emg, int begin, int end)
{
	_begin = begin;
	_end = end;
	double sum = 0;
	for(int i = _begin; i <= _end; i++)
	{
		sum+= emg->value(i);
	}
	_level = sum / (_end - _begin);
}

double Range::air(Range * baseRange)
{
	return _level - baseRange->level();
}

double Range::level()
{
	return _level;
}