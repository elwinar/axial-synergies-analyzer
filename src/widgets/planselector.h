#ifndef PLAN_SELECTOR_H
#define PLAN_SELECTOR_H

#include <QString>
#include <QWidget>
#include <QList>

class QComboBox;
class QGridLayout;
class QLabel;

/**
 * A combobox widget to select the plan of analysis
 */
class PlanSelector : public QWidget
{
    Q_OBJECT
    
public:
    PlanSelector(QWidget * parent = 0);
    
    /**
     * Returns the selector label, or an empty string if none selected
     */
    int plan() const;
    
    /**
     * Tells if a valid plan has been selected, ie if both comboboxes have a selected value
     */
    bool valid() const;

public slots:
    /**
     * Set the plan of analysis
     */
    void setPlan(int value);
    
    /**
     * Set the plans' labels for the user to choose amongst
     */
    void setItems();

protected slots:
    /**
     * Internal behavior when the user select another plan in the comboboxes
     */
    void onSelectionChange();
    
    /**
     * Internal behavior when the value of one of the comboboxes change
     */
    void onValueChange();
    
signals:
    /**
     * Emitted whenever the user changed the selected plan. Won't trigger if the change is done programmatically.
     */
    void selectionChanged(int plan);
    
    /**
     * Emitted whenever the value of the selected plan changed.
     */
    void valueChanged(int plan);
    
private:
    /**
     * The list of available plans
     */
    QList<QString> _items;
    
    /**
     * The layout holding widget's content
     */
    QGridLayout * _layout;
    
    /**
     * The combobox standig for the plan
     */
    QComboBox * _planComboBox;
	
    
    /**
     * The label of the plan selector
     */
	QLabel * _planLabel;
};

#endif // PLAN_SELECTOR_H
