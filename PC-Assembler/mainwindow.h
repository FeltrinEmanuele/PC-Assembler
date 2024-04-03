
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "user_input.h"
#include <QListWidget>
#include "save_load_widget.h"
#include "builds_widget.h"
#include <QFileDialog>
#include <standard.h>
#include <artificial_intelligence.h>
#include <workstation.h>
#include <office.h>
#include <mixed.h>
#include <gaming.h>
#include <streaming.h>
#include <gaming_streaming.h>
#include <file_reader.h>
#include <json_handler.h>
#include <linked_list.h>
#include <QInputDialog>


class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    user_input *inputWidget;
    QListWidget *listWidget;
    save_load_widget *saveLoadWidget;
    builds_widget *buildsWidget;

    Linked_list mainList;

public:
    // Constructor that takes an optional parent widget as an argument
    explicit MainWindow(QWidget *parent = nullptr);

    // Displays the specified Pc object in the GUI
    void displayBuild(Pc* pc) const;

    // Checks if the specified Pc object is a valid build and displays an error message if it is not
    bool checkBuild(Pc *pc, QWidget *parent) const;

public slots:
    // Handles the creation of a new build
    void handle_create_build();

    // Handles the selection of an existing build
    void handle_select_build();

    // Handles saving the current list of builds to a file
    void handle_save();

    // Handles loading a list of builds from a file
    void handle_load();

    // Handles deleting a selected build
    void handle_delete_build();

    // Handles renaming a selected build
    void handle_rename_build();

    // Resets all input fields and clears the current list of builds
    void handle_reset_all();
};


#endif // MAINWINDOW_H
