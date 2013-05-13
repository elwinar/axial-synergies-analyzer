#ifndef RECORD_H
#define RECORD_H

#include <QList>
#include <QMap>
#include <QString>
#include "utils/marker.h"
#include "utils/point.h"

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
    bool contains(QString label) const;
    
    /**
     * Count the number of markers of the record. This count include the standard markers (O, X, Y, Z)
     */
    unsigned int count() const;
    
    /**
     * Return the duration of the record, ie the number of recorded frames
     */
    unsigned int duration() const;
    
    /**
     * The physical filename of the record
     */
    QString filename() const;
    
    /**
     * Return the list of the record's markers' labels
     */
    QList<QString> labels() const;
    
    /**
     * Return a particular marker based on its name
     */
    Marker marker(QString label) const;
    
    /**
     * The name of the record
     */
    QString name() const;
    
    /**
     * Set the duration of the record
     */
    void setDuration(unsigned int duration);
    
    /**
     * Set the filename of the record
     */
    void setFilename(QString filename);
    
    /**
     * Set a marker of the record based on its name
     */
    void setMarker(QString label, Marker marker);
    
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
    unsigned int _duration;
    QString _filename;
    QMap<QString, Marker> _markers;
    QString _name;
};

#endif // RECORD_H
