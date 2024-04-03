
#ifndef BASIC_DATA_WIDGET_H
#define BASIC_DATA_WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>

class input_data_widget : public QWidget
{
    Q_OBJECT

public:

    explicit input_data_widget(const QString &text, QWidget *parent = nullptr);

    // Returns the text entered in the line edit widget
    QString getLineEditText() const;

    QLineEdit *lineEdit;

private:

    QLabel *label;
};


#endif // BASIC_DATA_WIDGET_H
