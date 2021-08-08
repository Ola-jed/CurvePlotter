#include <QApplication>
#include "CurvePlotterWindow.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QCoreApplication::setApplicationName("CurvePlotter");
    QCoreApplication::setOrganizationName("CurvePlotter");
    QCoreApplication::setApplicationVersion("1.0");
    CurvePlotterWindow curvePlotterWindow;
    curvePlotterWindow.show();
    return QApplication::exec();
}
