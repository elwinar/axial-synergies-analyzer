#ifndef MOTION_DETECTOR_WIDGET_H
#define MOTION_DETECTOR_WIDGET_H

#include <QPair>
#include <QString>
#include <QWidget>

#include "tools/motiondetector.h"

class AngleSelector;
class AngularMotionPlot;
class QPushButton;
class QSpinBox;
class QVBoxLayout;
class Record;

class MotionDetectorWidget : public QWidget
{
    Q_OBJECT
    
public:
    MotionDetectorWidget(QWidget * parent = 0);
    
    Record * record() const;
    
public slots:
    void run();
    void save();
    void setRecord(Record * record);
    void setDefaultAngle(QPair<QString, QString> fixed, QPair<QString, QString> mobile);
    
protected slots:
    void onBeginSpinBoxValueChanged(int value);
    void onEndSpinBoxValueChanged(int value);
    void onPeakSpinBoxValueChanged(int value);

signals:
    void recordChanged(Record * record);
    
private:
    AngleSelector * _angleSelector;
    QSpinBox * _beginSpinBox;
    QSpinBox * _endSpinBox;
    QPair<QString, QString> _fixedDefault;
    QVBoxLayout * _layout;
    QPair<QString, QString> _mobileDefault;
    MotionDetector _motionDetector;
    QSpinBox * _peakSpinBox;
    AngularMotionPlot * _plot;
    Record * _record;
    QPushButton * _saveButton;
};

#endif // MOTION_DETECTOR_WIDGET_H
