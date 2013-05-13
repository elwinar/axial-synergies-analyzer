#include "angularmotionplot.h"

#include <QDebug>

AngularMotionPlot::AngularMotionPlot(QWidget * parent): QCustomPlot(parent)
{
    /*
     * Initialize the items
     */
    _beginLine = new QCPItemStraightLine(this);
    _beginLine->setVisible(false);
    addItem(_beginLine);
    
    _endLine = new QCPItemStraightLine(this);
    _endLine->setVisible(false);
    addItem(_endLine);
    
    _peakLine = new QCPItemStraightLine(this);
    _peakLine->setVisible(false);
    addItem(_peakLine);
    
    /*
     * Initialize the axis
     */
    _timeAxis = xAxis;
    _timeAxis->setVisible(false);
    _timeAxis->setLabel(tr("Time"));
    
    _amplitudeAxis = yAxis;
    _amplitudeAxis->setVisible(false);
    _amplitudeAxis->setLabel(tr("Amplitude"));
    _amplitudeAxis->setRange(0, 180);
    
    _speedAxis = yAxis2;
    _speedAxis->setVisible(false);
    _speedAxis->setLabel(tr("Speed"));
    
    /*
     * Update the graphic
     */
    replot();
}

void AngularMotionPlot::clear()
{
    clearGraphs();
    
    _timeAxis->setVisible(false);
    _amplitudeAxis->setVisible(false);
    _speedAxis->setVisible(false);
    
    _beginLine->setVisible(false);
    _peakLine->setVisible(false);
    _endLine->setVisible(false);
    
    replot();
}

void AngularMotionPlot::drawCurve(QMap<unsigned int, double> data, QString name, QPen pen, QCPAxis * keyAxis, QCPAxis * valueAxis, bool rescaleValueAxis)
{
    /* 
     * Initialize the "old" key
     */
    unsigned int old = data.begin().key() - 1;
    
    /*
     * Create the first graph, who will be the only one to be displayed on the legend
     */
    QCPGraph * graph = addGraph(keyAxis, valueAxis);
    graph->setPen(pen);
    graph->setName(name);
    
    /*
     * Iterate throught the data
     */
    unsigned int max = data.begin().key();
    for(QMap<unsigned int, double>::iterator it = data.begin(); it != data.end(); it++)
    {
        /*
         * If the current key is not directly following the old, there is a gap in the data, so we must create a new graph to display the chunk
         */
        if(it.key() != old + 1)
        {
            graph = addGraph(keyAxis, valueAxis);
            graph->removeFromLegend();
            graph->setPen(pen);
        }
        
        /*
         * Add the current point to the graph
         */
        graph->addData(it.key(), it.value());
        
        /*
         * Update max value
         */
        if(data.value(max) < it.value())
        {
            max = it.key();
        }
        
        /* 
         * Update the key
         */
        old = it.key();
    }
    
    /*
     * If requested, rescale the value axis
     */
    if(rescaleValueAxis == true)
    {
        valueAxis->setRange(0, data.value(max) * 1.05);
    }
    
    /*
     * Update the graphic
     */
    replot();
}


void AngularMotionPlot::moveLine(QCPItemStraightLine * line, unsigned int index, QPen pen, QCPAxis * x, QCPAxis * y)
{
    line->setPen(pen);
    
    /*
     * Move the given item to the chosen index
     */
    line->point1->setAxes(x, y);
    line->point1->setCoords(index, 0);
    line->point2->setAxes(x, y);
    line->point2->setCoords(index, 1);
    
    /*
     * Set it visible
     */
    line->setVisible(true);
    
    /*
     * Update the graphic
     */
    replot();
}

void AngularMotionPlot::setAmplitudeCurve(QMap<unsigned int, double> value)
{
    _timeAxis->setVisible(true);
    _amplitudeAxis->setVisible(true);
    drawCurve(value, "Amplitude", QPen(Qt::red), _timeAxis, _amplitudeAxis);
}

void AngularMotionPlot::setBeginLine(unsigned int value)
{
    moveLine(_beginLine, value, QPen(Qt::green), _timeAxis, _speedAxis);
}

void AngularMotionPlot::setEndLine(unsigned int value)
{
    moveLine(_endLine, value, QPen(Qt::green), _timeAxis, _speedAxis);
}

void AngularMotionPlot::setPeakLine(unsigned int value)
{
    moveLine(_peakLine, value, QPen(Qt::green), _timeAxis, _speedAxis);
}

void AngularMotionPlot::setRange(unsigned int start, unsigned int stop)
{
    _timeAxis->setRange(start, stop);
}

void AngularMotionPlot::setSpeedCurve(QMap<unsigned int, double> value)
{
    _timeAxis->setVisible(true);
    _speedAxis->setVisible(true);
    drawCurve(value, "Speed", QPen(Qt::blue), _timeAxis, _speedAxis, true);
}
