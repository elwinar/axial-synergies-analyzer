#include "mainwindow.h"

#include <QAction>
#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QMenu>
#include <QMenuBar>
#include <QStyle>

#include "tools/parser.h"
#include "utils/record.h"
#include "widgets/recordwidget.h"

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

void MainWindow::initializeCentralWidget()
{
    qDebug() << "[mainwindow] initializing central widget";
    
    _recordWidget = new RecordWidget();
    setCentralWidget(_recordWidget);
}

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

void MainWindow::load(QString filename)
{
    qDebug() << "[mainwindow] loading" << filename;
    
    if(_record != 0)
    {
        delete _record;
    }
    QFile file(filename);
    _record = Parser::parse(&file);
    
    emit loaded(_record);
}

void MainWindow::loadSettings()
{
    qDebug() << "[mainwindow] loading settings from" << _settings.fileName();
    
    resize(_settings.value("window/size", QSize(400, 400)).toSize());
    move(_settings.value("window/position", QPoint(200, 200)).toPoint());
}

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

void MainWindow::saveSettings()
{
    qDebug() << "[mainwindow] saving settings into" << _settings.fileName();
    
    _settings.setValue("window/size", size());
    _settings.setValue("window/position", pos());
}
