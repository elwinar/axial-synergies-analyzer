#include "range.h"

Range::Range(QMap<unsigned int, double> * emg, int begin, int end) : _begin(begin), _end(end)
{
	double sum = 0;
	for(int i = _begin; i <= _end; i++)
	{
		sum+= emg->value(i);
	}
	_level = sum / (_end - _begin);
}

double Range::level() const
{
	return _level;
}