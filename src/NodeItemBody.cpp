#include "NodeItemBody.h"
#include <QPainter>
#include <QGraphicsDropShadowEffect>
#include <QPropertyAnimation>
#include <QStyleOptionGraphicsItem>


QColor saturated(QColor color, int factor = 150)
{
	double h = color.hsvHueF();
	double s = color.hsvSaturationF();
	double v = color.valueF();
	double a = color.alphaF();
	s = factor * s / 100.0;
	s = qMax(qMin(1.0, s), 0.0);
	return QColor::fromHsvF(h, s, v, a).convertTo(color.spec());
}

QRadialGradient radial_gradient(QColor color, QColor color_light)
{
	QRadialGradient gradient = QRadialGradient(0.5, 0.5, 0.5);
	gradient.setColorAt(0.0, color_light);
	gradient.setColorAt(0.5, color_light);
	gradient.setColorAt(1.0, color);
	gradient.setCoordinateMode(QRadialGradient::ObjectBoundingMode);
	return gradient;
}

static QRadialGradient color_node_body_selected = radial_gradient(QColor("#FFA840"), saturated(QColor("#FFA840"), 50));
static QRadialGradient color_node_body_normal = radial_gradient(QColor("#FFD39F"), saturated(QColor("#FFD39F"), 50));


NodeItemBody::NodeItemBody(QGraphicsItem* parent)
	:GraphicsPathObject(parent),
	__isSelected(false),
	__hasFocus(false),
	__hover(false),
	__progress(0)
{
	setAcceptHoverEvents(true);
	setFlag(QGraphicsItem::ItemSendsScenePositionChanges, true);
	setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);

	QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect(this);
	shadow->setBlurRadius(17);
	shadow->setColor(QColor("#9CACB4"));
	shadow->setOffset(QPointF(0, 0));
	shadow->setEnabled(false);
	setGraphicsEffect(shadow);

	setShapeRect(QRectF(-24, -24, 48, 48));
	__updateBrush();
}

void NodeItemBody::setShapeRect(QRectF rect)
{
	__shapeRect = rect;

	QPainterPath path;
	path.addEllipse(rect);
	setPath(path);
}

void NodeItemBody::setProgress(int progress)
{
	__progress = progress;
	update();
}

int NodeItemBody::progress() const
{
	return __progress;
}

void NodeItemBody::setSelected(bool selected)
{
	__isSelected = selected;
	__updateBrush();
}

void NodeItemBody::setHasFocus(bool focus)
{
	__hasFocus = focus;
	__updatePen();
}

void NodeItemBody::__updateBrush()
{
	setBrush(QBrush(__isSelected ? color_node_body_selected : color_node_body_normal));
}

void NodeItemBody::__updatePen()
{
	setPen(__hasFocus ? QPen(QColor("#609ED7"), 1.5) : QPen(Qt::NoPen));
}

void NodeItemBody::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
	graphicsEffect()->setEnabled(true);
	GraphicsPathObject::hoverEnterEvent(event);
}

void NodeItemBody::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
	graphicsEffect()->setEnabled(false);
	GraphicsPathObject::hoverLeaveEvent(event);
}

void NodeItemBody::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	GraphicsPathObject::paint(painter, option, widget);

	if (__progress)
	{
		painter->save();
		painter->setClipPath(shape(), Qt::ReplaceClip);
		QColor color("#515151");
		QPen pen = QPen(color, 5);
		painter->setPen(pen);
		painter->setRenderHints(QPainter::Antialiasing);
		int span = qMax(1, int(__progress * 57.60));
		painter->drawArc(__shapeRect, 90 * 16, -span);
		painter->restore();
	}
}
