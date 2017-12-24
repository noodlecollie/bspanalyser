#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "commands/mainwindowcommands.h"
#include "model/bspfile.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    static constexpr int DEFAULT_STATUS_MESSAGE_TIMEOUT = 5000;

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    BSPFile* bspFile();

    void showTemporaryStatusMessage(const QString& message, int timeout = DEFAULT_STATUS_MESSAGE_TIMEOUT);

private slots:
    void bspFileLoaded();
    void bspFileCleared();

private:
    Ui::MainWindow *ui;
    MainWindowCommands* m_pCommands;
    BSPFile* m_pBSPFile;
};

#endif // MAINWINDOW_H
