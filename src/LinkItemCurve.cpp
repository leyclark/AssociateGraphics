#include "LinkItemCurve.h"
#include <QPen>
#include <QGraphicsDropShadowEffect>
#include <QPainterPathStroker>


LinkItemCurve::LinkItemCurve(QGraphicsItem* parent)
	:QGraphicsPathItem(parent)
{
	setAcceptedMouseButtons(Qt::NoButton);
	setAcceptHoverEvents(true);

	QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect;
	shadow->setBlurRadius(10);
	shadow->setColor(QColor("#9CACB4"));
	shadow->setOffset(QPointF(0, 0));
	shadow->setEnabled(false);
	setGraphicsEffect(shadow);

	__hover = false;
	__enabled = true;
	setPen(QPen(QBrush(QColor("#9CACB4")), 2.0));
}

void LinkItemCurve::setHoverState(bool hover)
{
	QGraphicsEffect* shadow = graphicsEffect();
	if (shadow->isEnabled() != hover)
	{
		shadow->setEnabled(hover);
	}
}

void LinkItemCurve::setCurvePath(const QPainterPath& path)
{
	prepareGeometryChange();
	__curvepath = path;
	setPath(__curvepath);
}

QPainterPath LinkItemCurve::shape() const
{
	return __curvepath;
}
