#pragma once

#include <QGraphicsWidget>

class NodeItem;
class AnchorPoint;
class SourceAnchorItem;
class SinkAnchorItem;
class LinkItemCurve;
class LinkItemIndicator;

class LinkItem : public QGraphicsWidget
{
	Q_OBJECT
public:
	LinkItem(QGraphicsItem* parent = Q_NULLPTR, Qt::WindowFlags wFlags = Qt::WindowFlags());

public:
	void setSourceItem(AnchorPoint* anchor, bool showIndicate);

	void setSinkItem(AnchorPoint* anchor, bool showIndicate);

protected:
	virtual QPainterPath shape() const;

	virtual QRectF boundingRect() const;

	virtual void hoverEnterEvent(QGraphicsSceneHoverEvent* event);

	virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);

protected Q_SLOTS:
	void __updateCurve();

protected:
	AnchorPoint*		__sourceAnchor;
	AnchorPoint*		__sinkAnchor;

	LinkItemIndicator*	__sourceIndicator;
	LinkItemCurve*		__curveItem;
	LinkItemIndicator*	__sinkIndicator;
// 	QGraphicsTextItem*	__linkTextItem;
};
