#ifndef RECORDWIDGET_H
#define RECORDWIDGET_H

#include <QTabWidget>

class Record;
class MotionDetectorWidget;

class RecordWidget : public QTabWidget
{
    Q_OBJECT

public:
    RecordWidget(Record * record = 0, QWidget * parent = 0);
    
public slots:
    void setRecord(Record * record);
    
signals:
    void recordChanged(Record * record);

protected:
    void initializeMotionDetectorWidget();

private:
    MotionDetectorWidget * _motionDetectorWidget;
    Record * _record;
};

#endif // RECORDWIDGET_H
