#include "LinkItemIndicator.h"
#include <QPen>
#include <QPainter>
#include <QStyleOptionGraphicsItem>


LinkItemIndicator::LinkItemIndicator(QGraphicsItem* parent)
	:QGraphicsEllipseItem(parent)
{
}

void LinkItemIndicator::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget *widget)
{
	bool hover = option->state & QStyle::State_MouseOver;
	QColor normal = QColor("#9CACB4");

	painter->save();
	painter->setPen(QPen(Qt::NoPen));	
	painter->setBrush(QBrush(hover ? normal.darker(110) : normal));
	painter->drawEllipse(QRectF(-3.5, -3.5, 7, 7));
	painter->restore();
}
