#pragma once

#include <chrono>

class QPoint;
class QPointF;
class QRectF;
class QVector2D;
class QSize;
class QSizeF;

namespace QSchematic {

    class Settings
    {
    public:
        Settings();
        virtual ~Settings() = default;

        QPoint toGridPoint(const QPointF& point) const;
        QPoint toScenePoint(const QPoint& gridPoint) const;
        QPoint snapToGrid(const QPointF& scenePoint) const;
        QVector2D snapToGrid(const QVector2D& sceneVector) const;
        QSize snapToGrid(const QSizeF& sceneSize) const;

        bool debug;
        int gridSize;
        int gridPointSize;
        bool showGrid;
        int highlightRectPadding;
        int resizeHandleSize;
        bool routeStraightAngles;
        bool preserveStraightAngles;
        bool antialiasing;
        std::chrono::milliseconds popupDelay;
    };

}
