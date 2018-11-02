#include "NodeItem.h"
#include "NodeItemBody.h"
#include "NodeItemAnchor.h"
#include "NodeItemText.h"
#include "AnchorPoint.h"
#include <QTextDocument>


NodeItem::NodeItem(const QString& caption, QGraphicsItem* parent, Qt::WindowFlags wFlags)
	:QGraphicsWidget(parent, wFlags), __caption(caption)
{
	setFocusPolicy(Qt::ClickFocus);
	setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
	setFlag(QGraphicsItem::ItemHasNoContents, true);
	setFlag(QGraphicsItem::ItemIsSelectable, true);
	setFlag(QGraphicsItem::ItemIsMovable, true);
	setFlag(QGraphicsItem::ItemIsFocusable, true);
	setZValue(0);

	__shapeItem = new NodeItemBody(this);
	__inputAnchorItem = new SinkAnchorItem(this);
	__outputAnchorItem = new SourceAnchorItem(this);
	__captionTextItem = new NodeItemText(this);

	__updateTitleText();
}

void NodeItem::setProgress(int progress_)
{
	__shapeItem->setProgress(progress_);
}

QVariant NodeItem::itemChange(GraphicsItemChange change, const QVariant& value)
{
	if (change == GraphicsItemChange::ItemSelectedChange)
	{
		bool selected = value.toBool();
		__shapeItem->setSelected(selected);
		__captionTextItem->setSelectionState(selected);
	}
	else if (change == GraphicsItemChange::ItemPositionHasChanged)
	{
		emit positionChanged(value.toPointF());
	}

	return QGraphicsWidget::itemChange(change, value);
}

void NodeItem::focusInEvent(QFocusEvent* event)
{
	__shapeItem->setHasFocus(true);
	QGraphicsWidget::focusInEvent(event);
}

void NodeItem::focusOutEvent(QFocusEvent* event)
{
	__shapeItem->setHasFocus(false);
	QGraphicsWidget::focusOutEvent(event);
}

void NodeItem::__updateTitleText()
{
	prepareGeometryChange();

	QString	text(QString("<div align=\"center\">%1").arg(__caption));

	int progress_ = __shapeItem->progress();
	if (progress_)
	{
		text.append(QString("<span style=\"font - style: italic\">%1%%</span>").arg(progress_));
	}
	text.append("</div>");

	__captionTextItem->setHtml(text);
	__captionTextItem->document()->adjustSize();
	__captionTextItem->setPos(-__captionTextItem->textWidth() / 2., 33);
}

QPainterPath NodeItem::shape() const
{
	return __shapeItem->shape();
}

QRectF NodeItem::boundingRect() const
{
	return childrenBoundingRect();
}
