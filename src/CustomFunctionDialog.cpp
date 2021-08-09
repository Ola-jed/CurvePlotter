#include "CustomFunctionDialog.hpp"

CustomFunctionDialog::CustomFunctionDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Custom function");
    setFixedSize(400, 100);
    indicationLabel = new QLabel("Enter your function below (x is the variable name)", this);
    functionEdit    = new QLineEdit(this);
    ok              = new QPushButton("Ok", this);
    connect(ok, &QPushButton::clicked, this, &CustomFunctionDialog::validateFunction);
    auto lay = new QVBoxLayout(this);
    lay->addWidget(indicationLabel);
    lay->addWidget(functionEdit, 2);
    lay->addWidget(ok);
}

/// Validate the function entered by the user
void CustomFunctionDialog::validateFunction()
{
    const auto                   expression_string{functionEdit->text().toStdString()};
    double                       x;
    exprtk::symbol_table<double> symbol_table;
    symbol_table.add_variable("x", x);
    symbol_table.add_constants();
    exprtk::expression<double> expression;
    expression.register_symbol_table(symbol_table);
    exprtk::parser<double> parser;
    if (!parser.compile(expression_string, expression))
    {

    }
    for (x = static_cast<double>(-5); x <= 5; x += static_cast<double>(0.001))
    {
        double y = expression.value();
        printf("%19.15f\t%19.15f\n", x, y);
    }
}
