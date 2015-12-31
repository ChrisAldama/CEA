#include "stimuli.h"
#include <QFile>
#include <QStringList>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonParseError>

#define INPUT_S "in"
#define OUTPUT_S "out"

Stimuli::Stimuli()
{

}

QByteArray Stimuli::toJSon()
{
    QString json = "{\"input\":[%1],"
                   " \"output\":[%2]}";

    QStringList arr1;
    for(const auto &number:in){
        arr1 << QString::number(number);
    }

    json = json.arg(arr1.join(','));
    QStringList arr2;
    for(const auto &number:out){
        arr2 << QString::number(number);
    }

    json = json.arg(arr2.join(','));
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

    if(!(arr1_v.isArray() && arr2_v.isArray())){
        return Stimuli();
    }

    auto arr1 = arr1_v.toArray();
    auto arr2 = arr2_v.toArray();

    Vector in;
    Vector out;

    for(const auto &val: arr1){
        in.push_back(val.toDouble());
    }
    for(const auto &val: arr2){
        out.push_back(val.toDouble());
    }

    Stimuli sti;
    sti.in = in;
    sti.out = out;

    return sti;
}

