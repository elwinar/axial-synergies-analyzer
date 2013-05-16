#include "parser.h"

#include <QDebug>
#include <QFile>
#include <QString>
#include <QStringList>
#include <QTextStream>
#include <QVector>

#include "utils/record.h"
#include "utils/analogdata.h"

Record * Parser::parse(QFile * file)
{
    /*
     * open the file in read-only mode
     * create a text stream to read it
     * create a buffer
     * create vars to fill
     */
    file->open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream stream(file);
    QString buffer;
    Record * record = new Record();
    QVector<QString> labels;
    QVector<Marker> markers;
    
    record->setFilename(file->fileName());
    
    /*
     * read the name of the record
     */
    record->setName(stream.readLine());
    
    /*
     * read each line while not meeting the label TRAJECTORIES to skip metadata
     */
    do
    {
        buffer = stream.readLine();
    } while(buffer.compare("TRAJECTORIES"));
    
    /*
     * skip the frequency of capture
     */
    stream.readLine();
    
    /*
     * read one line
     * initialize the reading positions
     * while not at the end of the line
     *   compute next label start position
     *   compute next label end position
     *   add it to labels' list
     */
    buffer = stream.readLine();
    int start = 0;
    int end = 0;
    while(end != -1)
    {
        start = buffer.indexOf(':', end) + 1;
        end = buffer.indexOf(',', start);
        labels.append(buffer.mid(start, end - start));
    }
    
    /*
     * skip the fields details
     */
    stream.readLine();
    
    /*
     * resize markers' list to fit number of detected markers
     * read first line
     * while line isn't empty
     *   split it around ','
     *   retrive the time label
     *   foreach  label
     *     if there is data for the labels' marker
     *       add the new point to the marker
     *   read next line
     */
    markers.resize(labels.size());
    unsigned int time = 0;
    buffer = stream.readLine();
    while(!buffer.isEmpty())
    {
	QStringList fields = buffer.split(',');
	time = fields[0].toUInt();
        for(int i = 0; i < labels.size(); i++)
        {
            if(!fields[1 + i*3].isEmpty())
            {
		markers[i].setPoint(time, Point(fields[1 + i*3].toDouble(), fields[2 + i*3].toDouble(), fields[3 + i*3].toDouble()));
            }
        }
        buffer = stream.readLine();
    }
    
    /*
     * set the duration of the record
     */
    record->setDuration(time);
    
    /*
     * foreach marker
     *   add the marker to the record
     */
    for(int i = 0; i < markers.size(); i++)
    {
	record->setMarker(labels[i], markers[i]);
    }
    
    /*
     * return the record
     */
    return record;
}

Record * Parser::analogSignal(QFile * file)
{
    /*
     * open the file in read-only mode
     * create a text stream to read it
     * create a buffer
     * create vars to fill
     */
    file->open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream stream(file);
    QString buffer;
    Record * record = new Record();
    QVector<QString> labels;
    QVector<AnalogData> analogDatas;
    
    record->setFilename(file->fileName());
    
    /*
     * read the name of the record
     */
    record->setName(stream.readLine());
    
    /*
     * read each line while not meeting the label ANALOG to skip metadata
     */
    do
    {
        buffer = stream.readLine();
    } while(buffer.compare("ANALOG"));
    
    /*
     * skip the frequency of capture
     */
    stream.readLine();
    
    /*
     * read one line
     * initialize the reading positions
     * while not at the last occurence of ","
     *   add the found string to labels
     */
    buffer = stream.readLine();
	QStringList fields = buffer.split(',');
	for(int it = 1; it <= buffer.lastIndexOf(','); it++)
    {
		labels.append(fields[it]);
    }
	
    /*
     * skip the units line
     */
    stream.readLine();
    
    /*
     * resize analog datas' list to fit number of detected labels
     * read first line
     * while line isn't empty
     *   split it around ','
     *   retrive the time label
     *   foreach  label
     *     if there is an analog data
     *       add it to the analogDatas array
     *   read next line
     */
    analogDatas.resize(labels.size());
    unsigned int time = 0;
    buffer = stream.readLine();
    while(!buffer.isEmpty())
    {
		fields = buffer.split(',');
		time = fields[0].toUInt();
        for(int it = 1; it <= labels.size(); it++)
        {
            if(!fields[it].isEmpty())
            {
				analogDatas[it].setSignal(time, fields[it].toDouble());
            }
        }
        buffer = stream.readLine();
    }
}
