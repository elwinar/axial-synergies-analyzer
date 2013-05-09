#ifndef RECORDWIDGET_H
#define RECORDWIDGET_H

#include <QTabWidget>

#include "utils/record.h"

class RecordWidget : public QTabWidget
{
    Q_OBJECT

public:
    /**
     * Create a widget to manipulate a record
     */
    RecordWidget(QWidget * parent = 0, Record * record = 0);
    
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
};

#endif // RECORDWIDGET_H
