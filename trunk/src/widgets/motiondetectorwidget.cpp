#include "motiondetectorwidget.h"

MotionDetectorWidget::MotionDetectorWidget(QWidget * parent): QWidget(parent)
{
    _layout = new QGridLayout();
    setLayout(_layout);
    initializeButtons();
    initializeSelectors();
    initializePlot();
}

MotionDetectorWidget::~MotionDetectorWidget()
{
}

void MotionDetectorWidget::initializeButtons()
{
    _runButton = new QPushButton(tr("Run"));
    _layout->addWidget(_runButton, 0, 0);
    
    _saveButton = new QPushButton(tr("Save"));
    _layout->addWidget(_saveButton, 0, 1);
}

void MotionDetectorWidget::initializeSelectors()
{
    _fixedLabel = new QLabel(tr("Fixed angle"));
    _layout->addWidget(_fixedLabel, 1, 0);
    
    _proximalFixedComboBox = new QComboBox();
    _layout->addWidget(_proximalFixedComboBox, 1, 1);
    
    _distalFixedComboBox = new QComboBox();
    _layout->addWidget(_distalFixedComboBox, 1, 2);
    
    _mobileLabel = new QLabel(tr("Mobile angle"));
    _layout->addWidget(_mobileLabel, 2, 0);
    
    _proximalMobileComboBox = new QComboBox();
    _layout->addWidget(_proximalMobileComboBox, 2, 1);
    
    _distalMobileComboBox = new QComboBox();
    _layout->addWidget(_distalMobileComboBox, 2, 2);
}

void MotionDetectorWidget::initializePlot()
{
    _plot = new QCustomPlot();
    _layout->addWidget(_plot, 3, 0, 5, 5);
}
