#ifndef UTILS_H
#define UTILS_H

#include <QString>

class Utils
{
public:
    Utils();
    static const QString readFile(QString fileName);
    /*
    static void log(QString &text);
    static void log(QString &tag, QString &text);
    */
};

#endif // UTILS_H
