#pragma once

#include <QGraphicsScene>

class NewLinkHandler;

class CanvasScene : public QGraphicsScene
{
	Q_OBJECT
public:
	CanvasScene(QObject *parent = Q_NULLPTR);

public:


private:


protected:
	virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);

	virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event);

	virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);

protected:
	NewLinkHandler* __newLinkHandler;
};
