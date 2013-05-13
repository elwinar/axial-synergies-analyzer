#ifndef RECORDWIDGET_H
#define RECORDWIDGET_H

#include <QTabWidget>

class QSettings;
class MotionDetectorWidget;
class Record;

class RecordWidget : public QTabWidget
{
    Q_OBJECT

public:
    RecordWidget(QWidget * parent = 0);
    
public slots:
    void setRecord(Record * value);
    void setSettings(QSettings * value);
    
signals:
    void recordChanged(Record * record);

protected:
    void initializeMotionDetectorWidget();

private:
    MotionDetectorWidget * _motionDetectorWidget;
    Record * _record;
    QSettings * _settings;
};

#endif // RECORDWIDGET_H
