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

public slots:
    void clear();
    void populate();

private slots:
    void updateSelectAllButtonState();
    void selectAllButtonPressed();
    void handleItemSelectionChanged();
    void performSearch();

private:
    Ui::ValueSearchWidget *ui;

    bool bspFileIsValid() const;
    bool canRunSearch() const;
    int selectedLumpCount() const;
    void populateLumpSelector();
    void clearResultsTable();
    void refreshGeneralControls();
    void refreshSearchButtonEnabledState();
};

#endif // VALUESEARCHWIDGET_H
