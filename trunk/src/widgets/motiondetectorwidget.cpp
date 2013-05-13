#include "motiondetectorwidget.h"

#include <QDebug>
#include <QList>
#include <QString>
#include <QVBoxLayout>

#include "tools/motiondetector.h"
#include "utils/record.h"
#include "widgets/angleselector.h"
#include "widgets/angularmotionplot.h"

MotionDetectorWidget::MotionDetectorWidget(QWidget * parent): QWidget(parent)
{
    _layout = new QVBoxLayout();
    setLayout(_layout);
    
    _angleSelector = new AngleSelector();
    _layout->addWidget(_angleSelector);
    QObject::connect(_angleSelector, SIGNAL(selectionChanged(QPair<QString, QString>, QPair<QString, QString>)), this, SLOT(run()));
    
    _plot = new AngularMotionPlot();
    _layout->addWidget(_plot);
}

void MotionDetectorWidget::run()
{
    _plot->clear();
    if(!_angleSelector->fixed().first.isEmpty() && !_angleSelector->fixed().second.isEmpty() && !_angleSelector->mobile().first.isEmpty() && !_angleSelector->mobile().second.isEmpty())
    {
        _motionDetector.run(_angleSelector->fixed(), _angleSelector->mobile());
        _plot->setAmplitudeCurve(_motionDetector.amplitudes());
        _plot->setSpeedCurve(_motionDetector.speeds());
        
        if(_motionDetector.detected())
        {
            _plot->setBeginLine(_motionDetector.begin());
            _plot->setEndLine(_motionDetector.end());
            _plot->setPeakLine(_motionDetector.peak());
        }
    }
}

Record * MotionDetectorWidget::record() const
{
    return _record;
}

void MotionDetectorWidget::setRecord(Record * record)
{
    _record = record;
    _motionDetector.setRecord(_record);
    _angleSelector->setItems(_record->labels());
    _angleSelector->setFixed(_fixedDefault);
    _angleSelector->setMobile(_mobileDefault);
    _plot->setRange(1, _record->duration());
    run();
}

void MotionDetectorWidget::setDefaultAngle(QPair<QString, QString> fixed, QPair<QString, QString> mobile)
{
    qDebug() << "[motiondetectorwidget] got default angle (" << fixed.first << fixed.second << mobile.first << mobile.second << ")";
    _fixedDefault = fixed;
    _mobileDefault = mobile;
}
