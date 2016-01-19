#include "stimuli.h"
#include <QFile>
#include <QStringList>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonParseError>
#include <assert.h>

#define INPUT_S "in"
#define OUTPUT_S "out"
#define NAME_S "name"
#define INS "inputs"
#define OUTS "outputs"

Stimuli::Stimuli()
{

}

QByteArray Stimuli::toJSon()
{
    QString json = "{\"in\":[%1],"
                   " \"out\":[%2]}";


    return json.toLocal8Bit();

}

bool Stimuli::saveFile(const QString &filename)
{
    QFile file(filename);
    if(!file.open(QFile::WriteOnly)){
        return false;
    }
    auto json = toJSon();
    file.write(json);
    file.close();
    return true;
}

Stimuli Stimuli::fromFile(const QString &filename)
{
    QFile file(filename);
    if(!file.open(QFile::ReadOnly)){
        return Stimuli();
    }
    QByteArray data = file.readAll();
    file.close();

    return fromJSon(data);
}

VVector arrayToVector(const QJsonArray &arr)
{
    VVector vector;
    for(const QJsonValue &val : arr){
        Vector v;
        if(val.isArray()){
            QJsonArray subArr = val.toArray();
            for(const QJsonValue &sVal : subArr){
                double num = sVal.toDouble();
                v.push_back(num);
            }
        }
        else if(val.isDouble()){
            v.push_back(val.toDouble());
        }

        vector.push_back(v);
    }

    return vector;

}

Stimuli Stimuli::fromJSon(const QByteArray &json)
{
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(json, &error);
    if(error.error != QJsonParseError::NoError){
        return Stimuli();
    }
    QJsonObject obj = doc.object();
    QJsonValue arr1_v = obj.value(INPUT_S);
    QJsonValue arr2_v = obj.value(OUTPUT_S);
    QJsonValue name = obj.value(NAME_S);

    if(!(arr1_v.isArray() && arr2_v.isArray())){
        return Stimuli();
    }

    auto arr1 = arr1_v.toArray();
    auto arr2 = arr2_v.toArray();

    assert(arr1.size() == arr2.size());

    Stimuli sti;
    sti.in = arrayToVector(arr1);
    sti.out = arrayToVector(arr2);
    sti.name = name.toString("none");
    sti.samples = arr1.size();
    sti.inputs = obj.value(INS).toInt();
    sti.outputs = obj.value(OUTS).toInt();

    return sti;
}

