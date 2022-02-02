#include "CurvePlotterSettings.hpp"
#include <QDebug>

CurvePlotterSettings::CurvePlotterSettings(QWidget *parent, int precision, int minRange, int maxRange,
                                           int animation, int theme) : QDialog(parent), precision(precision),
                                                                       minRange(minRange), maxRange(maxRange),
                                                                       animationIndex(animation),
                                                                       themeIndex(theme)
{
    setFixedSize(800, 250);
    setWindowTitle("CP Settings");
    buildComponents();
    initComponents();
    makeConnections();
    auto formLayout = new QFormLayout;
    formLayout->addRow(tr("&Precision (number of subdivisions):"), precisionSlider);
    formLayout->addRow(tr("&Min range:"), minRangeSlider);
    formLayout->addRow(tr("&Max range:"), maxRangeSlider);
    formLayout->addRow(tr("&Animations:"), animationComboBox);
    formLayout->addRow(tr("&Theme:"), themeComboBox);
    formLayout->addWidget(ok);
    formLayout->addWidget(cancel);
    setLayout(formLayout);
}

/// Build all widget components
void CurvePlotterSettings::buildComponents()
{
    precisionSlider   = new QSlider(Qt::Horizontal, this);
    minRangeSlider    = new QSlider(Qt::Horizontal, this);
    maxRangeSlider    = new QSlider(Qt::Horizontal, this);
    animationComboBox = new QComboBox(this);
    themeComboBox     = new QComboBox(this);
    ok                = new QPushButton("Ok", this);
    cancel            = new QPushButton("Cancel", this);
    precisionSlider->setRange(9, 599);
    precisionSlider->setTickInterval(10);
    minRangeSlider->setRange(0, 10000);
    maxRangeSlider->setRange(10, 10000);
    themeComboBox->addItems(
            {"Light", "Blue Cerulean", "Dark", "Sand", "Blue natural", "High Contrast", "Blue Icy", "Qt"});
    animationComboBox->addItems(
            {"No Animation", "Grid axis Animations", "Series Animations", "All Animations"});
}

/// Read the app settings to initialize all the components
void CurvePlotterSettings::initComponents()
{
    precisionSlider->setValue(precision);
    minRangeSlider->setValue(minRange);
    maxRangeSlider->setValue(maxRange);
    themeComboBox->setCurrentIndex(themeIndex);
    animationComboBox->setCurrentIndex(animationIndex);
}

/// Connect all the ui components to their slots to emit signals
/// When ok is clicked, we update the settings
/// When close is clicked we reload the saved settings
void CurvePlotterSettings::makeConnections()
{
    connect(ok, &QPushButton::clicked, [this] {
        emit precisionChanged(precisionSlider->value());
        emit minRangeChanged(minRangeSlider->value());
        emit maxRangeChanged(maxRangeSlider->value());
        emit themeChanged(themeComboBox->currentIndex());
        emit animationChanged(animationComboBox->currentIndex());
        close();
    });
    connect(cancel, &QPushButton::clicked, [this] {
        initComponents();
    });
}
