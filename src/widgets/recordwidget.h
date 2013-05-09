#ifndef RECORDWIDGET_H
#define RECORDWIDGET_H

#include <QTabWidget>

class Record;
class MotionDetectorWidget;

class RecordWidget : public QTabWidget
{
    Q_OBJECT

public:
    /**
     * Create a widget to manipulate a record
     */
    RecordWidget(QWidget * parent = 0, Record * record = 0);

protected:
    /**
     * Initialize the motion detector widget of the widget
     */
    void initializeMotionDetectorWidget();
    
public slots:
    /**
     * Update the record pointer of the widget
     */
    void setRecord(Record * record);
    
signals:
    /**
     * Emitted when the record pointer of the widget change
     */
    void recordChanged(Record * record);

private:
    Record * _record;
    
    MotionDetectorWidget * _motionDetectorWidget;
};

#endif // RECORDWIDGET_H
