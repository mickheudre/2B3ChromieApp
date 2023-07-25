#include "colorspacegenerator.h"
extern "C" {
#include "structures.h"
#include "conversion.h"
#include "gestion_bibliotheque.h"
#include "conversion.h"
#include "recherche.h"
}
#include <QDebug>
#include <QColor>
#include <QImage>
#include <QUrl>

ColorSpaceGenerator::ColorSpaceGenerator()
{


}

void ColorSpaceGenerator::run(QColor paperColor, QColor inkColor, const QUrl &imagePath)
{
    QImage *image = new QImage(imagePath.toLocalFile());

    QImage outputImage(QSize(image->width(), image->height()), QImage::Format_RGB32);
    QVector<ElementBibliotheque1D> bibliotheque1D(256*256*256);
    QVector<ComposantesNuance1D> profil1D(16*16*16);
    EnteteFichierProfil entete;

    int taux_encre = 1000;

    CouleurDImpression couleur, couleurPapier;
    couleur.couleur.r = inkColor.red();
    couleur.couleur.g = inkColor.green();
    couleur.couleur.b = inkColor.blue();

    couleurPapier.couleur.r = paperColor.red();
    couleurPapier.couleur.g = paperColor.green();
    couleurPapier.couleur.b = paperColor.blue();

    QVector<RgbColor> nuancier(256);
    QVector<uchar> imageConv(image->width()*image->height()*3);
    QVector<uchar> composante1(image->width()*image->height());
    QVector<RgbColor> imageSimulee(image->width()*image->height());

    QImage profileImage(16*16, 16*16, QImage::Format_ARGB32);

    for(int i = 0; i < image->width(); i ++) {
        for (int j = 0; j < image->height(); j++) {
            imageConv[(i + j*image->width())*3    ] = image->pixelColor(i,j).red();
            imageConv[(i + j*image->width())*3 + 1] = image->pixelColor(i,j).green();
            imageConv[(i + j*image->width())*3 + 2] = image->pixelColor(i,j).blue();
        }
    }

    creationNuancier1D(couleurPapier.couleur, &couleur.couleur, nuancier.data());
    QVector<int> tableauDesDifferences(256);
    estimationTempsCalul(1, nuancier.data(), tableauDesDifferences.data());
    creerProfil1D(couleurPapier,couleur,profil1D.data(),&entete,nuancier.data(),tableauDesDifferences.data());

    calculerFichiersImpression1D(imageConv.data(), image->width(), image->height(), profil1D.data(), bibliotheque1D.data(), taux_encre);

    for(int i=0;i<image->width()*image->height();i++)
    {
        composante1.data()[i] = bibliotheque1D[256*256*((RgbColor*)imageConv.data())[i].r+256*((RgbColor*)imageConv.data())[i].g+((RgbColor*)imageConv.data())[i].b].composantes.composante1;

    }
    RgbColor* imageSimuleeData  = imageSimulee.data();
    imageSimuleeData = simulerImpression1D(composante1.data(),couleurPapier.couleur,couleur.couleur,image->width()*image->height());

    float alpha=0;
    int i=0;
    QImage imageRendue(QSize(image->width(), image->height()), QImage::Format_RGB32);

    for(int i=0;i<image->width();i++)
    {
        for (int j = 0; j < image->height(); j++) {
            outputImage.setPixelColor(i,j, QColor(composante1[i + j*image->width()], composante1[i + j*image->width()], composante1[i + j*image->width()]));
            imageRendue.setPixelColor(i,j, QColor(imageSimuleeData[i + j*image->width()].r, imageSimuleeData[i + j*image->width()].g, imageSimuleeData[i + j*image->width()].b));

        }

    }

    for (int r = 0; r < 16; r++) {
        for (int g= 0; g < 16; g++) {
            for (int b = 0; b < 16; b++) {
                profileImage.setPixelColor(r+b*16, g, QColor(couleur.couleur.r, couleur.couleur.g, couleur.couleur.b, profil1D[r*g*b].composante1));

            }
        }
    }


    m_outputImagePath = QUrl::fromLocalFile("/Users/mick/outputB4.jpg");
    m_outputImage = imageRendue;
    emit outputImageChanged();
}

QUrl ColorSpaceGenerator::outputImagePath() const
{
    return m_outputImagePath;
}

const QImage ColorSpaceGenerator::outputImage() const
{
    return m_outputImage;
}
