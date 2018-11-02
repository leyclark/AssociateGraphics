#pragma once

class CanvasScene;
class NodeItem;
class NodeItemAnchor;
class AnchorPoint;
class LinkItem;
class QGraphicsSceneMouseEvent;


class NewLinkHandler
{
public:
	NewLinkHandler(CanvasScene* scene);

public:
	void handleMousePress(QGraphicsSceneMouseEvent* event);

	void handleMouseMove(QGraphicsSceneMouseEvent* event);

	void handleMouseRelease(QGraphicsSceneMouseEvent* event);

protected:
	CanvasScene*	__scene;
	LinkItem*		__linkItemTemp;

	bool			__isSouceAnchor;

	NodeItem*		__sourceNodeItem;
	NodeItemAnchor*	__sourceNodeAnchor;
	NodeItem*		__sinkNodeItem;
	NodeItemAnchor* __sinkNodeAnchor;

	AnchorPoint*	__nodeAnchorPoint;
	AnchorPoint*	__cursorAnchorPoint;
	AnchorPoint*	__mouseMoveAnchorPoint;
};
