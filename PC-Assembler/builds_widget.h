#ifndef BUILDS_WIDGET_H
#define BUILDS_WIDGET_H

#include "qlistwidget.h"
#include <QWidget>
#include <QPushButton>
#include <QListView>
#include <linked_list.h>
#include <QStringListModel>

class builds_widget : public QWidget
{
    Q_OBJECT

public:

    explicit builds_widget(const QString &buttonText, QWidget *parent = nullptr);
    // Function to display a list using a Linked_list object as parameter
    void displayList(const Linked_list& list);
    // Function to get the ID from the list widget
    int getIdFromListWidget();

signals:
    // Signals for selecting a build, renaming a build and deleting a build respectively
    void select_build();
    void rename_build();
    void delete_build();
    void reset_all();

private:

    QPushButton *button;

    QListWidget *listWidget;

    QPushButton *button1;
    QPushButton *button2;
    QPushButton *button3;
};

#endif // BUILDS_WIDGET_H
