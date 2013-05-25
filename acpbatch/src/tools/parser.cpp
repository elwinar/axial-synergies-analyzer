#include "parser.h"

#include <QDebug>
#include <QFile>
#include <QString>
#include <QStringList>
#include <QTextStream>
#include <QVector>

#include "utils/record.h"
#include "utils/analogdata.h"

#include <cassert>

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
    QVector<QString> markersLabels;
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
    buffer = stream.readLine();
    QStringList frequencyLine = buffer.split('.');
    record->setMarkersFrequency(frequencyLine[0].toUInt());
    
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
        markersLabels.append(buffer.mid(start, end - start));
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
    markers.resize(markersLabels.size());
    unsigned int markersTime = 0;
    buffer = stream.readLine();
    while(!buffer.isEmpty())
    {
        QStringList fields = buffer.split(',');
        markersTime = fields[0].toUInt();
        for(int i = 0; i < markersLabels.size(); i++)
        {
            if(!fields[1 + i*3].isEmpty())
            {
                markers[i].setPoint(markersTime, Point(fields[1 + i*3].toDouble(), fields[2 + i*3].toDouble(), fields[3 + i*3].toDouble()));
            }
        }
        buffer = stream.readLine();
    }
    
    /*
     * set the duration of the record
     */
    record->setMarkersDuration(markersTime);
    
    /*
     * foreach marker
     *   add the marker to the record
     */
    for(int i = 0; i < markers.size(); i++)
    {
        record->setMarker(markersLabels[i], markers[i]);
    }
    
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
    buffer = stream.readLine();
    frequencyLine = buffer.split('.');
    record->setAnalogdatasFrequency(frequencyLine[0].toUInt());
    
    /*
     * read one line
     * initialize the reading positions
     * while not at the last occurence of ","
     *   add the found string to labels
     */
    
    QVector<QString> analogLabels;
    buffer = stream.readLine();
	QStringList fields = buffer.split(',');
	for(int it = 1; it < fields.size(); it++)
    {
		analogLabels.append(fields[it]);
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
    QVector<AnalogData> analogDatas;
    analogDatas.resize(analogLabels.size());
    unsigned int analogTime = 0;
    buffer = stream.readLine();
    while(!buffer.isEmpty())
    {
		QStringList fields = buffer.split(',');
        analogTime = fields[0].toUInt();
        for(int i = 0; i < analogLabels.size(); i++)
        {
            if(!fields[1 + i].isEmpty())
            {
				analogDatas[i].setSignal(analogTime, fields[1 + i].toDouble());
            }
        }
        buffer = stream.readLine();
    }
    
    /*
     * set the duration of the record
     */
    record->setAnalogdatasDuration(analogTime);
    
    /*
     * foreach marker
     *   add the marker to the record
     */
    for(int i = 0; i < analogDatas.size(); i++)
    {
        record->setAnalogdata(analogLabels[i], analogDatas[i]);
    }
    
    /*
     * return the record
     */
    return record;
}
