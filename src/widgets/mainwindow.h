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
    /**
     * Create a main window for the application
     */
    MainWindow(QWidget * parent = 0);
    ~MainWindow();
    
protected:
    /**
     * Initialize the window's central widget
     */
    void initializeCentralWidget();
    
    /**
     * Initialize the window's menu and actions
     */
    void initializeMenu();
    
    /**
     * Load the settings of the application from configuration file
     */
    void loadSettings();
    
    /**
     * Save the settings of the application into the configuration file
     */
    void saveSettings();
    
public slots:
    /**
     * Load a record from a file
     */
    void load(QString filename);
    
    /**
     * Open a file dialog to let the user choose a file to open
     */
    void open();
    
signals:
    /**
     * Emitted when a record is loaded
     */
    void loaded(Record * record);
    
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
    
    /**
     * Change the working record
     */
    void setRecord(Record * record);
};

#endif // MAIN_WINDOW_H
