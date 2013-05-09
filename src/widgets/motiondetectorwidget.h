#ifndef MOTION_DETECTOR_WIDGET_H
#define MOTION_DETECTOR_WIDGET_H

#include <QMap>
#include <QPen>
#include <QWidget>
#include "libs/qcustomplot.h"

class QComboBox;
class QCustomPlot;
class QCPItemStraightLine;
class QSpinBox;
class MotionDetector;
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
    
public slots:
    /**
     * Clear the plot from all content
     */
    void clearPlot();
    
    /**
     * Clear the selectors content
     */
    void clearComboBoxes();
    
    void drawGraph(QMap<unsigned int, double> data, QPen pen, QCPAxis * xAxis, QCPAxis * yAxis, QString name);
    
    /**
     * Draw the widget's plot according to the detector's state
     */
    void drawPlot();
    
    /**
     * Draw the widget's motion's lines
     */
    void drawBeginLine(int position);
    void drawPeakLine(int position);
    void drawEndLine(int position);
    
    /**
     * Run the detector, and update the widget according to it's result
     */
    void run();
    
    /**
     * Save the result of the detection
     */
    void save();
    
    /**
     * Update the record pointer of the widget
     */
    void setRecord(Record * record);
    
    /**
     * Setup the comboboxes' contents
     */
    void setupComboBoxes();
    
    /**
     * Setup the spinboxes' range
     */
    void setupSpinBoxes();
    
    /**
     * Setup the plot legends and axis
     */
    void setupPlot();

signals:
    /**
     * Emitted whenever the record pointer of the widget change
     */
    void recordChanged(Record * record);
    
    /**
     * Emitted whenever the detector run, either it found a motion or not
     */
    void detected();
    
private:
    Record * _record;
    MotionDetector * _detector;
    
    QComboBox * _distalFixedComboBox;
    QComboBox * _proximalFixedComboBox;
    
    QComboBox * _distalMobileComboBox;
    QComboBox * _proximalMobileComboBox;
    
    QCustomPlot * _plot;
    
    QSpinBox * _beginSpinBox;
    QSpinBox * _peakSpinBox;
    QSpinBox * _endSpinBox;
    
    QCPItemStraightLine * _beginLine;
    QCPItemStraightLine * _peakLine;
    QCPItemStraightLine * _endLine;
    
    /**
     * Initialize the widget's layout
     */
    void initializeLayout();
};

#endif // MOTION_DETECTOR_WIDGET_H
