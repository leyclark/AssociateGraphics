#pragma once

#include "GraphicsPathObject.h"


class NodeItemBody : public GraphicsPathObject
{
	Q_OBJECT
public:
	NodeItemBody(QGraphicsItem* parent = Q_NULLPTR);

public:
	void setShapeRect(QRectF rect);

	void setProgress(int progress);

	int progress() const;

	void setSelected(bool selected);

	void setHasFocus(bool focus);

protected:
	void __updatePen();

	void __updateBrush();

protected:
	virtual void hoverEnterEvent(QGraphicsSceneHoverEvent* event);

	virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);

	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

protected:
	QRectF	__shapeRect;

	bool	__isSelected;
	bool	__hasFocus;
	bool	__hover;

	int		__progress;
};
