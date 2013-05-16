#include "segmentselector.h"

#include <QComboBox>
#include <QDebug>
#include <QHBoxLayout>

SegmentSelector::SegmentSelector(QWidget * parent): QWidget(parent)
{
    _layout = new QHBoxLayout();
    setLayout(_layout);
    
    _proximalComboBox = new QComboBox();
    _layout->addWidget(_proximalComboBox);
    QObject::connect(_proximalComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(onValueChange()));
    
    _distalComboBox = new QComboBox();
    _layout->addWidget(_distalComboBox);
    QObject::connect(_distalComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(onValueChange()));
}

QString SegmentSelector::distal() const
{
    return _distalComboBox->currentText();
}

void SegmentSelector::onSelectionChange()
{
    emit selectionChanged(proximal(), distal());
}

void SegmentSelector::onValueChange()
{
    emit valueChanged(proximal(), distal());
}

QString SegmentSelector::proximal() const
{
    return _proximalComboBox->currentText();
}

void SegmentSelector::setDistal(QString value)
{
    /*
    Disconnect the signal, then set the value, and reconnect the signal, to prevent it from being triggered when the change is made programmatically
    */
    QObject::disconnect(_distalComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(onSelectionChange()));
    _distalComboBox->setCurrentIndex(_items.indexOf(value));
    QObject::connect(_distalComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(onSelectionChange()));
}

void SegmentSelector::setItems(QList<QString> value)
{
    /*
    Disconnect the signals, then update the items, and reconnect the signals, to prevent them from being triggered when the change is made programmatically
    */
    QObject::disconnect(_distalComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(onSelectionChange()));
    QObject::disconnect(_proximalComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(onSelectionChange()));
    _items = value;
    _proximalComboBox->clear();
    _proximalComboBox->addItems(_items);
    _distalComboBox->clear();
    _distalComboBox->addItems(_items);
    QObject::connect(_distalComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(onSelectionChange()));
    QObject::connect(_proximalComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(onSelectionChange()));
}

void SegmentSelector::setProximal(QString value)
{
    /*
    Disconnect the signal, then set the value, and reconnect the signal, to prevent it from being triggered when the change is made programmatically
    */
    QObject::disconnect(_proximalComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(onSelectionChange()));
    _proximalComboBox->setCurrentIndex(_items.indexOf(value));
    QObject::connect(_proximalComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(onSelectionChange()));
}

bool SegmentSelector::valid() const
{
    return (_proximalComboBox->currentIndex() != -1) && (_distalComboBox->currentIndex() != -1);
}
