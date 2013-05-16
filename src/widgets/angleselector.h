#ifndef ANGLE_SELECTOR_H
#define ANGLE_SELECTOR_H

#include <QList>
#include <QPair>
#include <QString>
#include <QWidget>

class QGridLayout;
class QLabel;
class SegmentSelector;

/**
 * A widget to select an angle composed of two segments
 */
class AngleSelector : public QWidget
{
    Q_OBJECT
    
public:
    AngleSelector(QWidget * parent = 0);
    
    /**
     * Return the selected labels of the fixed segment of the angle
     */
    QPair<QString, QString> fixed() const;
    
    /**
     * Return the selected labels of the mobile segment of the angle
     */
    QPair<QString, QString> mobile() const;
    
    /**
     * Tells if a valid angle has been selected, ie if both segment selectors have a selected value
     */
    bool valid() const;
    
public slots:
    /**
     * Set the fixed segment of the angle, or set it to none if value doesn't exists
     */
    void setFixed(QPair<QString, QString> value);
    
    /**
     * Set the points labels for the user to choose amongst
     */
    void setItems(QList<QString> value);
    
    /**
     * Set the segments selectors labels
     */
    void setLabels(QString fixed, QString mobile);
    
    /**
     * Set the mobile segment of the angle, or set it to none if value doesn't exists
     */
    void setMobile(QPair<QString, QString> value);
    
protected slots:
    /**
     * Internal behavior when the user select another item in one of the segments selectors
     */
    void onSelectionChange();
    
    /**
     * Internal behavior when the value of one of the segments selectors change
     */
    void onValueChange();
    
signals:
    /**
     * Emitted whenever the user changed the selected angle. Won't trigger if the change is done programmatically.
     */
    void selectionChanged(QPair<QString, QString> fixed, QPair<QString, QString> mobile);
    
    /**
     * Emitted whenever the value of the selected angle changed.
     */
    void valueChanged(QPair<QString, QString> fixed, QPair<QString, QString> mobile);
    
private:
    /**
     * The layout holding widget's content
     */
    QGridLayout * _layout;
    
    /**
     * The label of the fixed segment selector
     */
    QLabel * _fixedLabel;
    
    /**
     * The label of the mobile segment selector
     */
    QLabel * _mobileLabel;
    
    /**
     * The fixed segment selector
     */
    SegmentSelector * _fixedSelector;
    
    /**
     * The mobile segment selector
     */
    SegmentSelector * _mobileSelector;
};

#endif // ANGLE_SELECTOR_H
