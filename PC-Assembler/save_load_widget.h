#ifndef SAVE_LOAD_WIDGET_H
#define SAVE_LOAD_WIDGET_H

#include <QWidget>
#include <QPushButton>

class save_load_widget : public QWidget
{
    Q_OBJECT

public:
    // Constructor that takes save button text, load button text, and an optional parent widget as arguments
    explicit save_load_widget(const QString &saveButtonText, const QString &loadButtonText, QWidget *parent = nullptr);

signals:
    // Signal emitted when the load button is clicked
    void load();

    // Signal emitted when the save button is clicked
    void save();

private:
    // Pointer to a QPushButton object for the save button
    QPushButton *saveButton;

    // Pointer to a QPushButton object for the load button
    QPushButton *loadButton;
};


#endif // SAVE_LOAD_WIDGET_H
