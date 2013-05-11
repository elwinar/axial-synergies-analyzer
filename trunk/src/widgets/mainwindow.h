#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QString>

class QAction;
class QLabel;
class QMenu;
class QSettings;
class Record;
class RecordWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget * parent = 0);
    ~MainWindow();
    
public slots:
    void loadRecord(QString filename);
    void open();
    void setRecord(Record * record);
    
signals:
    void recordLoaded(Record * record);
    
protected:
    void initializeCentralWidget();
    void initializeMenu();
    void loadSettings();
    void saveSettings();
    
private:
    QAction * _aboutQtAction;
    QMenu * _aboutMenu;
    QMenu * _fileMenu;
    QAction * _openAction;
    QAction * _quitAction;
    Record * _record;
    RecordWidget * _recordWidget;
    QSettings * _settings;
    QLabel * _workingFileLabel;
};

#endif // MAIN_WINDOW_H
