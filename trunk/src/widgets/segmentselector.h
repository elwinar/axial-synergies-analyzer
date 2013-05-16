#ifndef SEGMENT_SELECTOR_H
#define SEGMENT_SELECTOR_H

#include <QList>
#include <QPair>
#include <QString>
#include <QWidget>

class QComboBox;
class QHBoxLayout;

/**
 * A double combobox widget to select a segment composed of two points
 */
class SegmentSelector : public QWidget
{
    Q_OBJECT
    
public:
    SegmentSelector(QWidget * parent = 0);
    
    /**
     * Returns the selected label of the distal point, or an empty string if none selected
     */
    QString distal() const;
    
    /**
     * Returns the selected label of the proximal point, or an empty string if none selected
     */
    QString proximal() const;
    
    /**
     * Tells if a valid segment has been selected, ie if both comboboxes have a selected value
     */
    bool valid() const;

public slots:
    /**
     * Set the distal point of the segment, or set it to none if value doesn't exists
     */
    void setDistal(QString value);
    
    /**
     * Set the points' labels for the user to choose amongst
     */
    void setItems(QList<QString> value);
    
    /**
     * Set the proximal point of the segment, or set it to none if value doesn't exists
     */
    void setProximal(QString value);

protected slots:
    /**
     * Internal behavior when the user select another item in one of the comboboxes
     */
    void onSelectionChange();
    
    /**
     * Internal behavior when the value of one of the comboboxes change
     */
    void onValueChange();
    
signals:
    /**
     * Emitted whenever the user changed the selected segment. Won't trigger if the change is done programmatically.
     */
    void selectionChanged(QString proximal, QString distal);
    
    /**
     * Emitted whenever the value of the selected segment changed.
     */
    void valueChanged(QString proximal, QString distal);
    
private:
    /**
     * The list of available point's labels
     */
    QList<QString> _items;
    
    /**
     * The layout holding widget's content
     */
    QHBoxLayout * _layout;
    
    /**
     * The combobox standing for the distal point of the segment
     */
    QComboBox * _distalComboBox;
    
    /**
     * The combobox standig for the proximal point of the segment
     */
    QComboBox * _proximalComboBox;
};

#endif // SEGMENT_SELECTOR_H
