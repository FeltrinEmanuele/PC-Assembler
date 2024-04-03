#include "input_data_combobox.h"
#include <QVBoxLayout>

// Constructor for the input_data_combobox class
input_data_combobox::input_data_combobox(const QString &text, const QStringList &items, QWidget *parent) : QWidget(parent)
{
    // Create a vertical layout for the widget
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Create a label with the given text
    label = new QLabel(text, this);

    // Create a combo box and add the given items to it
    comboBox = new QComboBox(this);
    comboBox->addItems(items);

    // Add the label and combo box to the layout
    layout->addWidget(label);
    layout->addWidget(comboBox);
}

// Method to get the current text from the combo box
QString input_data_combobox::getComboBoxText() const
{
    return comboBox->currentText();
}

