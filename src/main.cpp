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
    
    /*
    QTextStream out(stdout);
    
    QFile file(app.arguments().at(1));
    Record * record = Parser::parse(file);
    
    MotionDetector detector(record);
    detector.detect(QPair<QString, QString>("O", "Z"), QPair<QString, QString>("C7", "RTRO"));
    
    unsigned int begining = detector.begining();
    unsigned int peak = detector.peak();
    unsigned int end = detector.end();
    QMap<unsigned int, double> amplitudes = detector.amplitudes();
    QMap<unsigned int, double> speeds = detector.speeds();
    
    QCustomPlot* plot = new QCustomPlot;
    
    plot->xAxis->setLabel("time");
    plot->xAxis->setRange(1, record->duration());
    plot->yAxis->setLabel("amplitude");
    plot->yAxis->setRange(0, 180);
    plot->yAxis2->setLabel("speed");
    plot->yAxis2->setVisible(true);
    plot->yAxis2->setRange(0, speeds.value(peak));
    
    plot->addGraph(plot->xAxis, plot->yAxis);
    plot->graph(0)->setPen(QPen(Qt::red));
    for(QMap<unsigned int, double>::iterator i = amplitudes.begin(); i != amplitudes.end(); i++)
    {
        plot->graph(0)->addData(i.key(), i.value());
    }
    
    plot->addGraph(plot->xAxis, plot->yAxis2);
    plot->graph(1)->setPen(QPen(Qt::blue));
    for(QMap<unsigned int, double>::iterator i = speeds.begin(); i != speeds.end(); i++)
    {
        plot->graph(1)->addData(i.key(), i.value());
    }
    
    QCPItemStraightLine* line;
    
    line = new QCPItemStraightLine(plot);
    line->setPen(QPen(Qt::gray));
    line->point1->setAxes(plot->xAxis, plot->yAxis2);
    line->point1->setCoords(peak, 0);
    line->point2->setAxes(plot->xAxis, plot->yAxis2);
    line->point2->setCoords(peak, 1);
    plot->addItem(line);
    
    line = new QCPItemStraightLine(plot);
    line->setPen(QPen(Qt::gray));
    line->point1->setAxes(plot->xAxis, plot->yAxis2);
    line->point1->setCoords(begining, 0);
    line->point2->setAxes(plot->xAxis, plot->yAxis2);
    line->point2->setCoords(begining, 1);
    plot->addItem(line);
    
    line = new QCPItemStraightLine(plot);
    line->setPen(QPen(Qt::gray));
    line->point1->setAxes(plot->xAxis, plot->yAxis2);
    line->point1->setCoords(end, 0);
    line->point2->setAxes(plot->xAxis, plot->yAxis2);
    line->point2->setCoords(end, 1);
    plot->addItem(line);
    
    plot->replot();
    plot->show();
    
    delete record;
    */
    
    MainWindow w;
    w.show();
    
    return app.exec();
}
