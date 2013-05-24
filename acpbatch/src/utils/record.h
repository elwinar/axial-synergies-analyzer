#ifndef RECORD_H
#define RECORD_H

#include <QList>
#include <QMap>
#include <QString>
#include "utils/marker.h"
#include "utils/point.h"
#include "utils/analogdata.h"

/**
 * Represent a set of markers identified by labels.
 */
class Record
{
public:
    /**
     * Create a record with only the standard marker for axis O, X, Y and Z
     */
    Record();
    
    /**
     * Destroy the record
     */
    ~Record();
    
    /**
     * Tells wheter the record contains a particular marker based on its label
     */
    bool containsMarker(QString label) const;
    bool containsAnalogdata(QString label) const;
    
    /**
     * Count the number of markers of the record. This count include the standard markers (O, X, Y, Z)
     */
    unsigned int countMarkers() const;
    unsigned int countAnalogdatas() const;
    
    /**
     * Return the duration of the record, ie the number of recorded frames
     */
    unsigned int durationMarkers() const;
    unsigned int durationAnalogdatas() const;
    
    /**
     * The physical filename of the record
     */
    QString filename() const;
    
    /**
     * Return the list of the record's markers' labels
     */
    QList<QString> labelsMarkers() const;
    QList<QString> labelsAnalogdatas() const;
    
    /**
     * Return a particular marker based on its name
     */
    Marker marker(QString label) const;
    AnalogData analogdata(QString label) const;
    
    /**
     * The name of the record
     */
    QString name() const;
    
    /**
     * Set the duration of the record
     */
    void setMarkersDuration(unsigned int duration);
    void setAnalogdatasDuration(unsigned int duration);
    
    /**
     * Set the filename of the record
     */
    void setFilename(QString filename);
    
    /**
     * Set a marker of the record based on its name
     */
    void setMarker(QString label, Marker marker);
    void setAnalogdata(QString label, AnalogData data);
    
    /**
     * Set the name of the record
     */
    void setName(QString name);
    
protected:
    /**
     * Generate a marker consisting of the provided point for each recorded frame. Useful for standard markers...
     */
    Marker generate(Point point) const;
    
private:
    unsigned int _markersDuration;
    unsigned int _analogdatasDuration;
    QString _filename;
    QMap<QString, Marker> _markers;
    QString _name;
    QMap<QString, AnalogData> _analogdatas;
};

#endif // RECORD_H
