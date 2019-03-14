#include "widgets/mainwindow.h"
#include "exceptions/genericexception.h"
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    try
    {
        return a.exec();
    }
    catch (const GenericException& ex)
    {
        QMessageBox::critical(nullptr,
                              "Error",
                              QCoreApplication::translate("main.cpp", "An unhandled error occurred during runtime. %0").arg(ex.message()));
    }
    catch (...)
    {
        QMessageBox::critical(nullptr,
                              "Error",
                              QCoreApplication::translate("main.cpp", "An unhandled error occurred during runtime. That's all the information we have."));
    }

    return -1;
}
