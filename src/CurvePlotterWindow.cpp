#include "CurvePlotterWindow.hpp"

CurvePlotterWindow::CurvePlotterWindow() : QMainWindow()
{
    buildWindow();
    buildMenuBar();
    buildStatusBar();
    buildChart();
    makeConnections();
}

/// Build our menubar with all its components
void CurvePlotterWindow::buildMenuBar()
{
    functions      = menuBar()->addMenu("Functions");
    baseFunctions  = functions->addMenu("Base functions");
    customFunction = functions->addAction("Custom function");
    save           = menuBar()->addAction("Save");
    settings       = menuBar()->addAction("Settings");
    about          = menuBar()->addMenu("About");
    aboutCP        = about->addAction("About Curve Plotter");
    aboutQt        = about->addAction("About Qt");
    initBaseFunctions();
}

/// Build the components of our status bar
/// The zoom buttons and the message
void CurvePlotterWindow::buildStatusBar()
{
    statusBar = new QStatusBar(this);
    statusBar->showMessage("No function");
    zoomPlus  = new QPushButton(QIcon{":assets/plus.png"}, "", this);
    zoomMinus = new QPushButton(QIcon{":assets/minus.png"}, "", this);
    zoomPlus->setAutoRepeat(true);
    zoomMinus->setAutoRepeat(true);
    auto widget = new QWidget();
    auto layout = new QGridLayout(widget);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(zoomPlus, 0, 0, 1, 1, Qt::AlignVCenter | Qt::AlignLeft);
    layout->addWidget(zoomMinus, 0, 1, 1, 1, Qt::AlignVCenter | Qt::AlignRight);
    statusBar->addPermanentWidget(widget);
    setStatusBar(statusBar);
}

/// Make the connections for menu actions and for statusbar buttons
void CurvePlotterWindow::makeConnections()
{
    connect(settings, &QAction::triggered, this, &CurvePlotterWindow::onSettings);
    connect(customFunction, &QAction::triggered, this, &CurvePlotterWindow::onCustomFunction);
    connect(save, &QAction::triggered, this, &CurvePlotterWindow::onSave);
    connect(aboutCP, &QAction::triggered, this, &CurvePlotterWindow::onAbout);
    connect(aboutQt, &QAction::triggered, [this] {
        QMessageBox::aboutQt(this);
    });
    connect(zoomPlus, &QPushButton::clicked, [this] {
        chart->zoomIn();
    });
    connect(zoomMinus, &QPushButton::clicked, [this] {
        chart->zoomOut();
    });
}

/// Resize and center the window
/// And build the window components
void CurvePlotterWindow::buildWindow()
{
    setGeometry(QStyle::alignedRect(Qt::LeftToRight,
                                    Qt::AlignCenter, size(),
                                    QGuiApplication::primaryScreen()->availableGeometry()));
    setWindowIcon(QIcon{":assets/icon.png"});
    resize(850, 550);
}

/// Build our chart and chart view
void CurvePlotterWindow::buildChart()
{
    chart     = new QChart();
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chart->setTheme(static_cast<QChart::ChartTheme>(appSettings.value("theme", 2).toInt()));
    chart->setAnimationOptions(
            static_cast<QChart::AnimationOptions>(appSettings.value("animation", 2).toInt()));
    chart->createDefaultAxes();
    chart->setTitle("Curve plotter");
    chart->show();
    setCentralWidget(chartView);
}

/// Init the base functions list for our base function menu
void CurvePlotterWindow::initBaseFunctions()
{
    QMapIterator<BaseFunctions, QString> iterator(BASE_FUNCTIONS_SYMBOLS);
    while (iterator.hasNext())
    {
        iterator.next();
        baseFunctions->addAction(iterator.value(), [this, iterator]() {
            handleBaseFunctions(iterator.key());
        });
    }
}

/// Handle base functions actions trigger
/// Generate the appropriate lambda for plotting
/// \param funcName
void CurvePlotterWindow::handleBaseFunctions(const BaseFunctions &funcName)
{
    std::function<double(double)> func;
    const auto                    funcTitle = BASE_FUNCTIONS_SYMBOLS.value(funcName);
    chart->setTitle(funcTitle);
    statusBar->showMessage(funcTitle);
    switch (funcName)
    {
        case CONSTANT:
            func = [](double x) -> double {
                return x;
            };
            break;
        case QUADRATIC:
            func = [](double x) -> double {
                return x * x;
            };
            break;
        case CUBIC:
            func = [](double x) -> double {
                return x * x * x;
            };
            break;
        case SQUARE_ROOT:
            func = [](double x) -> double {
                return std::sqrt(x);
            };
            break;
        case CUBIC_ROOT:
            func = [](double x) -> double {
                return std::cbrt(x);
            };
            break;
        case INVERSE:
            func = [](double x) -> double {
                if (x == 0)
                {
                    throw std::exception();
                }
                return 1 / x;
            };
            break;
        case EXP:
            func = [](double x) -> double {
                return std::exp(x);
            };
            break;
        case LOG:
            func = [](double x) -> double {
                if (x <= 0)
                {
                    throw std::exception();
                }
                return std::log(x);
            };
            break;
        case COS:
            func = [](double x) -> double {
                return std::cos(x);
            };
            break;
        case SIN:
            func = [](double x) -> double {
                return std::sin(x);
            };
            break;
        case TAN:
            func = [](double x) -> double {
                return std::tan(x);
            };
            break;
        case ACOS:
            func = [](double x) -> double {
                return std::acos(x);
            };
            break;
        case ASIN:
            func = [](double x) -> double {
                return std::asin(x);
            };
            break;
    }
    plotBaseFunction(func);
}

/// Plot a base function
/// We remove series on the chart
/// If the function is not continuous, we create and other graph
/// We get the range of the chart (x and y)
/// And divide by the precision to draw the points
/// \param func
void CurvePlotterWindow::plotBaseFunction(const std::function<double(double)> &func)
{
    const auto usableMin = -1 * min;
    chart->removeAllSeries();
    auto const step = (max - usableMin) * 1. / precision;
    chart->addSeries(new QSplineSeries(this));
    chart->createDefaultAxes();
    chart->axes(Qt::Vertical).last()->setRange(usableMin, max);
    chart->axes(Qt::Horizontal).last()->setRange(usableMin, max);
    auto x = usableMin * 1.0;
    while (x <= max)
    {
        try
        {
            auto const res = func(x);
            qobject_cast<QSplineSeries *>(chart->series().last())->append(x, res);
        }
        catch (const std::exception &error)
        {
            // Just don't draw it
            // We have a blank, so we create a new series
            chart->addSeries(new QSplineSeries(this));
            chart->createDefaultAxes();
            chart->axes(Qt::Vertical).last()->setRange(usableMin, max);
            chart->axes(Qt::Horizontal).last()->setRange(usableMin, max);
        }
        x += step;
    }
}

/// Show the settings box and handle the changes
void CurvePlotterWindow::onSettings()
{
    auto plotterSettings = new CurvePlotterSettings(this, precision, min, max,
                                                    appSettings.value("animation", DEFAULT_ANIMATION).toInt(),
                                                    appSettings.value("theme", DEFAULT_THEME).toInt());
    connect(plotterSettings, &CurvePlotterSettings::precisionChanged, [this](int prec) {
        appSettings.setValue("precision", prec);
        precision = prec;
    });
    connect(plotterSettings, &CurvePlotterSettings::maxRangeChanged, [this](int maxRg) {
        appSettings.setValue("maxRange", maxRg);
        max = maxRg;
    });
    connect(plotterSettings, &CurvePlotterSettings::minRangeChanged, [this](int minRg) {
        appSettings.setValue("minRange", minRg);
        min = minRg;
    });
    connect(plotterSettings, &CurvePlotterSettings::themeChanged, [this](int theme) {
        appSettings.setValue("theme", theme);
        chart->setTheme(static_cast<QChart::ChartTheme>(theme));
    });
    connect(plotterSettings, &CurvePlotterSettings::animationChanged, [this](int animation) {
        appSettings.setValue("animation", animation);
        chart->setAnimationOptions(static_cast<QChart::AnimationOptions>(animation));
    });
    plotterSettings->show();
}

/// Saving the plot as an image
void CurvePlotterWindow::onSave()
{
    auto const screenName{QFileDialog::getSaveFileName(this, "Screenshot", "plot.png")};
    if (!screenName.trimmed().isEmpty())
    {
        if (chartView->grab().save(screenName))
        {
            QMessageBox::information(this, "Save", "Plot saved");
        }
        else
        {
            QMessageBox::warning(this, "Save", "Could not save the plot");
        }
    }
}

/// Show the about dialog for the app
void CurvePlotterWindow::onAbout()
{
    auto aboutDialog = new AboutCurvePlotter(this);
    aboutDialog->show();
}

/// Show the dialog with an input to let the user enter a custom function
void CurvePlotterWindow::onCustomFunction()
{
    auto customFunctionDialog = new CustomFunctionDialog(this);
    connect(customFunctionDialog, &CustomFunctionDialog::functionValidated, this,
            &CurvePlotterWindow::plotCustomFunction);
    customFunctionDialog->show();
}

/// Plot a custom function entered by the user
/// \param expression
/// \param usedValue
void CurvePlotterWindow::plotCustomFunction(const QString &expressionAsStr,
                                            exprtk::expression<double> &expression,
                                            double &usedValue)
{
    statusBar->showMessage(expressionAsStr);
    const auto usableMin = -1 * min;
    chart->removeAllSeries();
    auto const step = (max - usableMin) * 1. / precision;
    chart->addSeries(new QSplineSeries(this));
    chart->createDefaultAxes();
    chart->axes(Qt::Vertical).last()->setRange(usableMin, max);
    chart->axes(Qt::Horizontal).last()->setRange(usableMin, max);
    auto x = usableMin * 1.0;
    while (x <= max)
    {
        try
        {

            usedValue = x;
            auto const res = expression.value();
            qobject_cast<QSplineSeries *>(chart->series().last())->append(x, res);
        }
        catch (const std::exception &error)
        {
            // Just don't draw it
            // We have a blank, so we create a new series
            chart->addSeries(new QSplineSeries(this));
            chart->createDefaultAxes();
            chart->axes(Qt::Vertical).last()->setRange(usableMin, max);
            chart->axes(Qt::Horizontal).last()->setRange(usableMin, max);
        }
        x += step;
    }
}
