#pragma once

#include <QPalette>
#include <QGraphicsTextItem>


class NodeItemText : public QGraphicsTextItem
{
	Q_OBJECT
public:
	NodeItemText(QGraphicsItem *parent = Q_NULLPTR);

public:
	void setSelectionState(bool state);

	void setPallate(QPalette palette_);

	QPalette palette() const;

	void setHtml(QString contents);

private:
	void __updateDefaultTextColor();

private:
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

private:
	bool		__selected;
	QPalette	__palette;
	QString		__content;
};
