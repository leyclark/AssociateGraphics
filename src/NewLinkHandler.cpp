#include "NewLinkHandler.h"
#include "CanvasScene.h"
#include "NodeItem.h"
#include "NodeItemAnchor.h"
#include "AnchorPoint.h"
#include "LinkItem.h"
#include <QGraphicsSceneMouseEvent>


NewLinkHandler::NewLinkHandler(CanvasScene* scene)
	:__scene(scene),
	__linkItemTemp(Q_NULLPTR),
	__isSouceAnchor(true),
	__sourceNodeItem(Q_NULLPTR),
	__sourceNodeAnchor(Q_NULLPTR),
	__sinkNodeItem(Q_NULLPTR),
	__sinkNodeAnchor(Q_NULLPTR),
	__nodeAnchorPoint(Q_NULLPTR),
	__cursorAnchorPoint(Q_NULLPTR),
	__mouseMoveAnchorPoint(Q_NULLPTR)
{
}

void NewLinkHandler::handleMousePress(QGraphicsSceneMouseEvent* event)
{
	QPointF mousePoint = event->scenePos();
	QGraphicsItem* item = __scene->itemAt(mousePoint, QTransform());
	NodeItemAnchor* itemAnchor = dynamic_cast<NodeItemAnchor*>(item);
	if (itemAnchor)
	{
		__isSouceAnchor = itemAnchor->isSourceAnchor();
		if (__isSouceAnchor)
		{
			__sourceNodeAnchor = itemAnchor;
			__sourceNodeItem = (NodeItem*)(itemAnchor->parentItem());
		}
		else
		{
			__sinkNodeAnchor = itemAnchor;
			__sinkNodeItem = (NodeItem*)(itemAnchor->parentItem());
		}

		__nodeAnchorPoint = new AnchorPoint(itemAnchor);
		__nodeAnchorPoint->setPos(mousePoint);
		itemAnchor->addAnchor(__nodeAnchorPoint);

		event->accept();
	}
}

void NewLinkHandler::handleMouseMove(QGraphicsSceneMouseEvent* event)
{
	if (__nodeAnchorPoint)
	{
		QPointF mousePoint = event->scenePos();

		if (!__linkItemTemp)
		{
			__linkItemTemp = new LinkItem;
			__cursorAnchorPoint = new AnchorPoint;
			__mouseMoveAnchorPoint = new AnchorPoint;
			
			if (__isSouceAnchor)
			{
				__linkItemTemp->setSourceItem(__nodeAnchorPoint, true);
				__linkItemTemp->setSinkItem(__cursorAnchorPoint, false);
			}
			else
			{
				__linkItemTemp->setSinkItem(__nodeAnchorPoint, true);
				__linkItemTemp->setSourceItem(__cursorAnchorPoint, false);
			}
			__scene->addItem(__linkItemTemp);
		}

		if (__isSouceAnchor)
		{
			if (__sinkNodeAnchor)
			{
				__sinkNodeAnchor->removeAnchor(__mouseMoveAnchorPoint);
				__sinkNodeAnchor = Q_NULLPTR;
				__sinkNodeItem = Q_NULLPTR;
			}
		}
		else
		{
			if (__sourceNodeAnchor)
			{
				__sourceNodeAnchor->removeAnchor(__mouseMoveAnchorPoint);
				__sourceNodeAnchor = Q_NULLPTR;
				__sourceNodeItem = Q_NULLPTR;
			}
		}

		QGraphicsItem* item = __scene->itemAt(mousePoint, QTransform());
		NodeItemAnchor* itemAnchor = dynamic_cast<NodeItemAnchor*>(item);
		if (itemAnchor && itemAnchor->isSourceAnchor() != __isSouceAnchor)
		{
			NodeItem* nodeItem = (NodeItem*)itemAnchor->parentItem();
			if (nodeItem != (__isSouceAnchor ? __sourceNodeItem : __sinkNodeItem))
			{
				__mouseMoveAnchorPoint->setParentItem(itemAnchor);
				__mouseMoveAnchorPoint->setPos(mousePoint);
				itemAnchor->addAnchor(__mouseMoveAnchorPoint);

				if (__isSouceAnchor)
				{
					__sinkNodeAnchor = itemAnchor;
					__sinkNodeItem = nodeItem;
					__linkItemTemp->setSinkItem(__mouseMoveAnchorPoint, true);
				}
				else
				{
					__sourceNodeAnchor = itemAnchor;
					__sourceNodeItem = nodeItem;
					__linkItemTemp->setSourceItem(__mouseMoveAnchorPoint, true);
				}

				event->accept();
				return;
			}
		}

		__cursorAnchorPoint->setPos(event->scenePos());
		if (__isSouceAnchor)
		{
			__linkItemTemp->setSinkItem(__cursorAnchorPoint, false);
		}
		else
		{
			__linkItemTemp->setSourceItem(__cursorAnchorPoint, false);
		}
	}
}

void NewLinkHandler::handleMouseRelease(QGraphicsSceneMouseEvent* event)
{
	NodeItem* nodeItem = __isSouceAnchor ? __sinkNodeItem : __sourceNodeItem;
	if (!nodeItem)
	{
		// «Â¿Ì
		if (__linkItemTemp)
		{
			delete __linkItemTemp;
			delete __nodeAnchorPoint;
			delete __cursorAnchorPoint;
			delete __mouseMoveAnchorPoint;
		}
	}
}
