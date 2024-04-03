#ifndef ARTIFICIAL_INTELLIGENCE_H
#define ARTIFICIAL_INTELLIGENCE_H

#include "server.h"
#include <QJsonObject>

class Artificial_Intelligence : public Server{
public:

    Artificial_Intelligence(int id, QString& name, int total_budget, int total_tdp, QMap<QString, double>& budget, QMap<QString, QList<QJsonObject>>& components);
    // Constructor with parameters id, inputName and inputBudget
    Artificial_Intelligence(int id, QString inputName, int inputBudget);
    // Virtual function to choose a video card based on the number of video cards and minimum VRAM
    virtual const QJsonObject choseVideoCard(int numVideoCard, int minVram) const;
    // Override the assemble function from the base class
    void assemble() override;
    // Override the calculateTdp function from the base class
    void calculateTdp() override;
    // Override the allocateBudget function from the Server class
    void allocateBudget() override;
};

#endif // ARTIFICIAL_INTELLIGENCE_H
