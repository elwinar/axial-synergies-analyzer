#include "motiondetectorwidget.h"

#include <QDebug>
#include <QHBoxLayout>
#include <QFile>
#include <QList>
#include <QMessageBox>
#include <QPushButton>
#include <QSpinBox>
#include <QString>
#include <QVBoxLayout>

#include "tools/motiondetector.h"
#include "utils/record.h"
#include "widgets/angleselector.h"
#include "widgets/angularmotionplot.h"
#include "widgets/planselector.h"

MotionDetectorWidget::MotionDetectorWidget(QWidget * parent): QWidget(parent)
{
    _layout = new QVBoxLayout();
    setLayout(_layout);
    
    _angleSelector = new AngleSelector();
    _layout->addWidget(_angleSelector);
    _layout->setStretchFactor(_angleSelector, 0);
    QObject::connect(_angleSelector, SIGNAL(selectionChanged(QPair<QString, QString>, QPair<QString, QString>)), this, SLOT(run()));
    
    _planSelector = new PlanSelector();
    _layout->addWidget(_planSelector);
    _layout->setStretchFactor(_planSelector, 0);
    QObject::connect(_planSelector, SIGNAL(selectionChanged(int)), this, SLOT(run()));
	
    _plot = new AngularMotionPlot();
    _layout->addWidget(_plot);
    _layout->setStretchFactor(_plot, 1);
    
    QHBoxLayout * spinBoxesLayout = new QHBoxLayout();
    _beginSpinBox = new QSpinBox();
    _peakSpinBox = new QSpinBox();
    _endSpinBox = new QSpinBox();
    spinBoxesLayout->addWidget(_beginSpinBox);
    spinBoxesLayout->addWidget(_peakSpinBox);
    spinBoxesLayout->addWidget(_endSpinBox);
    _layout->addLayout(spinBoxesLayout);
    _layout->setStretchFactor(spinBoxesLayout, 0);
    QObject::connect(_beginSpinBox, SIGNAL(valueChanged(int)), this, SLOT(onBeginSpinBoxValueChange(int)));
    QObject::connect(_peakSpinBox, SIGNAL(valueChanged(int)), this, SLOT(onPeakSpinBoxValueChange(int)));
    QObject::connect(_endSpinBox, SIGNAL(valueChanged(int)), this, SLOT(onEndSpinBoxValueChange(int)));
    
    QPushButton * _saveButton = new QPushButton(tr("Save"));
    _saveButton->setShortcut(QKeySequence("Ctrl+S"));
    _layout->addWidget(_saveButton);
    _layout->setStretchFactor(_saveButton, 0);
    QObject::connect(_saveButton, SIGNAL(clicked()), this, SLOT(save()));
}

void MotionDetectorWidget::onBeginSpinBoxValueChange(int value)
{
    _plot->setBeginLine(value);
}

void MotionDetectorWidget::onPeakSpinBoxValueChange(int value)
{
    _plot->setPeakLine(value);
}

void MotionDetectorWidget::onEndSpinBoxValueChange(int value)
{
    _plot->setEndLine(value);
}

void MotionDetectorWidget::run()
{
    _plot->clear();
    
    if(_angleSelector->valid() && _planSelector->valid())
    {
        _motionDetector.run(_angleSelector->fixed(), _angleSelector->mobile(), _planSelector->plan());
        _plot->setAmplitudeCurve(_motionDetector.amplitudes());
        _plot->setSpeedCurve(_motionDetector.speeds());
        
        if(_motionDetector.detected())
        {
            _beginSpinBox->setValue(_motionDetector.begin());
            _peakSpinBox->setValue(_motionDetector.peak());
            _endSpinBox->setValue(_motionDetector.end());
        }
    }
}

Record * MotionDetectorWidget::record() const
{
    return _record;
}

void MotionDetectorWidget::save()
{
    if(_motionDetector.detected())
    {
        QFile file("motion-result.csv");
        file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append);
        QTextStream out(&file);
        
        double duration = _endSpinBox->value() - _beginSpinBox->value();
        double amplitude = abs(_motionDetector.amplitudes().value(_beginSpinBox->value()) - _motionDetector.amplitudes().value(_endSpinBox->value()));
        double speed = (amplitude / duration);
        
        double beginTime = _beginSpinBox->value();
        double beginAmplitude = _motionDetector.amplitudes().value(_beginSpinBox->value());
        double beginSpeed = _motionDetector.speeds().value(_beginSpinBox->value());
        
        double peakTime = _peakSpinBox->value();
        double peakAmplitude = _motionDetector.amplitudes().value(_peakSpinBox->value());
        double peakSpeed = _motionDetector.speeds().value(_peakSpinBox->value());
        
        double endTime = _endSpinBox->value();
        double endAmplitude = _motionDetector.amplitudes().value(_endSpinBox->value());
        double endSpeed = _motionDetector.speeds().value(_endSpinBox->value());
        
        out << _record->filename() << "," 
            << _angleSelector->fixed().first << ","
            << _angleSelector->fixed().second << "," 
            << _angleSelector->mobile().first << ","
            << _angleSelector->mobile().second << "," 
            << duration << ","
            << amplitude << ","
            << speed << ","
            << beginTime << ","
            << beginAmplitude << ","
            << beginSpeed << ","
            << peakTime << ","
            << peakAmplitude << ","
            << peakSpeed << ","
            << endTime << ","
            << endAmplitude << ","
            << endSpeed << "\n";
    }
    else
    {
        QMessageBox::warning(this, tr("No motion detected"), tr("No motion has been detected, so there is nothing to save"));
    }
}

void MotionDetectorWidget::setRecord(Record * record)
{
    _record = record;
    _motionDetector.setRecord(_record);
    _angleSelector->setItems(_record->labels());
    _angleSelector->setFixed(_fixedDefault);
    _angleSelector->setMobile(_mobileDefault);
	_planSelector->setItems();
	_planSelector->setPlan(_planDefault);
    _plot->setRange(1, _record->duration());
    _beginSpinBox->setRange(1, _record->duration());
    _peakSpinBox->setRange(1, _record->duration());
    _endSpinBox->setRange(1, _record->duration());
    
    run();
    
    emit recordChanged(_record);
}

void MotionDetectorWidget::setDefaultAngle(QPair<QString, QString> fixed, QPair<QString, QString> mobile)
{
    _fixedDefault = fixed;
    _mobileDefault = mobile;
}

void MotionDetectorWidget::setDefaultPlan(int plan)
{
	_planDefault = plan;
}
