#include "CanvasScene.h"
#include "NodeItem.h"
#include "NodeItemAnchor.h"
#include "AnchorPoint.h"
#include "NewLinkHandler.h"
#include <QGraphicsSceneMouseEvent>


CanvasScene::CanvasScene(QObject *parent)
	:QGraphicsScene(parent), __newLinkHandler(Q_NULLPTR)
{
	NodeItem* node = new NodeItem(QStringLiteral("·¢ÉäÆ÷"));
	addItem(node);
	node->setPos(0, 0);

	NodeItem* node2 = new NodeItem(QStringLiteral("½ÓÊÕÆ÷"));
	addItem(node2);
	node2->setPos(100, 100);
}

void CanvasScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	QPointF pos = event->scenePos();
	QGraphicsItem* item = itemAt(pos, QTransform());
	NodeItemAnchor* itemAnchor = dynamic_cast<NodeItemAnchor*>(item);
	if (itemAnchor && event->button() == Qt::LeftButton)
	{
		if (!__newLinkHandler)
		{
			__newLinkHandler = new NewLinkHandler(this);
			__newLinkHandler->handleMousePress(event);
		}
	}

	QGraphicsScene::mousePressEvent(event);
}

void CanvasScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
	if (__newLinkHandler)
	{
		__newLinkHandler->handleMouseMove(event);
	}

	QGraphicsScene::mouseMoveEvent(event);
}

void CanvasScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
	if (__newLinkHandler)
	{
		__newLinkHandler->handleMouseRelease(event);

		delete __newLinkHandler;
		__newLinkHandler = Q_NULLPTR;
	}

	QGraphicsScene::mouseReleaseEvent(event);
}
