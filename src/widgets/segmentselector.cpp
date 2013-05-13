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
    QObject::connect(_proximalComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(onSelectionChange()));
    
    _distalComboBox = new QComboBox();
    _layout->addWidget(_distalComboBox);
    QObject::connect(_distalComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(onSelectionChange()));
}

QString SegmentSelector::distal() const
{
    return _distalComboBox->currentText();
}

void SegmentSelector::onSelectionChange()
{
    emit selectionChanged(proximal(), distal());
}

QString SegmentSelector::proximal() const
{
    return _proximalComboBox->currentText();
}

void SegmentSelector::setDistal(QString value)
{
    qDebug() << "[segmentselector] distal point set to" << value;
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
    qDebug() << "[segmentselector] proximal point set to" << value;
    _proximalComboBox->setCurrentIndex(_items.indexOf(value));
}
