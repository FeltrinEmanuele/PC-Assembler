
#ifndef STANDARD_H
#define STANDARD_H
#include "server.h"
#include <QJsonObject>


class Standard : public Server {
public:
    // Constructor that takes an id, name, and budget as input
    // Adds an external hard drive to the components QMap of the Pc class
    // Constraint: minimum of 3 internal storage components
    Standard(int id, QString inputName, int inputBudget);

    // Virtual function that returns a QJsonObject representing an external hard drive
    virtual const QJsonObject choseExternalHardDrive() const;

    // Override the assemble function from the Server class
    void assemble() override;

    // Override the calculateTdp function from the Server class
    void calculateTdp() override;

    Standard(int id, QString& name, int total_budget, int total_tdp, QMap<QString, double>& budget, QMap<QString, QList<QJsonObject>>& components);

    // Override the allocateBudget function from the Server class
    void allocateBudget() override;
};



#endif // STANDARD_H
