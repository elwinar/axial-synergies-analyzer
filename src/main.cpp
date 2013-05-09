#include <QApplication>
#include <QDebug>
#include <QPen>
#include <QString>
#include <QTextStream>

#include "libs/qcustomplot.h"

#include "widgets/mainwindow.h"

#include "tools/motiondetector.h"
#include "tools/parser.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    
    QCoreApplication::setApplicationName("axial-synergies-analyzer");
    
    MainWindow w;
    w.show();
    
    return app.exec();
}
