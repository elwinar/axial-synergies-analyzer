#include "recordwidget.h"

#include "motiondetectorwidget.h"

RecordWidget::RecordWidget(QWidget *parent) : QTabWidget(parent)
{
    addTab(new MotionDetectorWidget(), tr("Motion Detection"));
}
