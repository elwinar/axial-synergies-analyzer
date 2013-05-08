#ifndef MOTION_DETECTOR_WIDGET_H
#define MOTION_DETECTOR_WIDGET_H

#include <QPushButton>
#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include <QWidget>

#include "libs/qcustomplot.h"

class MotionDetectorWidget : public QWidget
{
    Q_OBJECT
    
public:
    MotionDetectorWidget(QWidget * parent = 0);
    ~MotionDetectorWidget();
    
protected:
    void initializeSelectors();
    void initializeButtons();
    void initializePlot();
    
private:
    QGridLayout * _layout;
    
    QPushButton * _runButton;
    QPushButton * _saveButton;
    
    QLabel * _fixedLabel;
    QLabel * _mobileLabel;
    QComboBox * _proximalFixedComboBox;
    QComboBox * _distalFixedComboBox;
    QComboBox * _proximalMobileComboBox;
    QComboBox * _distalMobileComboBox;
    
    QCustomPlot * _plot;
};

#endif // MOTION_DETECTOR_WIDGET_H
