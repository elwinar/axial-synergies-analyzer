#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QAction>
#include <QFile>
#include <QGridLayout>
#include <QMainWindow>
#include <QMenu>
#include <QSettings>

#include "utils/record.h"
#include "widgets/recordwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget * parent = 0);
    ~MainWindow();
    
    
protected:
    void loadSettings();
    void saveSettings();
    void initializeMenu();
    void initializeCentralWidget();
    
private:
    QSettings _settings;
    
    QMenu * _fileMenu;
    QMenu * _aboutMenu;
    
    QAction * _openAction;
    QAction * _quitAction;
    QAction * _aboutQtAction;
    
    Record * _record;
    RecordWidget * _recordWidget;
    
public slots:
    void load(QString filename);
    void open();
    
signals:
    void loaded(Record * record);
};

#endif // MAIN_WINDOW_H
