#include "LinkItem.h"
#include "LinkItemCurve.h"
#include "LinkItemIndicator.h"
#include "AnchorPoint.h"
#include <QtMath>
#include <QPen>
#include <QGraphicsTextItem>


LinkItem::LinkItem(QGraphicsItem* parent, Qt::WindowFlags wFlags)
	:QGraphicsWidget(parent, wFlags), __sourceAnchor(Q_NULLPTR), __sinkAnchor(Q_NULLPTR)
{
	setFlag(QGraphicsItem::ItemHasNoContents, true);
	setAcceptedMouseButtons(Qt::RightButton | Qt::LeftButton);
	setAcceptHoverEvents(true);
	setZValue(0);

	__sourceIndicator = new LinkItemIndicator(this);
	__sourceIndicator->hide();
	__curveItem = new LinkItemCurve(this);
	__sinkIndicator = new LinkItemIndicator(this);
	__sinkIndicator->hide();

// 	__linkTextItem = new QGraphicsTextItem(this);
// 	__linkTextItem->setAcceptedMouseButtons(Qt::NoButton);
// 	__linkTextItem->setAcceptHoverEvents(false);
}

void LinkItem::setSourceItem(AnchorPoint* anchor, bool showIndicate)
{
	disconnect(__sourceAnchor, SIGNAL(positionChanged(QPointF)), this, SLOT(__updateCurve()));
	__sourceAnchor = anchor;
	__sourceIndicator->setVisible(showIndicate);
	connect(__sourceAnchor, SIGNAL(positionChanged(QPointF)), this, SLOT(__updateCurve()));

	__updateCurve();
}

void LinkItem::setSinkItem(AnchorPoint* anchor, bool showIndicate)
{
	disconnect(__sinkAnchor, SIGNAL(positionChanged(QPointF)), this, SLOT(__updateCurve()));
	__sinkAnchor = anchor;
	__sinkIndicator->setVisible(showIndicate);
	connect(__sinkAnchor, SIGNAL(positionChanged(QPointF)), this, SLOT(__updateCurve()));

	__updateCurve();
}

QPainterPath LinkItem::shape() const
{
	return __curveItem->shape();
}

QRectF LinkItem::boundingRect() const
{
	return childrenBoundingRect();
}

void LinkItem::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
	__curveItem->setHoverState(true);
	QGraphicsWidget::hoverEnterEvent(event);
}

void LinkItem::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
	__curveItem->setHoverState(false);
	QGraphicsWidget::hoverLeaveEvent(event);
}

void LinkItem::__updateCurve()
{
	prepareGeometryChange();

	if (__sourceAnchor && __sinkAnchor)
	{
		QPointF source_pos = __curveItem->mapFromScene(__sourceAnchor->scenePos());
		QPointF sink_pos = __curveItem->mapFromScene(__sinkAnchor->scenePos());

		QPointF delta = source_pos - sink_pos;
		double dist = qSqrt(delta.x() * delta.x() + delta.y() * delta.y());
		double cp_offset = qMin(dist / 2.0, 60.0);

		QPainterPath path;
		path.moveTo(source_pos);
		path.cubicTo(source_pos + QPointF(cp_offset, 0), sink_pos - QPointF(cp_offset, 0), sink_pos);
		__curveItem->setCurvePath(path);
		__sourceIndicator->setPos(source_pos);
		__sinkIndicator->setPos(sink_pos);
	}
	else
	{

	}
}
