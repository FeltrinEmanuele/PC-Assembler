
#ifndef PRODUCTIVITY_H
#define PRODUCTIVITY_H
#include <QJsonObject>
#include <full_setup.h>


class Productivity : public Full_Setup{
public:
    // Constructor that takes an id, input name, and input budget as arguments and adds an optical drive and an external hard drive to the components QMap of the Pc class
    Productivity(int id, QString inputName, int inputBudget);

    // Constructor that takes an id, name, total budget, total tdp, budget QMap, and components QMap as arguments
    Productivity(int id, QString& name, int total_budget, int total_tdp, QMap<QString, double>& budget, QMap<QString, QList<QJsonObject>>& components);

    // Chooses an optical drive object from the dataset and returns it as a QJsonObject. Virtual method
    virtual const QJsonObject choseOpticalDrive() const;

    // Chooses an external hard drive object from the dataset and returns it as a QJsonObject. Virtual method
    virtual const QJsonObject choseExternalHardDrive() const;

    // Calculates the total TDP of the setup. Overrides the method from the parent class
    void calculateTdp() override;
};


#endif // PRODUCTIVITY_H
