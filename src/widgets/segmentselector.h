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
    QPair<QString, QString> value() const;

public slots:
    void setDistal(QString value);
    void setItems(QList<QString> value);
    void setProximal(QString value);
    void setValue(QString proximal, QString distal);
    void setValue(QPair<QString, QString> value);

protected:
    void onDistalValueChanged();
    void onProximalValueChanged();
    
signals:
    void distalValueChanged(QString);
    void proximalValueChanged(QString);
    void valueChanged(QPair<QString, QString>);
    
private:
    QList<QString> _items;
    QHBoxLayout * _layout;
    QComboBox * _distalComboBox;
    QComboBox * _proximalComboBox;
};

#endif // SEGMENT_SELECTOR_H
