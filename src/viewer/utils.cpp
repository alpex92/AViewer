#include "include/utils.h"

#include <QFile>
#include <QTextStream>

Utils::Utils() {}

const QString Utils::readFile(QString fileName)
{
    QFile file(fileName);
    QString result = "";
    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream in(&file);
        result = in.readAll();
        file.close();
    }
    return result;
}



