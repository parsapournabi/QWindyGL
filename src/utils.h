#ifndef UTILS_H
#define UTILS_H

#include <QObject>
#include <QMap>
#include <QImage>
#include <QPainter>
#include <QColor>
#include <QLinearGradient>
#include <QtMath>
#include <QDir>

namespace Utils
{

    /**
     *  Coordinates Minimum & Maximum Values
     *  These should be use at vertices converting process
    **/
    constexpr float LimitLeft = -M_PI; // -180.0 deg
    constexpr float LimitRight = M_PI; // 180.0 deg
    constexpr float LimitBottom = -M_PI_2; // -90.0 deg
    constexpr float LimitTop = M_PI_2; // 90.0 deg


    inline QMap<float, QColor> defaultRampColors =
    {
        {0.0, "#3288bd"},
        {0.1, "#66c2a5"},
        {0.2, "#abdda4"},
        {0.3, "#e6f598"},
        {0.4, "#fee08b"},
        {0.5, "#fdae61"},
        {0.6, "#f46d43"},
        {1.0, "#d53e4f"}
    };

    inline static QImage getColorRamp(const QMap<float, QColor>& colorRamp = defaultRampColors)
    {
        const int width = 256;
        const int height = 1;

        QImage image(width, height, QImage::Format_ARGB32_Premultiplied);
        image.fill(Qt::transparent);

        QLinearGradient gradient(0, 0, width, 0); // Horizontal
        // QLinearGradient gradient(0, 0, 0, height); // Vertical

        for (auto it = colorRamp.begin(); it != colorRamp.end(); ++it)
        {
            gradient.setColorAt(it.key(), it.value());
        }

        QPainter painter(&image);
        painter.setRenderHint(QPainter::Antialiasing, false);
        painter.fillRect(image.rect(), gradient);
        painter.end();

        return image;
    }

    inline QImage getWindData(int index, const char* dir = IMAGES_SOURCE_DIR)
    {
        /** Getting all available images which are  declared at `dir` **/
        QDir imgDir(dir);
        auto images = imgDir.entryInfoList(QDir::Filter::Files, QDir::SortFlag::Name);

        // Loading specific image
        if (index < images.size())
        {
            auto path = images.at(index).absoluteFilePath();
            return QImage(path);
        }
        return {};
    }

    inline static QStringList getWindDataNames(const char* dir = IMAGES_SOURCE_DIR)
    {
        return QDir(dir).entryList(QDir::Filter::Files, QDir::SortFlag::Name);
    }

}

#endif // UTILS_H
