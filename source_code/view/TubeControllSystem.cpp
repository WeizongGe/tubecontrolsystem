#include "TubeControllSystem.h"
#include "ui_TubeControllSystem.h"
// #define _DEBUG

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);
}

MainWidget::~MainWidget()
{
    delete ui;
}

//void MainWidget::paintEvent(QPaintEvent *event)
//{
//    QWidget::paintEvent(event);
////    static int i = 2;
////    qDebug()<<i;
////    ++i;
//}
