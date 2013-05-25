#include "acpanalyzer.h"

#include <QApplication>
#include "utils/angle.h"
#include <QVector>
#include "utils/marker.h"
#include "utils/vector.h"
#include "utils/point.h"

#include <libs/Eigen/Core>
#include <libs/Eigen/Eigen>

void ACPAnalyzer::run(unsigned int begin, unsigned int end, QTextStream & out)
{
    qDebug() << "Start";
    QSettings settings(QApplication::applicationFilePath().append(".ini"), QSettings::IniFormat);
    unsigned int sets = settings.value("sets", 0).toUInt();
    unsigned int angles = settings.value("angles", 0).toUInt();
    double threshold = settings.value("threshold", 0).toDouble();
    
    if(sets == 0 || angles == 0)
    {
        qDebug() << "Bad conf file...";
        return;
    }
    
    unsigned int onset = settings.value("onset", 0).toUInt();
    unsigned int offset = settings.value("offset", 0).toUInt();
    if(begin < onset)
    {
        begin = 0;
    }
    else
    {
        begin -= onset;
    }
    end += offset;
    
    /*
    Choisir jeu d'angles
    */
    unsigned int chosen_set = 0;
    QVector<QString> markers;
    for(unsigned int set = 1; set <= sets; set++)
    {
        qDebug() << "Checking set" << set;
        markers.clear();
        bool eligible = true;
        for(unsigned int angle = 1; angle <= angles; angle++)
        {
            QString fixed_proximal = settings.value(QString("set%1_angle%2/fixed_proximal").arg(set).arg(angle)).toString();
            QString fixed_distal = settings.value(QString("set%1_angle%2/fixed_distal").arg(set).arg(angle)).toString();
            QString mobile_proximal = settings.value(QString("set%1_angle%2/mobile_proximal").arg(set).arg(angle)).toString();
            QString mobile_distal = settings.value(QString("set%1_angle%2/mobile_distal").arg(set).arg(angle)).toString();
            
            if(!_record->containsMarker(fixed_proximal)
            || !_record->containsMarker(fixed_distal)
            || !_record->containsMarker(mobile_proximal)
            || !_record->containsMarker(mobile_distal))
            {
                qDebug() << "Invalid, skiping";
                eligible = false;
                break;
            }
            
            markers.push_back(fixed_proximal);
            markers.push_back(fixed_distal);
            markers.push_back(mobile_proximal);
            markers.push_back(mobile_distal);
        }
        if(!eligible)
        {
            continue;
        }
        
        qDebug() << "Computing liability threshold";
        unsigned int missing_individuals = 0;
        for(unsigned int individual = begin; individual < end; individual++)
        {
            for(unsigned int variable = 1; variable <= angles; variable++)
            {
                if(!_record->marker(markers.value((variable - 1) * 4)).exists(individual)
                || !_record->marker(markers.value((variable - 1) * 4 + 1)).exists(individual)
                || !_record->marker(markers.value((variable - 1) * 4 + 2)).exists(individual)
                || !_record->marker(markers.value((variable - 1) * 4 + 3)).exists(individual))
                {
                    missing_individuals++;
                    break;
                }
            }
        }
        
        double missing_ratio = (double) missing_individuals / ((double) end - (double) begin);
        qDebug() << "Liability:" << missing_ratio;
        if(missing_ratio <= threshold)
        {
            chosen_set = set;
            break;
        }
    }
    
    if(chosen_set == 0)
    {
        qDebug() << "No eligible set found";
        return;
    }
    else
    {
        qDebug() << "Using set" << chosen_set;
        qDebug() << markers;
    }
    
    /*
    Calculer matrice angles
    */
    unsigned int rows = end - begin + 1;
    unsigned int cols = angles;
    QVector<QVector<double> > amplitudes(rows, QVector<double>(cols, 0));
    for(unsigned int row = 0; row < rows; row++)
    {
        for(unsigned int column = 0; column < cols; column++)
        {
            Point fixed_proximal = _record->marker(markers.value(column * 4)).point(begin + row);
            Point fixed_distal = _record->marker(markers.value(column * 4 + 1)).point(begin + row);
            Point mobile_proximal = _record->marker(markers.value(column * 4 + 2)).point(begin + row);
            Point mobile_distal = _record->marker(markers.value(column * 4 + 3)).point(begin + row);
            amplitudes[row][column] = Angle(Vector(fixed_proximal, fixed_distal), Vector(mobile_proximal, mobile_distal), Angle::YZ).amplitude();
        }
    }
    qDebug() << "Amplitudes";
    print(amplitudes);
    
    /*
    Centrer matrice angles
    */
    QVector<double> means(cols);
    for(unsigned int col = 0; col < cols; col++)
    {
        for(unsigned int row = 0; row < rows; row++)
        {
            means[col] += amplitudes[row][col];
        }
    }
    for(unsigned int col = 0; col < cols; col++)
    {
        means[col] /= rows;
    }
    qDebug() << "Means";
    qDebug() << means;
    
    QVector<QVector<double> > centered(amplitudes);
    for(unsigned int col = 0; col < cols; col++)
    {
        for(unsigned int row = 0; row < rows; row++)
        {
            centered[row][col] -= means[col];
        }
    }
    qDebug() << "Centered";
    print(centered);
    
    /*
    Calculer covariance
    */
    QVector<QVector<double> > transposed(cols, QVector<double>(rows));
    for(unsigned int row = 0; row < cols; row++)
    {
        for(unsigned int col = 0; col < rows; col++)
        {
            transposed[row][col] = centered[col][row];
        }
    }
    qDebug() << "Transposed";
    print(transposed);
    
    QVector<QVector<double> > covariances(cols, QVector<double>(cols, 0));
    for(unsigned int row = 0; row < cols; row++)
    {
        for(unsigned int col = 0; col < cols; col++)
        {
            for(unsigned int i = 0; i < rows; i++)
            {
                covariances[row][col] += transposed[row][i] * centered[i][col];
            }
        }
    }
    
    for(unsigned int row = 0; row < cols; row++)
    {
        for(unsigned int col = 0; col < cols; col++)
        {
            covariances[row][col] /= cols * 2;
        }
    }
    qDebug() << "Covariance";
    print(covariances);
    
    /*
    Trouver valeurs et vecteurs propres
    */
    
    QVector<double> values(cols);
    QVector<QVector<double> > vectors(cols, QVector<double>(cols));
    eigen(covariances, values, vectors);
    qDebug() << "Eigen values";
    qDebug() << values;
    qDebug() << "Eigen vectors";
    print(vectors);
    
    /*
    Calculer scores
    */
    /*
    QVector<QVector<double> > scores(centered);
    for(unsigned int row = 0; row < rows; row++)
    {
        for(unsigned int col = 0; col < cols; col++)
        {
            for(unsigned int i = 0; i < cols; i++)
            {
                scores[row][col] += centered[row][i] * vectors[i][col];
            }
        }
    }
    qDebug() << "Scores";
    print(scores);
    */
    
    /*
    Exporter
    */
}

void ACPAnalyzer::print(QVector<QVector<double> > matrix)
{
    for(unsigned int i = 0; i < matrix.size();i++)
    {
        qDebug() << matrix.value(i);
    }
}

void ACPAnalyzer::eigen(QVector<QVector<double> > covariance, QVector<double> & values, QVector<QVector<double> > & vectors)
{
    using namespace Eigen;
    unsigned int size = covariance.size();
    
    // Convert covariance into an Eigen matrix
    MatrixXd matrix = MatrixXd(size, size);
    for(unsigned int row = 0; row < size; row++)
    {
        for(unsigned int col = 0; col < size; col++)
        {
            matrix(row,col) = covariance[row][col];
        }
    }
    // Find the eigenvalues & vectors using EigenSolver
    EigenSolver<MatrixXd> solver(matrix);
    
    // Convert results back to 
    VectorXd eigenValues = VectorXd::Zero(size);
    eigenValues = solver.eigenvalues().real();
    for(unsigned int col = 0; col < size; col++)
    {
        values[col] = eigenValues[col];
    }

    MatrixXd eigenVectors = MatrixXd::Zero(size, size);
    eigenVectors = solver.eigenvectors().real();
    for(unsigned int row = 0; row < size; row++)
    {
        for(unsigned int col = 0; col < size; col++)
        {
            vectors[row][col] = eigenVectors(row,col);
        }
    }
}
