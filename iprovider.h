#ifndef IPROVIDER_H
#define IPROVIDER_H

#include <QQuickImageProvider>
#include <QImage>

class IProvider : public QQuickImageProvider{

public:
    IProvider();

    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize);
    QImage img;
    QSize size();

private:
    QSize lastSize;
};

#endif // IPROVIDER_H
