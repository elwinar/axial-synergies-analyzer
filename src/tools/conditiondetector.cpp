#include "conditiondetector.h"

#include <QPair>

#include "utils/point.h"
#include "utils/record.h"
#include "utils/vector.h"

QString ConditionDetector::detect(Record * record)
{
	QString condition;
	
	// if none of this markers is contained in the record
	if(!record->contains("BALAVD") && !record->contains("BALAVG") && !record->contains("BALARD") &&	!record->contains("BALARG"))
	{
		condition = "STD";
	}
	else
	{
		Point proximal;
		Point distal;
		bool diagonalFound = false;
		
		for(unsigned int duration = 1; duration <= record->duration(); duration ++)
		{
			// if the first diagonal is set at given duration.
			if(record->marker("BALAVD").exists(duration) && record->marker("BALARG").exists(duration))
			{
				proximal = record->marker("BALAVD").point(duration);
				distal = record->marker("BALARG").point(duration);
				diagonalFound = true;
				break;
			}
			// if the second diagonal is set at given duration.
			if(record->marker("BALAVG").exists(duration) && record->marker("BALARD").exists(duration))
			{
				proximal = record->marker("BALAVG").point(duration);
				distal = record->marker("BALARD").point(duration);
				diagonalFound = true;
				break;
			}
		}
		
		if(diagonalFound)
		{
			Vector diagonal(proximal, distal);
			QPair<double, double> ankBoard(550, 620);
			QPair<double, double> kneBoard(650, 720);
			
			if(diagonal.length() >= ankBoard.first && diagonal.length() <= ankBoard.second)
			{
				condition = "ANK";
			}
			else if(diagonal.length() >= kneBoard.first && diagonal.length() <= kneBoard.second)
			{
				condition = "KNE";
			}
			else
			{
				condition = "INCORRECT DIAGONAL SIZE";
			}
		}
		else
		{
			condition = "NO DIAGONAL FOUND";
		}
	}
	return condition;
}