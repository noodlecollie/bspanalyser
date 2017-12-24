#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "mainwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_pCommands(new MainWindowCommands(this))
{
    ui->setupUi(this);

    connect(ui->actionOpen, &QAction::triggered, m_pCommands, &MainWindowCommands::menuLoadFile);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setHexDisplayContents(const QByteArray &contents)
{
    ui->mainwidget->hexDisplayWidget()->loadBinaryData(contents);
}
