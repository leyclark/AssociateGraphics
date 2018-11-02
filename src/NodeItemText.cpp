#include "NodeItemText.h"
#include <QPainter>
#include <QTextDocument>
#include <QTextBlock>


NodeItemText::NodeItemText(QGraphicsItem *parent)
	:QGraphicsTextItem(parent)
{
	__selected = false;
}

void NodeItemText::setSelectionState(bool state)
{
	if (__selected != state)
	{
		__selected = state;
		__updateDefaultTextColor();
		update();
	}
}

void NodeItemText::setPallate(QPalette palette_)
{
	__palette = palette_;
	__updateDefaultTextColor();
	update();
}

QPalette NodeItemText::palette() const
{
	return __palette;
}

void NodeItemText::setHtml(QString contents)
{
	if (__content != contents)
	{
		__content = contents;
		QGraphicsTextItem::setHtml(contents);
	}
}

void NodeItemText::__updateDefaultTextColor()
{
	setDefaultTextColor(__palette.color(__selected ? QPalette::HighlightedText : QPalette::WindowText));
}

void NodeItemText::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	if (__selected)
	{
		painter->save();
		painter->setPen(QPen(Qt::NoPen));
		painter->setBrush(palette().color(QPalette::Highlight));
		QTextDocument* doc = document();
		double margin = doc->documentMargin();
		painter->translate(margin, margin);
		double offset = qMin(margin, 2.0);
		for (QTextBlock block = doc->begin(); block != doc->end(); block = block.next())
		{
			for (int i = 0; i < block.layout()->lineCount(); ++i)
			{
				QTextLine line = block.layout()->lineAt(i);

				QRectF rect = line.naturalTextRect();
				painter->drawRoundedRect(rect.adjusted(-offset, -offset, offset, offset), 3, 3);
			}
		}
		painter->restore();
	}

	QGraphicsTextItem::paint(painter, option, widget);
}
