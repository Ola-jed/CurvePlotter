#ifndef CURVEPLOTTER_BASEFUNCTIONS_HPP
#define CURVEPLOTTER_BASEFUNCTIONS_HPP

#include <QMap>

/// The base functions for our plotter
/// x
/// x²
/// x³
/// √x
/// ∛x
/// 1/x
/// exp(x)
/// log(x)
/// cos(x)
/// sin(x)
/// tan(x)
/// acos(x)
/// asin(x)
enum BaseFunctions
{
    CONSTANT,
    QUADRATIC,
    CUBIC,
    SQUARE_ROOT,
    CUBIC_ROOT,
    INVERSE,
    EXP,
    LOG,
    COS,
    SIN,
    TAN,
    ACOS,
    ASIN
};

/// Mapping between functions names and their symbols
const QMap<BaseFunctions, QString> BASE_FUNCTIONS_SYMBOLS{
        {CONSTANT, "x"},
        {QUADRATIC, "x²"},
        {CUBIC, "x³"},
        {SQUARE_ROOT, "√x"},
        {CUBIC_ROOT, "∛x"},
        {INVERSE, "1/x"},
        {EXP, "exp"},
        {LOG, "log"},
        {COS, "cos"},
        {SIN, "sin"},
        {TAN, "tan"},
        {ACOS, "acos"},
        {ASIN, "asin"}
};

#endif //CURVEPLOTTER_BASEFUNCTIONS_HPP
