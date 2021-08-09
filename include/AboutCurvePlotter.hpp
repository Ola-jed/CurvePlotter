#ifndef CURVEPLOTTER_ABOUTCURVEPLOTTER_HPP
#define CURVEPLOTTER_ABOUTCURVEPLOTTER_HPP

#include <QLabel>
#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>

class AboutCurvePlotter : public QDialog
{
public:
    explicit AboutCurvePlotter(QWidget *parent);

private:
    QLabel      *logo;
    QLabel      *aboutText;
    QPushButton *ok;
};


#endif //CURVEPLOTTER_ABOUTCURVEPLOTTER_HPP
