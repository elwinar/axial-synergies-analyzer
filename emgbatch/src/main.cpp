#include <QApplication>
#include <QTextStream>
#include <QFile>
#include <QCoreApplication>
#include <QString>
#include <QStringList>

#include "utils/record.h"
#include "tools/parser.h"
#include "tools/motiondetector.h"
#include "tools/emganalyzer.h"

#define FILE 0
#define FIXED_PROXIMAL 1
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

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    QTextStream out(stdout);
    QString dir =  QCoreApplication::applicationDirPath();
    QFile motionfile(dir + "\\motion-result.csv");
    
    if(motionfile.exists())
    {
        qDebug() << "Found input file (motion-result.csv)";
        
        motionfile.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream motionstream(&motionfile);
        
        QFile emgfile(dir + "\\emg-result.csv");
        emgfile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);
        QTextStream emgstream(&emgfile);
        emgstream << "filename"
            << "," << "TS start"
            << "," << "TS stop"
            << "," << "T1 start"
            << "," << "T1 stop"
            << "," << "T2 start"
            << "," << "T2 stop"
            << "," << "ZW1 TS"
            << "," << "ZW1 T1"
            << "," << "ZW1 T2"
            << "," << "ZW2 TS"
            << "," << "ZW2 T1"
            << "," << "ZW2 T2"
            << "," << "ZW3 TS"
            << "," << "ZW3 T1"
            << "," << "ZW3 T2"
            << "," << "ZW4 TS"
            << "," << "ZW4 T1"
            << "," << "ZW4 T2"
            << "," << "ZW5 TS"
            << "," << "ZW5 T1"
            << "," << "ZW5 T2"
            << "," << "ZW6 TS"
            << "," << "ZW6 T1"
            << "," << "ZW6 T2"
            << "," << "ZW7 TS"
            << "," << "ZW7 T1"
            << "," << "ZW7 T2"
            << "," << "ZW8 TS"
            << "," << "ZW8 T1"
            << "," << "ZW8 T2"
            << "\n";
        
        motionstream.readLine();
        while(!motionstream.atEnd())
        {
            QString buffer = motionstream.readLine();
            QStringList fields = buffer.split(',');
            QFile rfile(fields[FILE]);
            
            if(rfile.exists())
            {
                qDebug() << "Analyzing" << fields[FILE];
                Record * record = Parser::parse(&rfile);
                
                emgstream << fields[FILE];
                EMGAnalyzer emg(record);
                emg.run(fields[BEGIN_TIME].toUInt(), fields[END_TIME].toUInt(), emgstream);
                
                delete record;
            }
            else
            {
                qDebug() << fields[FILE] << "not found";
            }
        }
    }
}
