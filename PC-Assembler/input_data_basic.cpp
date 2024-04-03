
#include "input_data_basic.h"
#include <QVBoxLayout>

// Constructor for the input_data_widget class
input_data_widget::input_data_widget(const QString &text, QWidget *parent) : QWidget(parent)
{
    // Create a vertical layout for the widget
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Create a label with the given text
    label = new QLabel(text, this);

    // Create a line edit
    lineEdit = new QLineEdit(this);

    // Add the label and line edit to the layout
    layout->addWidget(label);
    layout->addWidget(lineEdit);
}

// Method to get the text from the line edit
QString input_data_widget::getLineEditText() const
{
    return lineEdit->text();
}
