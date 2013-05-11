#include "angularmotionplot.h"

AngularMotionPlot::AngularMotionPlot(QWidget * parent): QCustomPlot(parent)
{
    _beginLine = new QCPItemStraightLine(this);
    _beginLine->setVisible(false);
    addItem(_beginLine);
    
    _endLine = new QCPItemStraightLine(this);
    addItem(_peakLine);
    _peakLine->setVisible(false);
    
    _peakLine = new QCPItemStraightLine(this);
    addItem(_endLine);
    _endLine->setVisible(false);
    
    xAxis->setVisible(false);
    xAxis->setLabel(tr("Time"));
    xAxis->setRange(1, 100);
    
    yAxis->setVisible(false);
    yAxis->setLabel(tr("Amplitude"));
    yAxis->setRange(0, 180);
    
    yAxis2->setVisible(false);
    yAxis2->setLabel(tr("Speed"));
    yAxis2->setRange(0, 1);
    
    replot();
}

void AngularMotionPlot::drawCurve(QMap<unsigned int, double> data, QPen pen, QCPAxis * xAxis, QCPAxis * yAxis, QString name)
{
    unsigned int o = data.begin().key() - 1;
    QCPGraph * graph = addGraph(xAxis, yAxis);
    graph->setPen(pen);
    graph->setName(name);
    for(QMap<unsigned int, double>::iterator i = data.begin(); i != data.end(); i++)
    {
        if(i.key() != o + 1)
        {
            graph = addGraph(xAxis, yAxis);
            graph->removeFromLegend();
            graph->setPen(pen);
        }
        graph->addData(i.key(), i.value());
        o = i.key();
    }
}


void AngularMotionPlot::drawLine(unsigned int index)
{
    _endLine->setPen(QPen(Qt::green));
    _endLine->point1->setAxes(xAxis, yAxis2);
    _endLine->point1->setCoords(position, 0);
    _endLine->point2->setAxes(xAxis, yAxis2);
    _endLine->point2->setCoords(position, 1);
    _endLine->setVisible(true);
    
    replot();
}
