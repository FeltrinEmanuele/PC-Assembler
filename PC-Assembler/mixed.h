
#ifndef MIXED_H
#define MIXED_H
#include <QJsonObject>
#include <full_setup.h>


class Mixed : public Full_Setup{
public:
    // Constructor that takes an id, input name, and input budget as arguments and adds an optical drive, an external hard drive, and a webcam to the components QMap of the Pc class. The build must meet the constraints of the parent class
    Mixed(int id, QString inputName, int inputBudget);

    // Constructor that takes an id, name, total budget, total tdp, budget QMap, and components QMap as arguments
    Mixed(int id, QString& name, int total_budget, int total_tdp, QMap<QString, double>& budget, QMap<QString, QList<QJsonObject>>& components);

    // Chooses an optical drive object from the dataset and returns it as a QJsonObject
    virtual const QJsonObject choseOpticalDrive() const;

    // Chooses an external hard drive object from the dataset and returns it as a QJsonObject
    virtual const QJsonObject choseExternalHardDrive() const;

    // Chooses a webcam object from the dataset and returns it as a QJsonObject
    virtual const QJsonObject choseWebcam() const;

    // Chooses a case fan object from the dataset based on the number of case fans specified by the argument and returns it as a QJsonObject. Overrides the method from the parent class
    virtual const QJsonObject choseCaseFan(int fanNumber) const override;

    // Combines the budgets of two specified Full_Setup objects
    void combineBudget(Full_Setup& pc1, Full_Setup& pc2);

    // Calculates the total TDP of the setup. Overrides the method from the parent class
    void calculateTdp() override;

    // Assembles the setup by choosing components from the dataset. Overrides the method from the parent class
    void assemble() override;
};



#endif // MIXED_H
