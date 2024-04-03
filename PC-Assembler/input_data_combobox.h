
#ifndef INPUT_DATA_COMBOBOX_H
#define INPUT_DATA_COMBOBOX_H

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QStringList>

class input_data_combobox : public QWidget
{
    Q_OBJECT

public:

    explicit input_data_combobox(const QString &text, const QStringList &items, QWidget *parent = nullptr);

    // Returns the text of the currently selected item in the combo box
    QString getComboBoxText() const;

private:

    QLabel *label;

    QComboBox *comboBox;
};


#endif // INPUT_DATA_COMBOBOX_H
