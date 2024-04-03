
#ifndef SERVER_H
#define SERVER_H
#include "pc.h"
#include <QJsonObject>

class Server : public Pc {
public:
    // Constructor that takes an id, name, and budget as input
    // Adds an optical drive to the components QMap of the Pc class
    Server(int id, QString inputName, int InputBudget);

    // Virtual function that returns a QJsonObject representing an optical drive
    virtual const QJsonObject choseOpticalDrive() const;

    // Override the calculateTdp function from the Pc class
    void calculateTdp() override;

    // Constructor that takes an id, name, total budget, total tdp, budget map and components map as input
    Server(int id, QString& name, int total_budget, int total_tdp, QMap<QString, double>& budget, QMap<QString, QList<QJsonObject>>& components);
};


#endif // SERVER_H
