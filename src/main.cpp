#include <QApplication>
#include <QDebug>
#include <QList>
#include <QMap>
#include <QPen>
#include <QString>
#include <QStringList>
#include <QTextStream>

#include <algorithm>
#include <cmath>
#include "libs/qcustomplot.h"

#include "tools/motiondetector.h"
#include "tools/parser.h"
#include "utils/angle.h"
#include "utils/marker.h"
#include "utils/point.h"
#include "utils/record.h"
#include "utils/vector.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    QTextStream out(stdout);
    
    QFile fileQFile(app.arguments().at(1));
    Record record = Parser::parse(file);
    MotionDetector detector(record);
    
    detector.detect(QPair<QString, QString>("O", "Z"), QPair<QString, QString>("C7", "RTRO"));
    MotionDetector::Instant peak = detector.peak();
    MotionDetector::Instant begin = detector.begin();
    MotionDetector::Instant end = detector.end();
    /*
    
    QCustomPlot* plot = new QCustomPlot;
    plot->xAxis->setLabel("time");
    plot->xAxis->setRange(1, record.duration());
    plot->yAxis->setLabel("amplitude");
    plot->yAxis->setRange(0, 180);
    plot->yAxis2->setLabel("speed");
    plot->yAxis2->setVisible(true);
    plot->yAxis2->setRange(0, speeds.value(peak) * 1.1);
    
    plot->addGraph(plot->xAxis, plot->yAxis);
    plot->graph(0)->setPen(QPen(Qt::red));
    out << "data" << endl;
    for(QMap<unsigned int, double>::iterator i = amplitudes.begin(); i != amplitudes.end(); i++)
    {
        out << i.key() << " " << i.value() << endl;
        plot->graph(0)->addData(i.key(), i.value());
    }
    
    out << endl << "plot" << endl;
    for(QCPDataMap::const_iterator i = plot->graph(0)->data()->begin(); i != plot->graph(0)->data()->end(); i++)
    {
        out << i->key << " " << i->value << endl;
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
    line->point1->setCoords(0, threshold);
    line->point2->setAxes(plot->xAxis, plot->yAxis2);
    line->point2->setCoords(1, threshold);
    plot->addItem(line);
    
    line = new QCPItemStraightLine(plot);
    line->setPen(QPen(Qt::gray));
    line->point1->setAxes(plot->xAxis, plot->yAxis2);
    line->point1->setCoords(start, 0);
    line->point2->setAxes(plot->xAxis, plot->yAxis2);
    line->point2->setCoords(start, 1);
    plot->addItem(line);
    
    line = new QCPItemStraightLine(plot);
    line->setPen(QPen(Qt::gray));
    line->point1->setAxes(plot->xAxis, plot->yAxis2);
    line->point1->setCoords(stop, 0);
    line->point2->setAxes(plot->xAxis, plot->yAxis2);
    line->point2->setCoords(stop, 1);
    plot->addItem(line);
    
    plot->replot();
    plot->show();
    */
    
    return app.exec();
}
