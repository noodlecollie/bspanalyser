#ifndef BSPLUMPVIEWAREA_H
#define BSPLUMPVIEWAREA_H

#include <QWidget>

namespace Ui {
class BSPLumpViewArea;
}

class BSPLumpViewArea : public QWidget
{
    Q_OBJECT

public:
    explicit BSPLumpViewArea(QWidget *parent = 0);
    ~BSPLumpViewArea();

private:
    Ui::BSPLumpViewArea *ui;
};

#endif // BSPLUMPVIEWAREA_H
