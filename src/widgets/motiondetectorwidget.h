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

/**
 * The motion detector widget provide graphical user interface for the motion detector tool. It embed an angle selector, a plotting widget, an user-correction mechanism that uses spinboxes, and a save button.
 */
class MotionDetectorWidget : public QWidget
{
    Q_OBJECT
    
public:
    MotionDetectorWidget(QWidget * parent = 0);
    
    /**
     * Return a pointer on the current record of the motion detector
     */
    Record * record() const;
    
public slots:
    /**
     * Run the detector using the currently selected angle
     */
    void run();
    
    /**
     * Save the results of the detection into a file.
     * FIXME Saving is actually hard-coded into a static file. Needs to change this as soon as database is implemented
     */
    void save();
    
    /**
     * Set the pointer of the current record
     */
    void setRecord(Record * record);
    
    /**
     * Set the default selected angle
     */
    void setDefaultAngle(QPair<QString, QString> fixed, QPair<QString, QString> mobile);
    
protected slots:
    /**
     * Internal behavior of the detector when the begin spinbox's value change
     */
    void onBeginSpinBoxValueChange(int value);
    
    /**
     * Internal behavior of the detector when the end spinbox's value change
     */
    void onEndSpinBoxValueChange(int value);
    
    /**
     * Internal behavior of the detector when the peak spinbox's value change
     */
    void onPeakSpinBoxValueChange(int value);

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
