#include "iprovider.h"

IProvider::IProvider():
    QQuickImageProvider(QQmlImageProviderBase::Image)
{

}

QImage IProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    Q_UNUSED(id);
    if(img.isNull()){
        img = QImage(requestedSize, QImage::Format_RGB888);
        img.fill(Qt::white);
    }

    if(!size->isValid()){
        size->setHeight(img.height());
        size->setWidth(img.width());
    }
    if(requestedSize.isValid()){
        lastSize = requestedSize;
        return img.scaled(requestedSize,Qt::KeepAspectRatio,Qt::FastTransformation);
    }

    return img;
}

QSize IProvider::size()
{
    if(lastSize.isValid()){
        return lastSize;
    }

    return QSize(600,600);
}
