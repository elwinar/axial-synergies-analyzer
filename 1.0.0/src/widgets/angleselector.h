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
    
public slots:
    void setFixed(QPair<QString, QString> value);
    void setItems(QList<QString> value);
    void setLabels(QString fixed, QString mobile);
    void setMobile(QPair<QString, QString> value);
    
protected slots:
    void onSelectionChange();
    
signals:
    void selectionChanged(QPair<QString, QString> fixed, QPair<QString, QString> mobile);
    
private:
    QGridLayout * _layout;
    
    QLabel * _fixedLabel;
    QLabel * _mobileLabel;
    
    SegmentSelector * _fixedSelector;
    SegmentSelector * _mobileSelector;
};

#endif // ANGLE_SELECTOR_H
