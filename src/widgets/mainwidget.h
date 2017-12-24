#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QSplitter>

#include "hexdisplaywidget.h"
#include "bsplumpviewarea.h"

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = nullptr);

    HexDisplayWidget* hexDisplayWidget();
    BSPLumpViewArea* lumpViewArea();

signals:

public slots:

private:
    QSplitter* m_pSplitter;
    HexDisplayWidget* m_pHexDisplayWidget;
    BSPLumpViewArea* m_pLumpViewArea;
};

#endif // MAINWIDGET_H
