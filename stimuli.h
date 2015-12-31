#ifndef STIMULI_H
#define STIMULI_H
#include <QString>
#include "vector.h"

class Stimuli
{
public:
    Stimuli();
    Vector in;
    Vector out;

    QByteArray toJSon();
    bool saveFile(const QString &filename);

    static Stimuli fromFile(const QString &filename);
    static Stimuli fromJSon(const QByteArray &json);
};

#endif // STIMULI_H
