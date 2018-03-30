#ifndef NOTIMPLEMENTEDPLACEHOLDERWIDGET_H
#define NOTIMPLEMENTEDPLACEHOLDERWIDGET_H

#include <QWidget>

namespace Ui {
class NotImplementedPlaceholderWidget;
}

class NotImplementedPlaceholderWidget : public QWidget
{
    Q_OBJECT

public:
    explicit NotImplementedPlaceholderWidget(QWidget *parent = 0);
    ~NotImplementedPlaceholderWidget();

private:
    Ui::NotImplementedPlaceholderWidget *ui;
};

#endif // NOTIMPLEMENTEDPLACEHOLDERWIDGET_H
