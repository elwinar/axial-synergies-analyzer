#include "motiondetectorwidget.h"

#include <QVBoxLayout>
#include <QList>
#include <QString>

#include "tools/motiondetector.h"
#include "utils/record.h"
#include "widgets/angleselector.h"
#include "widgets/angularmotionplot.h"

MotionDetectorWidget::MotionDetectorWidget(QWidget * parent): QWidget(parent)
{
    _layout = new QVBoxLayout();
    setLayout(_layout);
    
    _selector = new AngleSelector();
    _layout->addWidget(_selector);
    
    _plot = new AngularMotionPlot();
    _layout->addWidget(_plot);
    QObject::connect(_selector, SIGNAL(selectionChanged(QPair<QString, QString>, QPair<QString, QString>)), this, SLOT(onSelectionChange()));
}

void MotionDetectorWidget::onSelectionChange()
{
    _plot->clear();
    if(!_selector->fixed().first.isEmpty() && !_selector->fixed().second.isEmpty() && !_selector->mobile().first.isEmpty() && !_selector->mobile().second.isEmpty())
    {
        _detector.run(_selector->fixed(), _selector->mobile());
        _plot->setAmplitudeCurve(_detector.amplitudes());
        _plot->setSpeedCurve(_detector.speeds());
        
        if(_detector.detected())
        {
            _plot->setBeginLine(_detector.begin());
            _plot->setEndLine(_detector.end());
            _plot->setPeakLine(_detector.peak());
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
    _detector.setRecord(_record);
    _selector->setItems(_record->labels());
    _plot->clear();
    _plot->setRange(1, _record->duration());
    
    emit recordChanged(_record);
}
