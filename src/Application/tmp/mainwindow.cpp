#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ViewerWidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	ViewerWidget *widget = new ViewerWidget;
	setCentralWidget(widget);
}

MainWindow::~MainWindow()
{
    delete ui;
}
