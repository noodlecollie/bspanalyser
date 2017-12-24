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

    QFile file(fileName);
    if ( !file.open(QIODevice::ReadOnly) )
    {
        QMessageBox::critical(mainWindow, tr("Error"), tr("Could not open file '%0'.").arg(fileName));
        return;
    }

    QByteArray contents = file.readAll();
    file.close();
    mainWindow->setHexDisplayContents(contents);

    setLastOpenDir(fileName);
}

void MainWindowCommands::setLastOpenDir(const QString &fileName)
{
    QDir dir(fileName);
    dir.cdUp();
    lastOpenDir = dir.canonicalPath();
}
