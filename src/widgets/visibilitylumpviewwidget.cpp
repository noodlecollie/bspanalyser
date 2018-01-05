#include "visibilitylumpviewwidget.h"
#include "ui_visibilitylumpviewwidget.h"
#include "visibilitychartrenderer.h"

#include "model/applicationmodel.h"
#include "bsp/viscompressor.h"

VisibilityLumpViewWidget::VisibilityLumpViewWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VisibilityLumpViewWidget),
    m_pNotesBox(new QTextEdit()),
    m_pLumpDef(),
    m_nLeafCount(0),
    m_pGraphicsScene(),
    m_bFitSceneInView(false)
{
    ui->setupUi(this);

    initInformationArea();
    initGraphicsScene();
}

VisibilityLumpViewWidget::~VisibilityLumpViewWidget()
{
    delete ui;
}

QWidget* VisibilityLumpViewWidget::asWidget()
{
    return this;
}

void VisibilityLumpViewWidget::loadLumpData(const QSharedPointer<BSPLumpDef>& lumpDef, const BSPDataFragment &fragment)
{
    // TODO
    Q_UNUSED(fragment)

    setLumpDef(lumpDef);
    m_liNotes.clear();

    calculateNumberOfLeaves();
    updateInformationArea();
}

void VisibilityLumpViewWidget::setLumpDef(const QSharedPointer<BSPLumpDef> &lumpDef)
{
    if ( !lumpDef || lumpDef->type() != BSPLumpDef::LumpType::VisData )
    {
        m_pLumpDef = QSharedPointer<VisibilityLumpDef>();
        return;
    }

    m_pLumpDef = lumpDef.staticCast<VisibilityLumpDef>();
}

void VisibilityLumpViewWidget::initGraphicsScene()
{
    ui->graphicsView->setScene(nullptr);
    m_pGraphicsScene.reset(createEmptyVisChart());
    ui->graphicsView->setScene(m_pGraphicsScene.data());
    m_bFitSceneInView = true;
}

void VisibilityLumpViewWidget::initInformationArea()
{
    QGridLayout* gridLayout = qobject_cast<QGridLayout*>(ui->gbInformation->layout());
    if ( !gridLayout )
    {
        return;
    }

    gridLayout->addWidget(m_pNotesBox, gridLayout->rowCount(), 0, 1, -1);

    m_pNotesBox->setVisible(false);
    m_pNotesBox->setReadOnly(true);
    m_pNotesBox->setFixedHeight(50);
    m_pNotesBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_pNotesBox->setLineWrapMode(QTextEdit::NoWrap);
}

void VisibilityLumpViewWidget::updateInformationArea()
{
    updateLabels();
    updateNotesBox();
}

void VisibilityLumpViewWidget::updateLabels()
{
    ui->lblBytesPerLine->setText(QString::number(VisCompressor::bytesRequiredPerCompressedRow(m_nLeafCount)));
    ui->lblTotalLeaves->setText(QString::number(m_nLeafCount));
}

void VisibilityLumpViewWidget::updateNotesBox()
{
    if ( m_liNotes.isEmpty() )
    {
        m_pNotesBox->clear();
        m_pNotesBox->setVisible(false);
        return;
    }

    QString list;

    for ( const QString& string : m_liNotes )
    {
        if ( !list.isEmpty() )
        {
            list += "<br/>";
        }

        list += "<span style=\"color:red;\">" + string + "</span>";
    }

    m_pNotesBox->setVisible(true);
    m_pNotesBox->setHtml("<p>" + list + "</p>");
}

void VisibilityLumpViewWidget::calculateNumberOfLeaves()
{
    if ( !m_pLumpDef )
    {
        m_nLeafCount = 0;
        return;
    }

    QSharedPointer<StructLumpDef> leavesLump = m_pLumpDef->leavesLump();
    if ( !leavesLump )
    {
        m_nLeafCount = 0;
        return;
    }

    BSPDataFragment leavesFragment = leavesLump->getDataFragment(ApplicationModel::globalPointer()->bspFileModel()->contents());
    quint32 structSize = leavesLump->bspStruct().size();
    quint32 lumpSize = leavesFragment.length();

    if ( lumpSize % structSize != 0 )
    {
        m_liNotes.append(QString("Leaves lump size (%0 bytes) was not a multiple of the leaf struct size (%1 bytes).")
                         .arg(lumpSize)
                         .arg(structSize));
    }

    m_nLeafCount = lumpSize / structSize;
}

QGraphicsScene* VisibilityLumpViewWidget::createEmptyVisChart()
{
    QGraphicsScene* scene = new QGraphicsScene();
    VisibilityChartRenderer renderer(*scene);

    /*if ( m_nLeafCount < 1 )
    {
        renderer.drawAxes(100, 100);
        return;
    }*/

    // TODO
    renderer.drawDefaultAxes();

    return scene;
}

void VisibilityLumpViewWidget::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);

    if ( m_bFitSceneInView )
    {
        if ( m_pGraphicsScene )
        {
            ui->graphicsView->fitInView(m_pGraphicsScene->sceneRect(), Qt::KeepAspectRatio);
        }

        m_bFitSceneInView = false;
    }
}
