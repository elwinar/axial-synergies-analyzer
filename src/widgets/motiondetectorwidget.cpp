#include "motiondetectorwidget.h"

#include <cmath>

#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include <QList>
#include <QMessageBox>
#include <QPushButton>
#include <QString>
#include <QSpinBox>

#include "libs/qcustomplot.h"
#include "tools/motiondetector.h"
#include "utils/record.h"

MotionDetectorWidget::MotionDetectorWidget(QWidget * parent, Record * record): QWidget(parent)
{
    _detector = new MotionDetector();
    
    initializeLayout();
    
    setRecord(record);
    
    QObject::connect(this, SIGNAL(detected()), this, SLOT(drawPlot()));
}

MotionDetectorWidget::~MotionDetectorWidget()
{
    delete _detector;
}

void MotionDetectorWidget::clearPlot()
{
    _plot->clearGraphs();
    
    _plot->xAxis->setVisible(false);
    _plot->yAxis->setVisible(false);
    _plot->yAxis2->setVisible(false);
    
    _beginLine->setVisible(false);
    _peakLine->setVisible(false);
    _endLine->setVisible(false);
    
    _plot->replot();
}

void MotionDetectorWidget::clearComboBoxes()
{
    _proximalFixedComboBox->clear();
    _distalFixedComboBox->clear();
    _proximalMobileComboBox->clear();
    _distalMobileComboBox->clear();
}

void MotionDetectorWidget::drawBeginLine(int position)
{
    _beginLine->setPen(QPen(Qt::gray));
    _beginLine->point1->setAxes(_plot->xAxis, _plot->yAxis2);
    _beginLine->point1->setCoords(position, 0);
    _beginLine->point2->setAxes(_plot->xAxis, _plot->yAxis2);
    _beginLine->point2->setCoords(position, 1);
    _beginLine->setVisible(true);
    
    _plot->replot();
}

void MotionDetectorWidget::drawPeakLine(int position)
{
    _peakLine->setPen(QPen(Qt::gray));
    _peakLine->point1->setAxes(_plot->xAxis, _plot->yAxis2);
    _peakLine->point1->setCoords(position, 0);
    _peakLine->point2->setAxes(_plot->xAxis, _plot->yAxis2);
    _peakLine->point2->setCoords(position, 1);
    _peakLine->setVisible(true);
    
    _plot->replot();
}

void MotionDetectorWidget::drawEndLine(int position)
{
    _endLine->setPen(QPen(Qt::gray));
    _endLine->point1->setAxes(_plot->xAxis, _plot->yAxis2);
    _endLine->point1->setCoords(position, 0);
    _endLine->point2->setAxes(_plot->xAxis, _plot->yAxis2);
    _endLine->point2->setCoords(position, 1);
    _endLine->setVisible(true);
    
    _plot->replot();
}

void MotionDetectorWidget::drawGraph(QMap<unsigned int, double> data, QPen pen, QCPAxis * xAxis, QCPAxis * yAxis, QString name)
{
    unsigned int o = data.begin().key() - 1;
    QCPGraph * graph = _plot->addGraph(xAxis, yAxis);
    graph->setPen(pen);
    graph->setName(name);
    for(QMap<unsigned int, double>::iterator i = data.begin(); i != data.end(); i++)
    {
        if(i.key() != o + 1)
        {
            graph = _plot->addGraph(xAxis, yAxis);
            graph->removeFromLegend();
            graph->setPen(pen);
        }
        graph->addData(i.key(), i.value());
        o = i.key();
    }
}

void MotionDetectorWidget::drawPlot()
{
    setupPlot();
    
    QMap<unsigned int, double> amplitudes = _detector->amplitudes();
    QMap<unsigned int, double> speeds = _detector->speeds();
    
    _plot->xAxis->setVisible(true);
    _plot->yAxis->setVisible(true);
    _plot->yAxis2->setVisible(true);
    _plot->yAxis2->setRange(0, speeds.value(_detector->peak()) * 1.05);
    _plot->legend->setVisible(true);
    
    drawGraph(amplitudes, QPen(Qt::red), _plot->xAxis, _plot->yAxis, tr("Amplitudes"));
    drawGraph(speeds, QPen(Qt::blue), _plot->xAxis, _plot->yAxis2, tr("Speeds"));
    
    _plot->replot();
}

void MotionDetectorWidget::initializeLayout()
{
    QVBoxLayout * layout = new QVBoxLayout();
    setLayout(layout);
    
    QVBoxLayout * comboBoxesLayout = new QVBoxLayout();
    
    QHBoxLayout * fixedAngleLayout = new QHBoxLayout();
    QLabel * fixedLabel = new QLabel(tr("Fixed angle"));
    _proximalFixedComboBox = new QComboBox();
    _distalFixedComboBox = new QComboBox();
    fixedAngleLayout->addWidget(fixedLabel);
    fixedAngleLayout->addWidget(_proximalFixedComboBox);
    fixedAngleLayout->addWidget(_distalFixedComboBox);
    comboBoxesLayout->addLayout(fixedAngleLayout);
    QObject::connect(_proximalFixedComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(run()));
    QObject::connect(_distalFixedComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(run()));
    
    QHBoxLayout * mobileAngleLayout = new QHBoxLayout();
    QLabel * mobileLabel = new QLabel(tr("Mobile angle"));
    _proximalMobileComboBox = new QComboBox();
    _distalMobileComboBox = new QComboBox();
    mobileAngleLayout->addWidget(mobileLabel);
    mobileAngleLayout->addWidget(_proximalMobileComboBox);
    mobileAngleLayout->addWidget(_distalMobileComboBox);
    comboBoxesLayout->addLayout(mobileAngleLayout);
    QObject::connect(_proximalMobileComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(run()));
    QObject::connect(_distalMobileComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(run()));
    
    layout->addLayout(comboBoxesLayout);
    
    QPushButton * runButton = new QPushButton(tr("Run"));
    //layout->addWidget(runButton);
    QObject::connect(runButton, SIGNAL(clicked()), this, SLOT(run()));
    
    _plot = new QCustomPlot();
    layout->addWidget(_plot);
    
    _beginLine = new QCPItemStraightLine(_plot);
    _peakLine = new QCPItemStraightLine(_plot);
    _endLine = new QCPItemStraightLine(_plot);
    _beginLine->setVisible(false);
    _peakLine->setVisible(false);
    _endLine->setVisible(false);
    _plot->addItem(_beginLine);
    _plot->addItem(_peakLine);
    _plot->addItem(_endLine);
    
    QHBoxLayout * spinBoxesLayout = new QHBoxLayout();
    _beginSpinBox = new QSpinBox();
    _peakSpinBox = new QSpinBox();
    _endSpinBox = new QSpinBox();
    spinBoxesLayout->addWidget(_beginSpinBox);
    spinBoxesLayout->addWidget(_peakSpinBox);
    spinBoxesLayout->addWidget(_endSpinBox);
    layout->addLayout(spinBoxesLayout);
    QObject::connect(_beginSpinBox, SIGNAL(valueChanged(int)), this, SLOT(drawBeginLine(int)));
    QObject::connect(_peakSpinBox, SIGNAL(valueChanged(int)), this, SLOT(drawPeakLine(int)));
    QObject::connect(_endSpinBox, SIGNAL(valueChanged(int)), this, SLOT(drawEndLine(int)));
    
    QPushButton * saveButton = new QPushButton(tr("Save"));
    layout->addWidget(saveButton);
    QObject::connect(saveButton, SIGNAL(clicked()), this, SLOT(save()));
}

void MotionDetectorWidget::run()
{
    if(_record != 0)
    {
        // FIXME pseudo try-catch minable pour palier à un problème momentanné dû à une conception à l'arrache
        if(_proximalFixedComboBox->currentIndex() == -1 ||
            _distalFixedComboBox->currentIndex() == -1 ||
            _proximalMobileComboBox->currentIndex() == -1 ||
            _distalMobileComboBox->currentIndex() == -1 )
        {
            return;
        }
        
        _detector->detect(QPair<QString, QString>(_proximalFixedComboBox->currentText(), _distalFixedComboBox->currentText()), QPair<QString, QString>(_proximalMobileComboBox->currentText(), _distalMobileComboBox->currentText()));
        
        emit detected();
        
        if(_detector->detected())
        {
            _beginSpinBox->setValue(_detector->begin());
            _peakSpinBox->setValue(_detector->peak());
            _endSpinBox->setValue(_detector->end());
        }
    }
    else
    {
        QMessageBox::warning(this, tr("No record loaded"), tr("Can't run because no record has been loaded"));
    }
}

void MotionDetectorWidget::save()
{
    if(_detector->detected())
    {
        QFile file("save.csv");
        file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append);
        QTextStream out(&file);
        
        double amplitude = abs(_detector->amplitudes().value(_detector->begin()) - _detector->amplitudes().value(_detector->end()));
        double duration = _detector->end() - _detector->begin();
        
        out << _record->filename() << "," << _proximalMobileComboBox->currentText() << "," << _distalMobileComboBox->currentText() << "," << duration << "," << amplitude << "," << (amplitude / duration) << "\n";
    }
    else
    {
        QMessageBox::warning(this, tr("No motion detected"), tr("No motion has been detected, so there is nothing to save"));
    }
}

void MotionDetectorWidget::setRecord(Record * record)
{
    _record = record;
    _detector->setRecord(record);
    
    if(_record == 0)
    {
        clearComboBoxes();
        clearPlot();
        setDisabled(true);
    }
    else
    {
        setupComboBoxes();
        setupPlot();
        setupSpinBoxes();
        setDisabled(false);
        run();
    }
    
    emit recordChanged(record);
}

void MotionDetectorWidget::setupPlot()
{
    clearPlot();
    
    _plot->xAxis->setLabel(tr("time"));
    _plot->xAxis->setRange(1, _record->duration());
    _plot->yAxis->setLabel(tr("amplitude"));
    _plot->yAxis->setRange(0, 180);
    _plot->yAxis2->setLabel(tr("speed"));
    _plot->yAxis2->setRange(0, 1);
    
    _plot->replot();
}

void MotionDetectorWidget::setupComboBoxes()
{
    Q_ASSERT(_record != 0);
    
    clearComboBoxes();
    
    QList<QString> labels = _record->labels();
    
    _proximalFixedComboBox->insertItems(0, labels);
    _proximalFixedComboBox->setCurrentIndex(labels.indexOf("O"));
    _distalFixedComboBox->insertItems(0, labels);
    _distalFixedComboBox->setCurrentIndex(labels.indexOf("Z"));
    _proximalMobileComboBox->insertItems(0, labels);
    _proximalMobileComboBox->setCurrentIndex(labels.indexOf("C7"));
    _distalMobileComboBox->insertItems(0, labels);
    _distalMobileComboBox->setCurrentIndex(labels.indexOf("RTRO"));
}

void MotionDetectorWidget::setupSpinBoxes()
{
    Q_ASSERT(_record != 0);
    
    _beginSpinBox->setRange(0, _record->duration());
    _endSpinBox->setRange(0, _record->duration());
    _peakSpinBox->setRange(0, _record->duration());
}
