#include "mainwindowcommands.h"

#include <QFileDialog>
#include <QApplication>
#include <QFile>
#include <QMessageBox>
#include <QtDebug>
#include <QJsonDocument>

#include "widgets/mainwindow.h"
#include "exceptions/genericexception.h"
#include "configs/bspformatreader.h"

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

    try
    {
        loadFile(fileName);
        processLoadedFile(fileName);
    }
    catch (GenericException& exception)
    {
        QMessageBox messageBox(QMessageBox::Critical, tr("Error"), QString("Error loading '%0'.").arg(fileName));
        messageBox.setDetailedText(exception.message());
        messageBox.exec();
        return;
    }

    emit newFileLoaded();
}

void MainWindowCommands::loadFile(const QString &fileName)
{
    BSPFileModel* fileModel = mainWindow->applicationModel()->bspFileModel();

    if ( fileModel->isValid() )
    {
        fileModel->clear();
        mainWindow->applicationModel()->bspFileStructure()->clear();
        emit fileCleared();
    }

    if ( !fileModel->load(fileName) )
    {
        throw GenericException("Could not load file from disk.");
    }

    const QByteArray& contents = fileModel->contents();

    if ( static_cast<quint32>(contents.length()) < 2 * sizeof(quint32) )
    {
        throw GenericException("File length was too short.");
    }

    const quint32* versionPtr = reinterpret_cast<const quint32*>(contents.constData());
    BSPFormatCollection& formatCollection = mainWindow->applicationModel()->bspFormatCollection();
    QSharedPointer<QByteArray> formatData = formatCollection.format(contents);

    if ( !formatData )
    {
        throw GenericException(QString("BSP version %0 is not supported.").arg(*versionPtr));
    }

    // Don't need to validate, as this data is from a previously valid document.
    QJsonDocument jsonDoc = QJsonDocument::fromBinaryData(*formatData, QJsonDocument::BypassValidation);
    BSPFileStructure& fileStructure = *mainWindow->applicationModel()->bspFileStructure();
    BSPFormatReader reader;
    QString errorString;

    if ( !reader.read(jsonDoc, fileStructure, errorString) )
    {
        throw GenericException(QString("Failed to read format file '%0'. %1").arg(formatCollection.sourceFileName(*versionPtr)).arg(errorString));
    }

    fileModel->setHasSubVersion(fileStructure.hasSubVersion());
}

void MainWindowCommands::processLoadedFile(const QString& fileName)
{
    setLastOpenDir(fileName);
    mainWindow->showTemporaryStatusMessage(tr("Loaded file: '%0'").arg(fileName));
}

void MainWindowCommands::setLastOpenDir(const QString &fileName)
{
    QDir dir(fileName);
    dir.cdUp();
    lastOpenDir = dir.canonicalPath();
}
