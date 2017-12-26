#ifndef MAINWINDOWCOMMANDS_H
#define MAINWINDOWCOMMANDS_H

#include <QObject>

class MainWindow;

class MainWindowCommands : public QObject
{
    Q_OBJECT
public:
    explicit MainWindowCommands(MainWindow* inMainWindow);

public slots:
    void menuLoadFile();

signals:
    void newFileLoaded();
    void fileCleared();

private:
    void setLastOpenDir(const QString& fileName);
    void loadFile(const QString& fileName);
    void processLoadedFile(const QString& fileName);

    MainWindow* mainWindow;

    QString lastOpenDir;
};

#endif // MAINWINDOWCOMMANDS_H
