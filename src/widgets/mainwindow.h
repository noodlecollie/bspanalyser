#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "commands/mainwindowcommands.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setHexDisplayContents(const QByteArray& contents);

private:
    Ui::MainWindow *ui;
    MainWindowCommands* m_pCommands;
};

#endif // MAINWINDOW_H
