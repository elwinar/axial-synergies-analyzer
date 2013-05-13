#ifndef SEGMENT_SELECTOR_H
#define SEGMENT_SELECTOR_H

#include <QList>
#include <QPair>
#include <QString>
#include <QWidget>

class QComboBox;
class QHBoxLayout;

class SegmentSelector : public QWidget
{
    Q_OBJECT
    
public:
    SegmentSelector(QWidget * parent = 0);
    
    QString distal() const;
    QString proximal() const;

public slots:
    void setDistal(QString value);
    void setItems(QList<QString> value);
    void setProximal(QString value);

protected slots:
    void onSelectionChange();
    
signals:
    void selectionChanged(QString proximal, QString distal);
    
private:
    QList<QString> _items;
    QHBoxLayout * _layout;
    QComboBox * _distalComboBox;
    QComboBox * _proximalComboBox;
};

#endif // SEGMENT_SELECTOR_H
