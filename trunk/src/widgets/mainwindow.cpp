#include "mainwindow.h"

#include <QAction>
#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QSettings>
#include <QStatusBar>
#include <QString>
#include <QStyle>

#include "tools/parser.h"
#include "utils/record.h"
#include "widgets/recordwidget.h"

MainWindow::MainWindow(QWidget * parent): QMainWindow(parent)
{
    _settings = new QSettings(QApplication::applicationFilePath().append(".ini"), QSettings::IniFormat);
    _record = 0;
    _workingFileLabel = new QLabel();
    statusBar()->addPermanentWidget(_workingFileLabel);
    initializeMenu();
    initializeCentralWidget();
    loadSettings();
}

MainWindow::~MainWindow()
{
    setRecord(0);
    saveSettings();
    delete _settings;
}

void MainWindow::initializeCentralWidget()
{
    _recordWidget = new RecordWidget();
    _recordWidget->setSettings(_settings);
    setCentralWidget(_recordWidget);
    
    QObject::connect(this, SIGNAL(recordLoaded(Record *)), _recordWidget, SLOT(setRecord(Record *)));
}

void MainWindow::initializeMenu()
{
    _fileMenu = menuBar()->addMenu(tr("&File"));
    _openAction = _fileMenu->addAction(tr("&Open"), this, SLOT(open()), QKeySequence("Ctrl+O"));
    _openAction->setIcon(qApp->style()->standardIcon(QStyle::SP_DialogOpenButton));
    _quitAction = _fileMenu->addAction(tr("&Quit"), qApp, SLOT(quit()), QKeySequence("Ctrl+Q"));
    _quitAction->setIcon(qApp->style()->standardIcon(QStyle::SP_DialogCloseButton));

    _aboutMenu = menuBar()->addMenu(tr("&About"));
    _aboutQtAction = _aboutMenu->addAction(tr("&Qt"), qApp, SLOT(aboutQt()));
}

void MainWindow::loadRecord(QString filename)
{
    QFileInfo fileinfo(filename);
    if(fileinfo.exists())
    {
        _settings->setValue("open/dir", fileinfo.canonicalPath());
        _settings->setValue("open/last", filename);
        
        QFile file(filename);
        setRecord(Parser::parse(&file));
        
        _workingFileLabel->setText(filename);
        
        emit recordLoaded(_record);
    }
}

void MainWindow::loadSettings()
{
    resize(_settings->value("window/size", QSize(400, 400)).toSize());
    move(_settings->value("window/position", QPoint(200, 200)).toPoint());
    
    if(_settings->contains("open/last"))
    {
        loadRecord(_settings->value("open/last").toString());
    }
}

void MainWindow::open()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Choose the file to open"), _settings->value("open/dir", QDir::home().path()).toString(), "csv (*.csv)");
    if(!filename.isNull())
    {
        loadRecord(filename);
    }
}

void MainWindow::saveSettings()
{
    _settings->setValue("window/size", size());
    _settings->setValue("window/position", pos());
}

void MainWindow::setRecord(Record * record)
{
    if(_record != 0)
    {
        delete _record;
    }
    _record = record;
}
 