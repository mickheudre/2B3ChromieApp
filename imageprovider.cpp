#include "imageprovider.h"

ImageProvider::ImageProvider(std::shared_ptr<ColorSpaceGenerator> colorSpaceGenerator) :
    m_colorSpaceGenerator(colorSpaceGenerator),
    QQuickImageProvider(QQuickImageProvider::Image)
{

}

QImage ImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    return m_colorSpaceGenerator->outputImage();
}
