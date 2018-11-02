#include "MainForm.h"
#include "CanvasScene.h"
#include "NodeItem.h"


MainForm::MainForm(QWidget *parent)
	: QWidget(parent), ui(new Ui::MainFormClass)
{
	ui->setupUi(this);
	ui->graphicsView->setRenderHint(QPainter::Antialiasing);

	scene = new CanvasScene();
	ui->graphicsView->setScene(scene);
}

MainForm::~MainForm()
{
	delete ui;
	delete scene;
}
