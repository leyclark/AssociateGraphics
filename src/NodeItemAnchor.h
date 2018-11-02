#pragma once

#include "GraphicsPathObject.h"

class AnchorPoint;


class NodeItemAnchor : public GraphicsPathObject
{
	Q_OBJECT
public:
	NodeItemAnchor(bool isSource, QGraphicsItem* parent = Q_NULLPTR);

public:
	bool isSourceAnchor() const	{ return __source; }

	void setAnchorRect(const QRectF& anchorRect);

	void addAnchor(AnchorPoint* anchor);

	void removeAnchor(AnchorPoint* anchor);

	virtual QPainterPath shape() const;

protected:
	virtual void hoverEnterEvent(QGraphicsSceneHoverEvent* event);

	virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);

protected Q_SLOTS:
	void __destroyAnchor();

protected:
	void __updateBrush();

	void __updateAnchorPos();

protected:
	bool	__source;

	QPainterPath __shape;
	QPainterPath __auchorPath;
	QPainterPath __dottedStroke;
	QPainterPath __fullStroke;

	QList<AnchorPoint*>	__points;
};


class SourceAnchorItem : public NodeItemAnchor
{
	Q_OBJECT
public:
	SourceAnchorItem(QGraphicsItem* parent = Q_NULLPTR)
		:NodeItemAnchor(true, parent)
	{
	}
};


class SinkAnchorItem : public NodeItemAnchor
{
	Q_OBJECT
public:
	SinkAnchorItem(QGraphicsItem* parent = Q_NULLPTR)
		:NodeItemAnchor(false, parent)
	{
	}
};
