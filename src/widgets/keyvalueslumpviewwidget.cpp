#include "keyvalueslumpviewwidget.h"
#include "ui_keyvalueslumpviewwidget.h"

KeyValuesLumpViewWidget::KeyValuesLumpViewWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::KeyValuesLumpViewWidget)
{
    ui->setupUi(this);
}

KeyValuesLumpViewWidget::~KeyValuesLumpViewWidget()
{
    delete ui;
}

QWidget* KeyValuesLumpViewWidget::asWidget()
{
    return this;
}

void KeyValuesLumpViewWidget::loadLumpData(const QSharedPointer<BSPLumpDef> &lumpDef, const BSPDataFragment &fragment)
{
    Q_UNUSED(lumpDef);

    QByteArray lumpData = fragment.data();
    ui->lblSize->setText(tr("Total size: %0 bytes").arg(lumpData.count()));

    QString errorString;
    ui->kvView->loadLumpData(lumpData, errorString);

    if ( !errorString.isEmpty() )
    {
        ui->gbInformation->displayError(errorString);
    }
}
