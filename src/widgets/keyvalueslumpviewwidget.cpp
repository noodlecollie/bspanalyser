#include "keyvalueslumpviewwidget.h"

#include <QVBoxLayout>
#include <QGroupBox>
#include <QHeaderView>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>

#include "util/textutil.h"
#include "bsp/keyvaluesjsonconverter.h"

namespace
{
    enum TreeColumn
    {
        KeyColumn,
        ValueColumn,

        TreeColumnCount
    };
}

Q_LOGGING_CATEGORY(lcKeyValuesLumpView, "KeyValuesLumpView")

KeyvaluesLumpViewWidget::KeyvaluesLumpViewWidget(QWidget *parent) :
    QWidget(parent),
    m_pSplitter(new QSplitter()),
    m_pTreeView(new QTreeWidget()),
    m_pRawView(new QPlainTextEdit())
{
    initTree();
    initRaw();

    QVBoxLayout* vLayout = new QVBoxLayout();
    vLayout->setMargin(0);
    vLayout->addWidget(m_pSplitter);
    setLayout(vLayout);
}

KeyvaluesLumpViewWidget::~KeyvaluesLumpViewWidget()
{
}

QWidget* KeyvaluesLumpViewWidget::asWidget()
{
    return this;
}

void KeyvaluesLumpViewWidget::loadLumpData(const QSharedPointer<BSPLumpDef>& lumpDef, const BSPDataFragment &fragment)
{
    Q_UNUSED(lumpDef);

    QByteArray lumpData = fragment.data();
    m_pRawView->setPlainText(lumpData.constData());

    bool success = loadKeyvaluesDataIntoTree(lumpData);
    m_pTreeView->parentWidget()->setVisible(success);
}

void KeyvaluesLumpViewWidget::initTree()
{
    initWithGroupBox(tr("Data"), m_pTreeView);

    m_pTreeView->setAnimated(true);
    m_pTreeView->setColumnCount(TreeColumnCount);
    m_pTreeView->setHeaderLabels(QStringList() << tr("Key") << tr("Value"));
    m_pTreeView->setUniformRowHeights(true);
}

void KeyvaluesLumpViewWidget::initRaw()
{
    initWithGroupBox(tr("Raw"), m_pRawView);

    m_pRawView->setLineWrapMode(QPlainTextEdit::NoWrap);
    m_pRawView->setReadOnly(true);
    m_pRawView->setFont(TextUtil::monospacedFont(10));
}

void KeyvaluesLumpViewWidget::initWithGroupBox(const QString &title, QWidget *widget)
{
    QGroupBox* groupBox = new QGroupBox(title);
    QVBoxLayout* vLayout = new QVBoxLayout();

    vLayout->setMargin(0);
    vLayout->addWidget(widget);
    groupBox->setLayout(vLayout);

    m_pSplitter->addWidget(groupBox);
}

bool KeyvaluesLumpViewWidget::loadKeyvaluesDataIntoTree(const QByteArray &kv)
{
    m_pTreeView->clear();

    KeyValuesJsonConverter converter;
    QByteArray json;
    QString errorString;

    if ( !converter.convert(kv, json, errorString) )
    {
        qCWarning(lcKeyValuesLumpView) << "Error converting KeyValues data." << errorString;
        return false;
    }

    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(json, &parseError);

    if ( parseError.error != QJsonParseError::NoError )
    {
        qCWarning(lcKeyValuesLumpView) << "Error parsing converted KeyValues data." << parseError.errorString();
        return false;
    }

    QJsonArray rootArray = jsonDoc.array();
    for ( int index = 0; index < rootArray.count(); ++index )
    {
        QJsonValue item = rootArray[index];
        if ( item.type() != QJsonValue::Object )
        {
            continue;
        }

        QJsonObject object = item.toObject();
        QJsonValue classname = object["classname"];
        QJsonValue targetname = object["targetname"];

        QString column1 = "[unknown class]";
        QString column2;

        if ( targetname.isString() )
        {
            column2 = QString("(%0)").arg(targetname.toString());
        }

        if ( classname.isString() )
        {
            column1 = classname.toString();
        }

        QTreeWidgetItem* treeItem = new QTreeWidgetItem();
        treeItem->setData(KeyColumn, Qt::DisplayRole, column1);

        if ( !column2.isEmpty() )
        {
            treeItem->setData(ValueColumn, Qt::DisplayRole, column2);
        }

        processTreeWidgetItem(treeItem, object);
        m_pTreeView->invisibleRootItem()->addChild(treeItem);
    }

    return true;
}

void KeyvaluesLumpViewWidget::processTreeWidgetItem(QTreeWidgetItem *item, const QJsonObject &kvObject)
{
    for ( QJsonObject::const_iterator it = kvObject.constBegin(); it != kvObject.constEnd(); ++it )
    {
        QTreeWidgetItem* child = new QTreeWidgetItem();

        child->setData(KeyColumn, Qt::DisplayRole, it.key());
        child->setData(ValueColumn, Qt::DisplayRole, it.value());
        item->addChild(child);
    }
}
