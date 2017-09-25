#ifndef TEXTFILE_H
#define TEXTFILE_H

#include <QFile>
#include <QTextStream>
#include <QString>
#include <QRegExp>

class TextFile
{
public:

    /*
     * Return value : true if ok,
     *                false if this failed for some reason.
     */
    static bool saveFile(const QString &pathToTheFile, const QString &data);

    /*
     * Return value : data string if ok,
     *                empty string if this failed for some reason.
     */
    static QString loadFile(const QString &pathToTheFile);
};

#endif // TEXTFILE_H
