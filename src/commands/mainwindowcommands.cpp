#include "mainwindowcommands.h"

#include <QFileDialog>
#include <QApplication>
#include <QFile>
#include <QMessageBox>
#include <QtDebug>

#include "widgets/mainwindow.h"

MainWindowCommands::MainWindowCommands(MainWindow* inMainWindow)
    : QObject(inMainWindow),
      mainWindow(inMainWindow),
      lastOpenDir(qApp->applicationDirPath())
{

}

void MainWindowCommands::menuLoadFile()
{
    QString fileName = QFileDialog::getOpenFileName(mainWindow, tr("Load BSP File"), lastOpenDir, "BSP files (*.bsp)");
    if ( fileName.isEmpty() )
    {
        return;
    }

    fileName = fileName.trimmed();

    if ( !mainWindow->applicationModel()->bspFileModel()->load(fileName) )
    {
        QMessageBox::critical(mainWindow, tr("Error"), tr("Could not open file '%0'.").arg(fileName));
        return;
    }

    setLastOpenDir(fileName);
    mainWindow->showTemporaryStatusMessage(tr("Loaded file: %0").arg(fileName));
}

void MainWindowCommands::setLastOpenDir(const QString &fileName)
{
    QDir dir(fileName);
    dir.cdUp();
    lastOpenDir = dir.canonicalPath();
}
