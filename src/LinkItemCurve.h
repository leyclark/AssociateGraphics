#pragma once

#include <QGraphicsPathItem>


class LinkItemCurve : public QGraphicsPathItem
{
public:
	LinkItemCurve(QGraphicsItem* parent = Q_NULLPTR);

public:
	void setHoverState(bool hover);

	void setCurvePath(const QPainterPath& path);

	QPainterPath shape() const;

protected:
	bool __hover;
	bool __enabled;
	
	QPainterPath __curvepath;
};
