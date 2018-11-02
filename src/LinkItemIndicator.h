#pragma once

#include <QGraphicsEllipseItem>


class LinkItemIndicator : public QGraphicsEllipseItem
{
public:
	LinkItemIndicator(QGraphicsItem* parent = Q_NULLPTR);

protected:
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget *widget);
};
