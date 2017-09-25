#include "textfile.h"

bool TextFile::saveFile(const QString &pathToTheFile, const QString &data)
{
    QFile file(pathToTheFile);
    if(file.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&file);
        stream << data;
        file.close();
        return true;
    }
    return false;
}

QString TextFile::loadFile(const QString &pathToTheFile)
{
    QString data;

    QFile file(pathToTheFile);
    if(file.open(QIODevice::ReadOnly))
    {
        data = file.readAll();
        file.close();
    }

    return data;
}
