#include "save_load_widget.h"
#include <QHBoxLayout>

// This is the constructor for the save_load_widget class
save_load_widget::save_load_widget(const QString &saveButtonText, const QString &loadButtonText, QWidget *parent) : QWidget(parent)
{
    // Create a new horizontal layout for the widget
    QHBoxLayout *layout = new QHBoxLayout(this);
    // Create a new save button with the given text
    saveButton = new QPushButton(saveButtonText, this);
    // Create a new load button with the given text
    loadButton = new QPushButton(loadButtonText, this);
    // Add the save and load buttons to the layout
    layout->addWidget(saveButton);
    layout->addWidget(loadButton);

    // Connect the clicked signal of the save button to the save signal of this widget
    connect(saveButton, SIGNAL(clicked()), this, SIGNAL(save()));
    // Connect the clicked signal of the load button to the load signal of this widget
    connect(loadButton, SIGNAL(clicked()), this, SIGNAL(load()));
}

