#include "GraphicsPathObject.h"
#include <QPainter>
#include <QPainterPathStroker>

GraphicsPathObject::GraphicsPathObject(QGraphicsItem* parent)
	:QGraphicsObject(parent), __pen(Qt::NoPen)
{
	setFlag(QGraphicsObject::ItemSendsGeometryChanges);
}

void GraphicsPathObject::setPath(const QPainterPath& painterPath)
{
	prepareGeometryChange();
	__path = painterPath;
	update();
}

QPainterPath GraphicsPathObject::path() const
{
	return __path;
}

void GraphicsPathObject::setBrush(const QBrush& brush)
{
	__brush = brush;
	update();
}

QBrush GraphicsPathObject::brush() const
{
	return __brush;
}

void GraphicsPathObject::setPen(const QPen& pen)
{
	__pen = pen;
	update();
}

QPen GraphicsPathObject::pen() const
{
	return __pen;
}

QPainterPath GraphicsPathObject::shape() const
{
	QPainterPathStroker stroker;
	stroker.setCapStyle(__pen.capStyle());
	stroker.setJoinStyle(__pen.joinStyle());
	stroker.setMiterLimit(__pen.miterLimit());
	stroker.setWidth(qMax(__pen.widthF(), 1e-9));

	QPainterPath shape = stroker.createStroke(__path);
	shape.addPath(__path);

	return shape;
}

QRectF GraphicsPathObject::boundingRect() const
{
	QRectF br = __path.controlPointRect();
	double pen_w = __pen.widthF();
	return br.adjusted(-pen_w, -pen_w, pen_w, pen_w);
}

QVariant GraphicsPathObject::itemChange(GraphicsItemChange change, const QVariant& value)
{
	if (change == QGraphicsItem::ItemPositionHasChanged)
	{
		emit positionChanged(value.toPointF());
	}

	return QGraphicsObject::itemChange(change, value);
}

void GraphicsPathObject::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	painter->save();
	painter->setPen(__pen);
	painter->setBrush(__brush);
	painter->drawPath(__path);
	painter->restore();
}
