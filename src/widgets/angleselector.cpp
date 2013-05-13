#include "angleselector.h"

#include <QDebug>
#include <QGridLayout>
#include <QLabel>

#include "widgets/segmentselector.h"

AngleSelector::AngleSelector(QWidget * parent): QWidget(parent)
{
    _layout = new QGridLayout();
    setLayout(_layout);
    
    _fixedLabel = new QLabel(tr("Fixed segment"));
    _layout->addWidget(_fixedLabel, 0, 0);
    
    _fixedSelector = new SegmentSelector();
    _layout->addWidget(_fixedSelector, 0, 1, 1, 2);
    QObject::connect(_fixedSelector, SIGNAL(selectionChanged(QString, QString)), this, SLOT(onSelectionChange()));
    
    _mobileLabel = new QLabel(tr("Mobile segment"));
    _layout->addWidget(_mobileLabel, 1, 0);
    
    _mobileSelector = new SegmentSelector();
    _layout->addWidget(_mobileSelector, 1, 1, 1, 2);
    QObject::connect(_mobileSelector, SIGNAL(selectionChanged(QString, QString)), this, SLOT(onSelectionChange()));
}

    
QPair<QString, QString> AngleSelector::fixed() const
{
    return QPair<QString, QString>(_fixedSelector->proximal(), _fixedSelector->distal());
}

void AngleSelector::onSelectionChange()
{
    emit selectionChanged(fixed(), mobile());
}

QPair<QString, QString> AngleSelector::mobile() const
{
    return QPair<QString, QString>(_mobileSelector->proximal(), _mobileSelector->distal());
}

void AngleSelector::setFixed(QPair<QString, QString> value)
{
    _fixedSelector->setProximal(value.first);
    _fixedSelector->setDistal(value.second);
}

void AngleSelector::setItems(QList<QString> value)
{
    _fixedSelector->setItems(value);
    _mobileSelector->setItems(value);
}

void AngleSelector::setLabels(QString fixed, QString mobile)
{
    _fixedLabel->setText(fixed);
    _mobileLabel->setText(mobile);
}

void AngleSelector::setMobile(QPair<QString, QString> value)
{
    _mobileSelector->setProximal(value.first);
    _mobileSelector->setDistal(value.second);
}
