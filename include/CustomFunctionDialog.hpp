#ifndef CURVEPLOTTER_CUSTOMFUNCTIONDIALOG_HPP
#define CURVEPLOTTER_CUSTOMFUNCTIONDIALOG_HPP

#include <QLabel>
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include "exprtk.hpp"

class CustomFunctionDialog : public QDialog
{
public:
    explicit CustomFunctionDialog(QWidget *parent);

private:
    QLineEdit   *functionEdit;
    QLabel      *indicationLabel;
    QPushButton *ok;

private slots:
    void validateFunction();
};


#endif //CURVEPLOTTER_CUSTOMFUNCTIONDIALOG_HPP
