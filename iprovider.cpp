#include "iprovider.h"

IProvider::IProvider():
    QQuickImageProvider(QQmlImageProviderBase::Image)
{

}

QImage IProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    Q_UNUSED(id);

    if(!size->isValid()){
        size->setHeight(img.height());
        size->setWidth(img.width());
    }
    if(requestedSize.isValid()){
        return img.scaled(requestedSize,Qt::KeepAspectRatio,Qt::FastTransformation);
    }

    return img;
}
