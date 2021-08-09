#include "AboutCurvePlotter.hpp"

AboutCurvePlotter::AboutCurvePlotter(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("About");
    setFixedSize(400, 150);
    logo = new QLabel("", this);
    logo->setPixmap(QPixmap{":assets/icon.png"});
    logo->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    aboutText = new QLabel("CurvePlotter is a software written in Qt5 with Qt Chart under<br>"
                           "GPL license<br>"
                           "Github: <a href=\"https://github.com/Ola-jed/CurvePlotter\">https://github.com/Ola-jed/CurvePlotter</a>",
                           this);
    aboutText->setTextFormat(Qt::RichText);
    aboutText->setOpenExternalLinks(true);
    ok = new QPushButton("Ok", this);
    auto lay = new QVBoxLayout(this);
    lay->addWidget(logo);
    lay->addWidget(aboutText);
    lay->addWidget(ok);
    connect(ok, &QPushButton::clicked, [this] {
        close();
    });
}
