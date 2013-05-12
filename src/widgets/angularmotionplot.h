#ifndef ANGULAR_MOTION_PLOT_H
#define ANGULAR_MOTION_PLOT_H

#include "libs/qcustomplot.h"

class AngularMotionPlot : public QCustomPlot
{
    Q_OBJECT
    
public:
    AngularMotionPlot(QWidget * parent = 0);
    
public slots:
    void clear();
    void setAmplitudeCurve(QMap<unsigned int, double> value);
    void setBeginLine(unsigned int value);
    void setEndLine(unsigned int value);
    void setPeakLine(unsigned int value);
    void setRange(unsigned int start, unsigned int stop);
    void setSpeedCurve(QMap<unsigned int, double> value);
    
protected:
    
signals:
    
private:
    QCPAxis * _timeAxis;
    QCPAxis * _amplitudeAxis;
    QCPAxis * _speedAxis;
    
    QCPItemStraightLine * _beginLine;
    QCPItemStraightLine * _endLine;
    QCPItemStraightLine * _peakLine;
    
    void drawCurve(QMap<unsigned int, double> data, QString name, QPen pen, QCPAxis * x, QCPAxis * y);
    void moveLine(QCPItemStraightLine * line, unsigned int index, QPen pen, QCPAxis * x, QCPAxis * y);
};

#endif // ANGULAR_MOTION_PLOT_H
