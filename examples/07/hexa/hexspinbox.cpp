#include "hexspinbox.hh"
#include <QtGui>

// Base of hexadecimal numbers
const int BASE = 16;

HexSpinBox::HexSpinBox(QWidget *parent)
    : QSpinBox(parent)
{
    setRange(0, 255);
    validator_ = new QRegularExpressionValidator(
                QRegularExpression("[0-9A-Fa-f]{1,8}"), this);
}

HexSpinBox::~HexSpinBox()
{
}

QValidator::State HexSpinBox::validate(QString &text, int &pos) const
{
    return validator_->validate(text, pos);
}

int HexSpinBox::valueFromText(const QString &text) const
{
    bool ok;
    return text.toInt(&ok, BASE);
}

QString HexSpinBox::textFromValue(int value) const
{
    return QString::number(value, BASE).toUpper();
}
