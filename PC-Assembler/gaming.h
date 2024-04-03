
#ifndef GAMING_H
#define GAMING_H
#include <full_setup.h>

class Gaming: public virtual Full_Setup{
public:
    // Constructor that takes an id, input name, and input budget as arguments and adds one or more CaseFan objects to the components QMap of the Pc class. The name of the CaseFan object must contain "RGB"
    Gaming(int id, QString inputName, int inputBudget);

    Gaming();

    Gaming(int id, QString& name, int total_budget, int total_tdp, QMap<QString, double>& budget, QMap<QString, QList<QJsonObject>>& components);

    // Chooses a case fan object from the dataset based on the number of case fans specified by the argument and returns it as a QJsonObject. Overrides the method from the parent class
    virtual const QJsonObject choseCaseFan(int n) const override;

    // Calculates the total TDP of the setup. Overrides the method from the parent class
    void calculateTdp() override;

    // Assembles the setup by choosing components from the dataset. Overrides the method from the parent class
    void assemble() override;

    // Allocates the budget for each component. Overrides the method from the parent class
    void allocateBudget() override;
};


#endif // GAMING_H
