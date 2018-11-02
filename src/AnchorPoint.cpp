#include "AnchorPoint.h"
#include <QPainter>


AnchorPoint::AnchorPoint(QGraphicsItem* parent)
	:QGraphicsObject(parent)
{
	setFlag(QGraphicsItem::ItemHasNoContents, true);		// 使paint无效
	setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);	// 发出位置改变信号
	setFlag(QGraphicsItem::ItemSendsScenePositionChanges, true);	// 发出位置改变信号
}

QRectF AnchorPoint::boundingRect() const
{
	return QRectF();
}

void AnchorPoint::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
}

QVariant AnchorPoint::itemChange(GraphicsItemChange change, const QVariant& value)
{
	if (change == QGraphicsItem::ItemPositionChange)
	{
		emit positionChanged(value.toPointF());
	}
	else if (change == QGraphicsItem::ItemScenePositionHasChanged)
	{
		emit positionChanged(value.toPointF());
	}

	return QGraphicsObject::itemChange(change, value);
}
