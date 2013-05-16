#include "analogdata.h"

#include <QtGlobal>

AnalogData::AnalogData()
{
};

AnalogData::~AnalogData()
{
}

unsigned int AnalogData::duration() const
{
    return _signals.end().key();
}

bool AnalogData::exists(unsigned int time) const
{
    return _signals.contains(time);
}

double AnalogData::signal(unsigned int time) const
{
    Q_ASSERT(exists(time));
    return _signals.value(time);
}
void AnalogData::setSignal(unsigned int time, double signal)
{
    _signals.insert(time, signal);
}
