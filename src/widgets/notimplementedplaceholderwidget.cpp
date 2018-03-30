#include "notimplementedplaceholderwidget.h"
#include "ui_notimplementedplaceholderwidget.h"

NotImplementedPlaceholderWidget::NotImplementedPlaceholderWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NotImplementedPlaceholderWidget)
{
    ui->setupUi(this);
}

NotImplementedPlaceholderWidget::~NotImplementedPlaceholderWidget()
{
    delete ui;
}
