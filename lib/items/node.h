#pragma once

#include <QList>
#include "item.h"
#include "connector.h"
#include "../types.h"

class QGraphicsSceneMouseEvent;
class QGraphicsSceneHoverEvent;

namespace QSchematic {

    class Connector;
    class Label;

    class Node : public Item
    {
        Q_OBJECT
        Q_DISABLE_COPY(Node)

    signals:
        void sizeChanged();

    public:
        enum Mode {
            None,
            Resize
        };
        Q_ENUM(Mode)

        Node(int type = Item::NodeType, QGraphicsItem* parent = nullptr);
        virtual ~Node() override = default;

        virtual Gpds::Container toContainer() const override;
        virtual void fromContainer(const Gpds::Container& container) override;
        virtual std::unique_ptr<Item> deepCopy() const override;

        Mode mode() const;
        void setSize(const QSizeF& size);
        void setSize(qreal width, qreal height);
        QSizeF size() const;
        QRectF sizeRect() const;
        void setAllowMouseResize(bool enabled);
        bool allowMouseResize() const;
        bool addConnector(const std::shared_ptr<Connector>& connector);
        bool removeConnector(const std::shared_ptr<Connector>& connector);
        void clearConnectors();
        QList<std::shared_ptr<Connector>> connectors() const;
        QList<QPointF> connectionPointsRelative() const;
        QList<QPointF> connectionPointsAbsolute() const;
        void setConnectorsMovable(bool enabled);
        bool connectorsMovable() const;
        void setConnectorsSnapPolicy(Connector::SnapPolicy policy);
        Connector::SnapPolicy connectorsSnapPolicy() const;
        void setConnectorsSnapToGrid(bool enabled);
        bool connectorsSnapToGrid() const;
        std::shared_ptr<QSchematic::Label> label() const;
        void setText(const QString& text);
        QString text() const;

        virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
        virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
        virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
        virtual void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
        virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;
        virtual void hoverMoveEvent(QGraphicsSceneHoverEvent* event) override;
        virtual QRectF boundingRect() const override;
        virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

    protected:
        void copyAttributes(Node& dest) const;
        QMap<RectanglePoint, QRect> resizeHandles() const;
        void paintResizeHandles(QPainter& painter);

    private:
        std::shared_ptr<Label> _label;
        Mode _mode;
        QPointF _lastMousePosWithGridMove;
        RectanglePoint _resizeHandle;
        QSizeF _size;
        bool _allowMouseResize;
        bool _connectorsMovable;
        Connector::SnapPolicy _connectorsSnapPolicy;
        bool _connectorsSnapToGrid;
        QList<std::shared_ptr<Connector>> _connectors;
    };

}
