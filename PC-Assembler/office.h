
#ifndef OFFICE_H
#define OFFICE_H
#include <QJsonObject>
#include <productivity.h>

class Office : public Productivity{
public:
    // Constructor that takes an id, input name, and input budget as arguments. The noise level of the case fan must be less than or equal to 25.0 dB
    Office(int id, QString inputName, int inputBudget);

    // Constructor that takes an id, name, total budget, total tdp, budget QMap, and components QMap as arguments
    Office(int id, QString& name, int total_budget, int total_tdp, QMap<QString, double>& budget, QMap<QString, QList<QJsonObject>>& components);

    // Chooses a case fan object from the dataset based on the number of case fans specified by the argument and returns it as a QJsonObject. Overrides the method from the parent class
    virtual const QJsonObject choseCaseFan(int n) const override;

    // Assembles the setup by choosing components from the dataset. Overrides the method from the parent class
    void assemble() override;

    // Allocates the budget for each component. Overrides the method from the parent class
    void allocateBudget() override;
};


#endif // OFFICE_H
