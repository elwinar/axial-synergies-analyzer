#ifndef ANGULAR_MOTION_PLOT_H
#define ANGULAR_MOTION_PLOT_H

#include "libs/qcustomplot.h"

class AngularMotionPlot : public QCustomPlot
{
    Q_OBJECT
    
public:
    AngularMotionPlot(QWidget * parent = 0);
    
public slots:
    void setRange(unsigned int start, unsigned int stop);
    void setAmplitudes(QMap<unsigned int, double> value);
    void setSpeeds(QMap<unsigned int, double> value);
    void setBegin(unsigned int value);
    void setPeak(unsigned int value);
    void setEnd(unsigned int value);
    
protected:
    
signals:
    
private:
    QCPItemStraightLine * _beginLine;
    QCPItemStraightLine * _endLine;
    QCPItemStraightLine * _peakLine;
    
    void drawCurve(QMap<unsigned int, double> data, QPen pen, QCPAxis * xAxis, QCPAxis * yAxis, QString name);
    void drawLine(unsigned int index);
};

#endif // ANGULAR_MOTION_PLOT_H
