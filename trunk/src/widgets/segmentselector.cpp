#include "segmentselector.h"

#include <QComboBox>
#include <QHBoxLayout>

SegmentSelector::SegmentSelector(QWidget * parent): QWidget(parent)
{
    _layout = new QHBoxLayout();
    setLayout(_layout);
    
    _proximalComboBox = new QComboBox();
    _layout->addWidget(_proximalComboBox);
    QObject::connect(_proximalComboBox, SIGNAL(valueChanged(QString)), this, SLOT(onProximalValueChanged()));
    
    _distalComboBox = new QComboBox();
    _layout->addWidget(_distalComboBox);
    QObject::connect(_distalComboBox, SIGNAL(valueChanged(QString)), this, SLOT(onDistalValueChanged()));
}

QString SegmentSelector::distal() const
{
    return _distalComboBox->currentText();
}

void SegmentSelector::onDistalValueChanged()
{
    emit distalValueChanged(distal());
    emit valueChanged(value());
}

void SegmentSelector::onProximalValueChanged()
{
    emit proximalValueChanged(proximal());
    emit valueChanged(value());
}

QString SegmentSelector::proximal() const
{
    return _proximalComboBox->currentText();
}

void SegmentSelector::setDistal(QString value)
{
    _distalComboBox->setCurrentIndex(_items.indexOf(value));
}

void SegmentSelector::setItems(QList<QString> value)
{
    _items = value;
    _proximalComboBox->clear();
    _proximalComboBox->addItems(_items);
    _distalComboBox->clear();
    _distalComboBox->addItems(_items);
}

void SegmentSelector::setProximal(QString value)
{
    _proximalComboBox->setCurrentIndex(_items.indexOf(value));
}

void SegmentSelector::setValue(QString proximal, QString distal)
{
    setProximal(proximal);
    setDistal(distal);
}

void SegmentSelector::setValue(QPair<QString, QString> value)
{
    setValue(value.first, value.second);
}

QPair<QString, QString> SegmentSelector::value() const
{
    return QPair<QString, QString>(proximal(), distal());
}
