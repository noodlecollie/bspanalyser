#ifndef INFODISPLAYGROUPBOX_H
#define INFODISPLAYGROUPBOX_H

#include <QGroupBox>

class QLabel;

class InfoDisplayGroupBox : public QGroupBox
{
    Q_OBJECT
public:
    explicit InfoDisplayGroupBox(QWidget *parent = nullptr);

signals:

public slots:
    void displayError(const QString& error);
    void clearError();

private:
    QLabel* m_pErrorLabel;
};

#endif // INFODISPLAYGROUPBOX_H
