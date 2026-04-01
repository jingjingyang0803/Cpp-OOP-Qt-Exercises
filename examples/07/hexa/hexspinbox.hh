#ifndef HEXSPINBOX_HH
#define HEXSPINBOX_HH

#include <QSpinBox>
#include <QRegularExpressionValidator>

class HexSpinBox : public QSpinBox
{
    Q_OBJECT

public:
    HexSpinBox(QWidget *parent = nullptr);
    ~HexSpinBox();

protected:
    // Validate hexadecimal values.
    virtual QValidator::State validate(QString& text, int& pos) const;

    // Transform QString text to the corresponding value.
    // Needed in displaying the value.
    virtual int valueFromText(const QString& text) const;

    // Transform int value to the corresponding QString text.
    // Needed in displaying the value.
    virtual QString textFromValue(int value) const;

private:
    // Validator for accepting hexadecimal values
    QRegularExpressionValidator *validator_;
};
#endif // HEXSPINBOX_HH
