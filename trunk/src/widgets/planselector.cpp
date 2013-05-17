#include "planselector.h"

#include <QComboBox>
#include <QDebug>
#include <QGridLayout>
#include <QLabel>

PlanSelector::PlanSelector(QWidget * parent): QWidget(parent)
{
    _layout = new QGridLayout();
    setLayout(_layout);
    
    _planLabel = new QLabel(tr("plan"));
    _layout->addWidget(_planLabel, 0, 0);
    
    _planComboBox = new QComboBox();
    _layout->addWidget(_planComboBox, 0, 1, 1, 2);
    QObject::connect(_planComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(onValueChange()));
}

int PlanSelector::plan() const
{
    return _planComboBox->currentIndex();
}

void PlanSelector::onSelectionChange()
{
    emit selectionChanged(plan());
}

void PlanSelector::onValueChange()
{
    emit valueChanged(plan());
}

void PlanSelector::setItems()
{
    /*
    Disconnect the signals, then update the items, and reconnect the signals, to prevent them from being triggered when the change is made programmatically
    */
    QObject::disconnect(_planComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(onSelectionChange()));
    QList<QString> _items;
	_items << "3D angle" << "transversal plan (XY)" << "sagittal plan(YZ)" << "frontal plan(ZX)";
    _planComboBox->clear();
    _planComboBox->addItems(_items);
    QObject::connect(_planComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(onSelectionChange()));

}

void PlanSelector::setPlan(int value)
{
    /*
    Disconnect the signal, then set the value, and reconnect the signal, to prevent it from being triggered when the change is made programmatically
    */
    QObject::disconnect(_planComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onSelectionChange()));
    _planComboBox->setCurrentIndex(value);
    QObject::connect(_planComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onSelectionChange()));
}

bool PlanSelector::valid() const
{
    return (_planComboBox->currentIndex() != -1);
}
