#pragma once

#include <QGraphicsWidget>

class NodeItemBody;
class SinkAnchorItem;
class SourceAnchorItem;
class NodeItemText;


class NodeItem : public QGraphicsWidget
{
	Q_OBJECT
public:
	NodeItem(const QString& caption, QGraphicsItem* parent = Q_NULLPTR, Qt::WindowFlags wFlags = Qt::WindowFlags());

public:
	void setProgress(int progress_);	

protected:
	virtual QPainterPath shape() const;

	virtual QRectF boundingRect() const;

	virtual QVariant itemChange(GraphicsItemChange change, const QVariant& value);

	virtual void focusInEvent(QFocusEvent* event);

	virtual void focusOutEvent(QFocusEvent* event);

protected:
	void __updateTitleText();

Q_SIGNALS:
	void positionChanged(QPointF);

public:
	QString				__caption;

	NodeItemBody*		__shapeItem;
	SinkAnchorItem*		__inputAnchorItem;
	SourceAnchorItem*	__outputAnchorItem;
	NodeItemText*		__captionTextItem;
};
