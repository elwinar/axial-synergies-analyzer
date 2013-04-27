#include "parser.h"

#include <QString>
#include <QStringList>
#include <QTextStream>
#include <QVector>

Record Parser::parse(QFile* file)
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
    Record record;
    QVector<QString> labels;
    QVector<Marker> markers;
    
    /*
     * skip the filename
     */
    stream.readLine();
    
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
    record.setDuration(time);
    
    /*
     * foreach marker
     *   add the marker to the record
     */
    for(unsigned int i = 0; i < markers.size(); i++)
    {
	record.setMarker(labels[i], markers[i]);
    }
    
    /*
     * return the record
     */
    return record;
}
