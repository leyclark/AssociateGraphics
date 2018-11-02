#pragma once

#include <QGraphicsObject>


class AnchorPoint : public QGraphicsObject
{
	Q_OBJECT
public:
	AnchorPoint(QGraphicsItem* parent = Q_NULLPTR);

private:
	virtual QRectF boundingRect() const;

	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

	virtual QVariant itemChange(GraphicsItemChange change, const QVariant& value);

Q_SIGNALS:
	void positionChanged(QPointF);
};
