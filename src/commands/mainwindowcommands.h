#ifndef MAINWINDOWCOMMANDS_H
#define MAINWINDOWCOMMANDS_H

#include <QObject>

class MainWindow;

class MainWindowCommands : public QObject
{
public:
    explicit MainWindowCommands(MainWindow* inMainWindow);

public slots:
    void menuLoadFile();

private:
    void setLastOpenDir(const QString& fileName);

    MainWindow* mainWindow;

    QString lastOpenDir;
};

#endif // MAINWINDOWCOMMANDS_H
