#ifndef BSPLUMPVIEWAREA_H
#define BSPLUMPVIEWAREA_H

#include <QWidget>
#include <QListWidget>

namespace Ui {
class BSPLumpViewArea;
}

class BSPLumpViewArea : public QWidget
{
    Q_OBJECT

public:
    explicit BSPLumpViewArea(QWidget *parent = 0);
    ~BSPLumpViewArea();

    QListWidget* lumpListWidget();

private:
    Ui::BSPLumpViewArea *ui;
};

#endif // BSPLUMPVIEWAREA_H
