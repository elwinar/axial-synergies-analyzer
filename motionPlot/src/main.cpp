#include <QApplication>
#include <QTextStream>
#include <QFile>
#include <QCoreApplication>
#include <QString>
#include <QStringList>
#include <QSettings>
#include <QFileInfo>
#include <QDir>

#include "utils/record.h"
#include "tools/parser.h"
#include "libs/qcustomplot.h"

#define FILE 0
#define FIXED_PROXIMAL 1
#define CONDITION 1
#define FIXED_DISTAL 2
#define MOBILE_PROXIMAL 3
#define MOBILE_DISTAL 4
#define DURATION 5
#define AMPLITUDE 6
#define SPEED 7
#define BEGIN_TIME 8
#define BEGIN_AMPLITUDE 9
#define BEGIN_SPEED 10
#define PEAK_TIME 11
#define PEAK_AMPLITUDE 12
#define PEAK_SPEED 13
#define END_TIME 14
#define END_AMPLITUDE 15
#define END_SPEED 16

struct RecordData
{
	QString subject;
	QString condition;
	int time;
};

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    QTextStream out(stdout);
    QString dir =  QCoreApplication::applicationDirPath();
    QFile motionfile(dir + "\\motion-result.csv");
    QFile conditionfile(dir + "\\condition-result.csv");
    QSettings settings(QApplication::applicationFilePath().append(".ini"), QSettings::IniFormat);
	QVector<QString> subjects;
	QVector<QString> conditions;
	
	QMap<QString, RecordData> records;
    
    if(motionfile.exists() && conditionfile.exists())
    {
        motionfile.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream motionstream(&motionfile);
        
        while(!motionstream.atEnd())
        {
			QString buffer = motionstream.readLine();
            QStringList fields = buffer.split(',');
			QFileInfo info(fields[FILE]);
            
            if(info.exists())
            {
				RecordData d;
				d.subject = info.dir().dirName();
				d.time = fields[BEGIN_TIME].toInt();
				records[fields[FILE]] = d;
				
				if(!subjects.contains(d.subject))
				{
					subjects.push_back(d.subject);
				}
            }
        }
		
		conditionfile.open(QIODevice::ReadOnly | QIODevice::Text);
		QTextStream conditionstream(&conditionfile);
		
		while(!conditionstream.atEnd())
		{
			QString buffer = conditionstream.readLine();
            QStringList fields = buffer.split(',');
			QFileInfo info(fields[FILE]);
			
			if(records.contains(fields[FILE]))
			{
				records[fields[FILE]].condition = fields[CONDITION];
				
				if(!conditions.contains(fields[CONDITION]))
				{
					conditions.push_back(fields[CONDITION]);
				}
			}
		}
    }
	
	for(QVector<QString>::iterator it = subjects.begin(); it != subjects.end(); it++)
	{
		for(QVector<QString>::iterator jt = conditions.begin(); jt != conditions.end(); jt++)
		{
			qDebug() << "[" << *it << *jt << "]";
			QCustomPlot* plot = new QCustomPlot();
			
			for(QMap<QString, RecordData>::iterator kt = records.begin(); kt != records.end(); kt++)
			{
				if(kt->subject == *it && kt->condition == *jt)
				{
					qDebug() << kt.key();
				}
			}
			
			delete plot;
		}
	}
}
