#ifndef CURVEPLOTTER_CURVEPLOTTERWINDOW_HPP
#define CURVEPLOTTER_CURVEPLOTTERWINDOW_HPP

#include <QMenu>
#include <cmath>
#include <QChart>
#include <QDebug>
#include <QStyle>
#include <QScreen>
#include <QMenuBar>
#include <stdexcept>
#include <functional>
#include <QChartView>
#include <QStatusBar>
#include <QFileDialog>
#include <QMainWindow>
#include <QApplication>
#include <QSplineSeries>
#include <QGuiApplication>
#include "BaseFunctions.hpp"
#include "AboutCurvePlotter.hpp"
#include "CustomFunctionDialog.hpp"
#include "CurvePlotterSettings.hpp"

#if QT_VERSION < 0x06
    using namespace QtCharts;
#endif

class CurvePlotterWindow : public QMainWindow
{
public:
    CurvePlotterWindow();
private:
    QMenu       *functions;
    QMenu       *baseFunctions;
    QMenu       *about;
    QAction     *customFunction;
    QAction     *save;
    QAction     *settings;
    QAction     *aboutCP;
    QAction     *aboutQt;
    QStatusBar  *statusBar;
    QChart      *chart;
    QChartView  *chartView;
    QSettings   appSettings;
    QPushButton *zoomPlus;
    QPushButton *zoomMinus;

    static constexpr int DEFAULT_PRECISION = 29;
    static constexpr int DEFAULT_MIN       = 0;
    static constexpr int DEFAULT_MAX       = 10;
    static constexpr int DEFAULT_ANIMATION = QChart::SeriesAnimations;
    static constexpr int DEFAULT_THEME     = QChart::ChartThemeDark;
    int                  precision         = appSettings.value("precision", DEFAULT_PRECISION).toInt();
    int                  min               = appSettings.value("minRange", DEFAULT_MIN).toInt();
    int                  max               = appSettings.value("maxRange", DEFAULT_MAX).toInt();
    void buildChart();
    void buildMenuBar();
    void buildStatusBar();
    void buildWindow();
    void initBaseFunctions();
    void makeConnections();

private slots:
    void handleBaseFunctions(const BaseFunctions &funcName);
    void plotBaseFunction(const std::function<double(double)> &func);
    void plotCustomFunction(const QString &expressionAsStr, exprtk::expression<double> &expression,
                            double &usedValue);
    void onSettings();
    void onSave();
    void onAbout();
    void onCustomFunction();
};

#endif //CURVEPLOTTER_CURVEPLOTTERWINDOW_HPP
