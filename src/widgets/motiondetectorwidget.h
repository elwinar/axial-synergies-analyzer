#ifndef MOTION_DETECTOR_WIDGET_H
#define MOTION_DETECTOR_WIDGET_H

#include <QWidget>

#include "tools/motiondetector.h"

class QComboBox;
class QCustomPlot;
class QGridLayout;
class QLabel;
class QPushButton;
class Record;

class MotionDetectorWidget : public QWidget
{
    Q_OBJECT
    
public:
    /**
     * Create a motion detector widget
     */
    MotionDetectorWidget(QWidget * parent = 0, Record * record = 0);
    ~MotionDetectorWidget();
    
protected:
    /**
     * Initialize the widget's buttons
     */
    void initializeButtons();
    
    /**
     * Initialize the widget's plot
     */
    void initializePlot();
    
    /**
     * Initialize the widget's selectors
     */
    void initializeSelectors();
    
public slots:
    /**
     * Update the record pointer of the widget
     */
    void setRecord(Record * record);

signals:
    /**
     * Emitted whenever the record pointer of the widget change
     */
    void recordChanged(Record * record);
    
private:
    MotionDetector detector;
    QComboBox * _distalFixedComboBox;
    QComboBox * _distalMobileComboBox;
    QLabel * _fixedLabel;
    QGridLayout * _layout;
    QLabel * _mobileLabel;
    QCustomPlot * _plot;
    QComboBox * _proximalFixedComboBox;
    QComboBox * _proximalMobileComboBox;
    Record * _record;
    QPushButton * _runButton;
    QPushButton * _saveButton;
};

#endif // MOTION_DETECTOR_WIDGET_H
