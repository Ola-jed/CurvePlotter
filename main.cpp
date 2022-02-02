#include <QApplication>
#include "CurvePlotterWindow.hpp"

int main(int argc, char *argv[])
{
    #if QT_VERSION < 0x06
        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
        QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    #endif
    QApplication a(argc, argv);
    QCoreApplication::setApplicationName("CurvePlotter");
    QCoreApplication::setOrganizationName("CurvePlotter");
    QCoreApplication::setApplicationVersion("1.0");
    CurvePlotterWindow curvePlotterWindow;
    curvePlotterWindow.show();
    return QApplication::exec();
}
