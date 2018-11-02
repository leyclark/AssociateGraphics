#pragma once

#include <QBrush>
#include <QPen>
#include <QGraphicsObject>


class GraphicsPathObject : public QGraphicsObject
{
	Q_OBJECT
public:
	GraphicsPathObject(QGraphicsItem* parent = Q_NULLPTR);

public:
	void setPath(const QPainterPath& painterPath);

	QPainterPath path() const;

	void setBrush(const QBrush& brush);

	QBrush brush() const;

	void setPen(const QPen& pen);

	QPen pen() const;

Q_SIGNALS:
	void positionChanged(QPointF);

public:
	virtual QPainterPath shape() const;

protected:
	virtual QRectF boundingRect() const;

	virtual QVariant itemChange(GraphicsItemChange change, const QVariant& value);

	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

protected:
	QPainterPath	__path;
	QBrush			__brush;
	QPen			__pen;
};
