#include "range.h"

Range::Range(AnalogData * emg, int begin, int end) : _begin(begin), _end(end)
{
	double sum = 0;
	for(int it = _begin; it <= _end; it++)
	{
		sum+= emg->signal(it);
	}
}

double Range::level() const
{
	return _level / (_end - _begin);
}