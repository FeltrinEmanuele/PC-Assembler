
#ifndef WORKSTATION_H
#define WORKSTATION_H
#include <QJsonObject>
#include <productivity.h>


class Workstation : public Productivity{
public:
    // Constraint: total budget must be greater than or equal to 3000
    Workstation(int id, QString inputName, int inputBudget);

    // Constructor that takes an id, name, total budget, total tdp, budget map and components map as input
    Workstation(int id, QString& name, int total_budget, int total_tdp, QMap<QString, double>& budget, QMap<QString, QList<QJsonObject>>& components);

    // Override the assemble function from the Productivity class
    void assemble() override;

    // Override the allocateBudget function from the Productivity class
    void allocateBudget() override;
};



#endif // WORKSTATION_H
