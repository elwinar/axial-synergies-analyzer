#ifndef ANGLE_SELECTOR_H
#define ANGLE_SELECTOR_H

#include <QList>
#include <QPair>
#include <QString>
#include <QWidget>

class QGridLayout;
class QLabel;
class SegmentSelector;

class AngleSelector : public QWidget
{
    Q_OBJECT
    
public:
    AngleSelector(QWidget * parent = 0);
    
    QPair<QString, QString> fixed() const;
    QPair<QString, QString> mobile() const;
    QPair<QPair<QString, QString>, QPair<QString, QString> > value() const;
    
public slots:
    void setFixed(QString proximal, QString distal);
    void setFixed(QPair<QString, QString> value);
    void setItems(QList<QString> value);
    void setLabels(QString fixed, QString mobile);
    void setMobile(QString proximal, QString distal);
    void setMobile(QPair<QString, QString> value);
    void setValue(QPair<QString, QString> fixed, QPair<QString, QString> mobile);
    void setValue(QPair<QPair<QString, QString>, QPair<QString, QString> > value);
    
protected:
    void onFixedValueChanged();
    void onMobileValueChanged();
    
signals:
    void fixedValueChanged(QPair<QString, QString> value);
    void mobileValueChanged(QPair<QString, QString> value);
    void valueChanged(QPair<QPair<QString, QString>, QPair<QString, QString> > value);
    
private:
    QGridLayout * _layout;
    
    QLabel * _fixedLabel;
    QLabel * _mobileLabel;
    
    SegmentSelector * _fixedSelector;
    SegmentSelector * _mobileSelector;
};

#endif // ANGLE_SELECTOR_H
