#ifndef STIMULI_H
#define STIMULI_H
#include <QString>
#include "vector.h"

class Stimuli
{
public:
    Stimuli();
    VVector in;
    VVector out;
    QString name;
    int samples;

    QByteArray toJSon();
    bool saveFile(const QString &filename);


    static Stimuli fromFile(const QString &filename);
    static Stimuli fromJSon(const QByteArray &json);
};

#endif // STIMULI_H
