#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QFileInfo>
#include <QMenuBar>
#include <QStyle>

#include "tools/parser.h"

/**
 * Create a main window for the application
 */
MainWindow::MainWindow(QWidget * parent): QMainWindow(parent), _settings(QApplication::applicationFilePath().append(".ini"), QSettings::IniFormat)
{
    _record = 0;
    loadSettings();
    initializeMenu();
    initializeCentralWidget();
}

MainWindow::~MainWindow()
{
    if(_record != 0)
    {
        delete _record;
    }
    saveSettings();
}

/**
 * Load the settings of the application from configuration file
 */
void MainWindow::loadSettings()
{
    qDebug() << "[mainwindow] loading settings from" << _settings.fileName();
    
    resize(_settings.value("window/size", QSize(400, 400)).toSize());
    move(_settings.value("window/position", QPoint(200, 200)).toPoint());
}

/**
 * Save the settings of the application into the configuration file
 */
void MainWindow::saveSettings()
{
    qDebug() << "[mainwindow] saving settings into" << _settings.fileName();
    
    _settings.setValue("window/size", size());
    _settings.setValue("window/position", pos());
}

/**
 * Initialize the window's menu and actions
 */
void MainWindow::initializeMenu()
{
    qDebug() << "[mainwindow] initializing menu";
    
    _fileMenu = menuBar()->addMenu(tr("&File"));
    _openAction = _fileMenu->addAction(tr("&Open"), this, SLOT(open()), QKeySequence("Ctrl+O"));
    _openAction->setIcon(qApp->style()->standardIcon(QStyle::SP_DialogOpenButton));
    _quitAction = _fileMenu->addAction(tr("&Quit"), qApp, SLOT(quit()), QKeySequence("Ctrl+Q"));
    _quitAction->setIcon(qApp->style()->standardIcon(QStyle::SP_DialogCloseButton));

    _aboutMenu = menuBar()->addMenu(tr("&About"));
    _aboutQtAction = _aboutMenu->addAction(tr("&Qt"), qApp, SLOT(aboutQt()));
}

void MainWindow::initializeCentralWidget()
{
    qDebug() << "[mainwindow] initializing central widget";
    
    _recordWidget = new RecordWidget();
    setCentralWidget(_recordWidget);
}

/**
 * Open a file dialog to let the user choose a file to open
 * TODO Multiple checks about file
 */
void MainWindow::open()
{
    qDebug() << "[mainwindow] opening file dialog";
    
    QString filename = QFileDialog::getOpenFileName(this, tr("Choose the file to open"), _settings.value("open/dir", QDir::home().path()).toString(), "csv (*.csv)");
    if(!filename.isNull())
    {
        QFileInfo fileinfo(filename);
        if(fileinfo.exists())
        {
            _settings.setValue("open/dir", fileinfo.canonicalPath());
            _settings.setValue("open/last", filename);
            load(filename);
        }
        else
        {
            qDebug() << "[mainwindow] file" << filename << "doesn't seem to exists";
        }
    }
    else
    {
        qDebug() << "[mainwindow] no file chosen, aborting";
    }
}

/**
 * Load a record from a file
 */
void MainWindow::load(QString filename)
{
    qDebug() << "[mainwindow] loading" << filename;
    
    if(_record != 0)
    {
        delete _record;
    }
    QFile file(filename);
    _record = Parser::parse(file);
    
    emit loaded(_record);
}
