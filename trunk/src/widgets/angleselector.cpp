#include "angleselector.h"

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
    QObject::connect(_fixedSelector, SIGNAL(valueChanged(QPair<QString, QString>)), this, SLOT(onFixedValueChanged()));
    
    _mobileLabel = new QLabel(tr("Mobile segment"));
    _layout->addWidget(_mobileLabel, 1, 0);
    
    _mobileSelector = new SegmentSelector();
    _layout->addWidget(_mobileSelector, 1, 1, 1, 2);
    QObject::connect(_mobileSelector, SIGNAL(valueChanged(QPair<QString, QString>)), this, SLOT(onMobileValueChanged()));
}

    
QPair<QString, QString> AngleSelector::fixed() const
{
    return _fixedSelector->value();
}

QPair<QString, QString> AngleSelector::mobile() const
{
    return _mobileSelector->value();
}

void AngleSelector::onFixedValueChanged()
{
    emit fixedValueChanged(fixed());
    emit valueChanged(value());
}

void AngleSelector::onMobileValueChanged()
{
    emit mobileValueChanged(mobile());
    emit valueChanged(value());
}

void AngleSelector::setFixed(QString proximal, QString distal)
{
    _fixedSelector->setProximal(proximal);
    _fixedSelector->setDistal(distal);
}

void AngleSelector::setFixed(QPair<QString, QString> value)
{
    setFixed(value.first, value.second);
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

void AngleSelector::setMobile(QString proximal, QString distal)
{
    _mobileSelector->setProximal(proximal);
    _mobileSelector->setDistal(distal);
}

void AngleSelector::setMobile(QPair<QString, QString> value)
{
    setMobile(value.first, value.second);
}

void AngleSelector::setValue(QPair<QString, QString> fixed, QPair<QString, QString> mobile)
{
    setFixed(fixed);
    setMobile(mobile);
}

void AngleSelector::setValue(QPair<QPair<QString, QString>, QPair<QString, QString> > value)
{
    setValue(value.first, value.second);
}

QPair<QPair<QString, QString>, QPair<QString, QString> > AngleSelector::value() const
{
    return QPair<QPair<QString, QString>, QPair<QString, QString> >(fixed(), mobile());
}
