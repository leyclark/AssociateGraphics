#include "NodeItemAnchor.h"
#include "AnchorPoint.h"
#include <QGraphicsDropShadowEffect>

static QBrush brush_node_anchor_normal(QColor("#CDD5D9"));
static QBrush brush_node_anchor_connected(QColor("#9CACB4"));


NodeItemAnchor::NodeItemAnchor(bool isSource, QGraphicsItem* parent)
	:GraphicsPathObject(parent), __source(isSource)
{
	setAcceptHoverEvents(true);

	QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect(this);
	shadow->setBlurRadius(10);
	shadow->setColor(QColor("#9CACB4"));
	shadow->setOffset(QPointF(0, 0));
	shadow->setEnabled(false);
	setGraphicsEffect(shadow);

	setAnchorRect(QRectF(-31, -31, 62, 62));
	__updateBrush();
}

void NodeItemAnchor::setAnchorRect(const QRectF& anchorRect)
{
	double startAngle = __source ? 45 : 135;
	double sweepLength = __source ? -90 : 90;

	__auchorPath = QPainterPath();
	__auchorPath.arcMoveTo(anchorRect, startAngle);
	__auchorPath.arcTo(anchorRect, startAngle, sweepLength);

	QPainterPathStroker stroke_path;
	stroke_path.setCapStyle(Qt::RoundCap);
	stroke_path.setWidth(12);
	__shape = stroke_path.createStroke(__auchorPath);

	stroke_path.setWidth(3);
	__fullStroke = stroke_path.createStroke(__auchorPath);

	stroke_path.setDashPattern(Qt::DotLine);
	__dottedStroke = stroke_path.createStroke(__auchorPath);
}

void NodeItemAnchor::addAnchor(AnchorPoint* anchor)
{
	anchor->setParentItem(this);
	__points.append(anchor);
	connect(anchor, SIGNAL(destroyed()), this, SLOT(__destroyAnchor()));

	__updateAnchorPos();
	__updateBrush();
}

void NodeItemAnchor::removeAnchor(AnchorPoint* anchor)
{
	__points.removeAll(anchor);

	__updateAnchorPos();
	__updateBrush();
}

QPainterPath NodeItemAnchor::shape() const
{
	return __shape;
}

void NodeItemAnchor::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
	graphicsEffect()->setEnabled(true);
	GraphicsPathObject::hoverEnterEvent(event);
}

void NodeItemAnchor::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
	graphicsEffect()->setEnabled(false);
	GraphicsPathObject::hoverLeaveEvent(event);
}

void NodeItemAnchor::__destroyAnchor()
{
	removeAnchor((AnchorPoint*)sender());
}

void NodeItemAnchor::__updateBrush()
{
	if (__points.isEmpty())
	{
		setPath(__dottedStroke);
		setBrush(brush_node_anchor_normal);
	}
	else
	{
		setPath(__fullStroke);
		setBrush(brush_node_anchor_connected);
	}
}

void NodeItemAnchor::__updateAnchorPos()
{
	double per = 1. / (__points.size() + 1);
	for (int i = 0; i < __points.size(); ++i)
	{
		__points[i]->setPos(__auchorPath.pointAtPercent((i + 1) * per));
	}
}
