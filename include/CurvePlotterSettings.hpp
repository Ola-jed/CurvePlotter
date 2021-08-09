#ifndef CURVEPLOTTER_CURVEPLOTTERSETTINGS_HPP
#define CURVEPLOTTER_CURVEPLOTTERSETTINGS_HPP

#include <QDialog>
#include <QSlider>
#include <QComboBox>
#include <QSettings>
#include <QPushButton>
#include <QFormLayout>

class CurvePlotterSettings : public QDialog
{
Q_OBJECT

public:
    explicit CurvePlotterSettings(QWidget *parent, int precision, int minRange, int maxRange, int animation,
                                  int theme);

private:
    QSlider     *precisionSlider;
    QSlider     *minRangeSlider;
    QSlider     *maxRangeSlider;
    QComboBox   *animationComboBox;
    QComboBox   *themeComboBox;
    QPushButton *ok;
    QPushButton *cancel;
    void buildComponents();
    void initComponents();
    void makeConnections();

    // Constants for default settings values
    const int precision      = 99;
    const int minRange       = 0;
    const int maxRange       = 0;
    const int animationIndex = 3;
    const int themeIndex     = 2;

signals:
    void precisionChanged(int precision);
    void minRangeChanged(int minRange);
    void maxRangeChanged(int maxRange);
    void themeChanged(int themeCode);
    void animationChanged(int animationCode);
};


#endif //CURVEPLOTTER_CURVEPLOTTERSETTINGS_HPP
