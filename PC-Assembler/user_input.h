#ifndef USER_INPUT_H
#define USER_INPUT_H

#include "input_data_basic.h"
#include "input_data_combobox.h"
#include <QWidget>
#include <QPushButton>
#include <QStringList>

class user_input : public QWidget
{
    Q_OBJECT

public:
    // Constructor that takes label texts, combo box label text, combo box items, button text and parent widget as input
    explicit user_input(const QString &label1Text, const QString &label2Text, const QString &comboLabelText, const QStringList &comboItems, const QString &buttonText, QWidget *parent = nullptr);

    // Function that returns the build text
    QString getBuildText() const;

    // Function that returns the name of the data widget
    QString getDataWidgetName() const;

    // Function that returns the price of the data widget
    QString getDataWidgetPrice() const;

    // Pointer to an input_data_widget object representing the name of the data widget
    input_data_widget *dataWidgetName;

    // Pointer to an input_data_widget object representing the price of the data widget
    input_data_widget *dataWidgetPrice;

signals:
    // Signal emitted when a build is created
    void create_build();

private:
    // Pointer to an input_data_combobox object representing a combo box
    input_data_combobox *comboBox;

    // Pointer to a QPushButton object representing a button
    QPushButton *button;
};


#endif // USER_INPUT_H
