#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QSplitter>

#include "hexdisplaywidget.h"

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = nullptr);

    HexDisplayWidget* hexDisplayWidget();

signals:

public slots:

private:
    QSplitter* m_pSplitter;
    HexDisplayWidget* m_pHexDisplayWidget;
};

#endif // MAINWIDGET_H
