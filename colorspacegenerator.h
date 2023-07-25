#ifndef COLORSPACEGENERATOR_H
#define COLORSPACEGENERATOR_H

#include <QObject>
#include <QImage>
#include <QUrl>
class ColorSpaceGenerator : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QUrl outputImage READ outputImagePath  NOTIFY outputImageChanged)

public:
    ColorSpaceGenerator();

    Q_INVOKABLE void run(QColor paperColor, QColor inkColor, const QUrl &imagePath);
    QUrl outputImagePath() const ;
    const QImage outputImage() const;
signals:
    void outputImageChanged();

private:
    QUrl m_outputImagePath;
    QImage m_outputImage;
};

#endif // COLORSPACEGENERATOR_H
