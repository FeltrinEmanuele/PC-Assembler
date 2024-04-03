#include "builds_widget.h"
#include <QVBoxLayout>

builds_widget::builds_widget(const QString &buttonText, QWidget *parent) : QWidget(parent)
{
    qDebug() << "Creating builds_widget"; // Add this line

    // Create a new vertical layout for the widget
    QVBoxLayout *layout = new QVBoxLayout(this);
    // Create a new push button with the specified text
    button = new QPushButton(buttonText, this);
    // Create a new list widget
    listWidget = new QListWidget(this);
    // Add the button to the layout
    layout->addWidget(button);

    // Add the new buttons
    button1 = new QPushButton("Cancella Build", this);
    button2 = new QPushButton("Modifica Nome Build", this);
    button3 = new QPushButton("Reset", this);
    layout->addWidget(button1);
    layout->addWidget(button2);
    layout->addWidget(button3);

    // Add the list widget to the layout
    layout->addWidget(listWidget);

    // Connect the signals and slots for the buttons
    connect(button, SIGNAL(clicked()), this, SIGNAL(select_build()));
    connect(button1, SIGNAL(clicked()), this, SIGNAL(delete_build()));
    connect(button2, SIGNAL(clicked()), this, SIGNAL(rename_build()));
    connect(button3, SIGNAL(clicked()), this, SIGNAL(reset_all()));

    qDebug() << "Finished creating builds_widget"; // Add this line


    // In the builds_widget constructor
    if (connect(button1, SIGNAL(clicked()), this, SIGNAL(delete_build()))) {
        qDebug() << "Connected button1 clicked signal to delete_build signal";
    } else {
        qDebug() << "Failed to connect button1 clicked signal to delete_build signal";
    }

    if (connect(button2, SIGNAL(clicked()), this, SIGNAL(rename_build()))) {
        qDebug() << "Connected button2 clicked signal to rename_build signal";
    } else {
        qDebug() << "Failed to connect button2 clicked signal to rename_build signal";
    }

    if (connect(button3, SIGNAL(clicked()), this, SIGNAL(reset_all()))) {
        qDebug() << "Connected button3 clicked signal to reset_all signal";
    } else {
        qDebug() << "Failed to connect button3 clicked signal to reset_all signal";
    }
}

// Method to display a linked list in the list widget
void builds_widget::displayList(const Linked_list& list) {
    qDebug() << "Displaying list";

    // Clear the list widget
    listWidget->clear();

    // Get the first node of the linked list
    Node* node = list.getFirst();

    // Loop through all nodes in the linked list
    while (node != nullptr) {
        // Get the name and ID of the PC associated with the current node
        QString name = list.findNameByPc(node->getPc());
        QString id = QString::number(node->getPc()->getID());

        qDebug() << "Adding item:" << name << "with ID:" << id;

        // Create a new item with the name and ID of the PC and add it to the list widget
        QListWidgetItem *item = new QListWidgetItem(name + " (ID: " + id + ")");
        listWidget->addItem(item);

        // Move on to the next node in the linked list
        node = node->getNext();
    }
}

// Method to get the ID of the selected item in the list widget
int builds_widget::getIdFromListWidget() {

    // Get the currently selected item in the list widget
    QListWidgetItem *item = listWidget->currentItem();

    if (item) {
        // Get the text of the selected item
        QString text = item->text();

        // Find the start and end positions of the ID in the text
        int start = text.indexOf("(ID: ") + 5;
        int end = text.indexOf(")", start);

        // Extract the ID string from the text
        QString idStr = text.mid(start, end - start);

        bool ok;

        // Convert the ID string to an integer
        int id = idStr.toInt(&ok);

        if (ok) {
            return id;
        }
    }

    return -1; // Return -1 if no item is selected or if the ID could not be parsed
}
