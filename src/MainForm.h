#pragma once

#include <QWidget>
#include "ui_MainForm.h"

namespace Ui {
	class MainFormClass;
}
class CanvasScene;


class MainForm : public QWidget
{
    Q_OBJECT
public:
    MainForm(QWidget *parent = Q_NULLPTR);
	~MainForm();	

private:
    Ui::MainFormClass* ui;
	CanvasScene* scene;
};
