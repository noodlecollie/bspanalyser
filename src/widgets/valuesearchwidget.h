#ifndef VALUESEARCHWIDGET_H
#define VALUESEARCHWIDGET_H

#include <QWidget>
#include <QVector>

namespace Ui {
class ValueSearchWidget;
}

class ValueSearchWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ValueSearchWidget(QWidget *parent = 0);
    ~ValueSearchWidget();

    QString searchProperty() const;
    QString searchValue() const;
    QVector<QString> searchLumps() const;

signals:
    void searchExecuted();

public slots:
    void clear();
    void populate();

private slots:
    void updateSelectAllButtonState();
    void selectAllButtonPressed();

private:
    Ui::ValueSearchWidget *ui;

    bool bspFileIsValid() const;
    void populateLumpSelector();
    void clearResultsTable();
    void refreshGeneralControls();
};

#endif // VALUESEARCHWIDGET_H
