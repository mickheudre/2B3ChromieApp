#ifndef IMAGEPROVIDER_H
#define IMAGEPROVIDER_H

#include <QQuickImageProvider>
#include "colorspacegenerator.h"

class ImageProvider : public QQuickImageProvider
{
public:
    ImageProvider(std::shared_ptr<ColorSpaceGenerator> colorSpaceGenerator);

private:
    std::shared_ptr<ColorSpaceGenerator> m_colorSpaceGenerator;

    // QQuickImageProvider interface
public:
    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize);
};

#endif // IMAGEPROVIDER_H
