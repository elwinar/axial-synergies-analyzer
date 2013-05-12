#include "conditiondetector.h"

#include <QPair>

#include "utils/point.h"
#include "utils/record.h"
#include "utils/vector.h"

ConditionDetector::ConditionDetector(Record * record)
{
	_record = record;
}

void ConditionDetector::detectCondition()
{
	// if none of this markers is contained in the record
	if(!_record->contains("BALAVD") && !_record->contains("BALAVG") &&	!_record->contains("BALARD") &&	!_record->contains("BALAVRG"))
	{
		_condition = "STD";
	}
	else
	{
		Point proximal;
		Point distal;
		bool points_are_init = false;
		
		for(unsigned int duration = 1; duration <= _record->duration(); duration ++)
		{
			// if the first diagonal is set at given duration.
			if(_record->marker("BALAVD").exists(duration) && _record->marker("BALARG").exists(duration))
			{
				proximal = _record->marker("BALAVD").point(duration);
				distal = _record->marker("BALARG").point(duration);
				points_are_init = true;
				break;
			}
			// if the second diagonal is set at given duration.
			if(_record->marker("BALAVG").exists(duration) && _record->marker("BALARD").exists(duration))
			{
				proximal = _record->marker("BALAVG").point(duration);
				distal = _record->marker("BALARD").point(duration);
				points_are_init = true;
				break;
			}
		}
		
		if(!points_are_init)
		{
			_condition = "NO DIAGONAL";
		}
		else
		{
			Vector diagonal(proximal, distal);
			QPair<double, double> ankBoard(550, 620);
			QPair<double, double> kneBoard(650, 720);
			
			if(diagonal.length() >= ankBoard.first && diagonal.length() <= ankBoard.second)
			{
				_condition = "ANK";
			}
			else if(diagonal.length() >= kneBoard.first && diagonal.length() <= kneBoard.second)
			{
				_condition = "KNE";
			}
			else
			{
				_condition = "FALSE DIAGONAL";
			}
		}
	}
}

QString ConditionDetector::condition()
{
	return _condition;
}