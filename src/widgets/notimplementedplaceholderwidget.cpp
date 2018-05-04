#include "notimplementedplaceholderwidget.h"
#include "ui_notimplementedplaceholderwidget.h"

NotImplementedPlaceholderWidget::NotImplementedPlaceholderWidget(const QString& description, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NotImplementedPlaceholderWidget)
{
    ui->setupUi(this);

    if ( !description.isEmpty() )
    {
        ui->description->setText(description);
    }
    else
    {
        ui->line->setVisible(false);
    }
}

NotImplementedPlaceholderWidget::~NotImplementedPlaceholderWidget()
{
    delete ui;
}

QWidget* NotImplementedPlaceholderWidget::asWidget()
{
    return this;
}

void NotImplementedPlaceholderWidget::loadLumpData(const QSharedPointer<BSPLumpDef> &lumpDef, const BSPDataFragment &fragment)
{
    Q_UNUSED(lumpDef);
    Q_UNUSED(fragment);
}

