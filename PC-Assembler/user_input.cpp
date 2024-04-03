#include "user_input.h"
#include <QVBoxLayout>

// This is the constructor for the user_input class
user_input::user_input(const QString &label1Text, const QString &label2Text, const QString &comboLabelText, const QStringList &comboItems, const QString &buttonText, QWidget *parent) : QWidget(parent)
{
    // Create a vertical layout for this widget
    QVBoxLayout *layout = new QVBoxLayout(this);
    // Create input_data_widget objects for the name and price
    dataWidgetName = new input_data_widget(label1Text, this);
    dataWidgetPrice = new input_data_widget(label2Text, this);
    // Create an input_data_combobox object for the build type
    comboBox = new input_data_combobox(comboLabelText, comboItems, this);
    // Create a button with the given text
    button = new QPushButton(buttonText, this);
    // Add the widgets to the layout
    layout->addWidget(dataWidgetName);
    layout->addWidget(dataWidgetPrice);
    layout->addWidget(comboBox);
    layout->addWidget(button);

    // Connect the clicked signal of the button to the create_build signal of this object
    connect(button, SIGNAL(clicked()), this, SIGNAL(create_build()));
}

// This function returns the text of the selected item in the combobox
QString user_input::getBuildText() const
{
    return comboBox->getComboBoxText();
}

// This function returns the text entered in the name input_data_widget
QString user_input::getDataWidgetName() const
{
    return dataWidgetName->getLineEditText();
}

// This function returns the text entered in the price input_data_widget
QString user_input::getDataWidgetPrice() const
{
    return dataWidgetPrice->getLineEditText();
}

