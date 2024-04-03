
#include "mainwindow.h"
#include <QApplication>


// Main function
int main(int argc, char *argv[])
{
    // Create a QApplication object
    QApplication app(argc, argv);

    // Create a MainWindow object
    MainWindow *window = new MainWindow;

    // Show the main window
    window->show();

    // Run the application
    int result = app.exec();

    // Delete the main window
    delete window;

    // Return the result of the application
    return result;
}

