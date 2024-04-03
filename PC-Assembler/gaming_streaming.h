
#ifndef GAMING_STREAMING_H
#define GAMING_STREAMING_H
#include <gaming.h>
#include <streaming.h>
#include <full_setup.h>

class Gaming_Streaming: public Gaming, public Streaming{
public:
    // Constructor that takes an id, name, and total budget as arguments and adds a FanController object to the components QMap of the Pc class
    Gaming_Streaming(int id, QString& name, int total_budget);

    Gaming_Streaming(int id, QString& name, int total_budget, int total_tdp, QMap<QString, double>& budget, QMap<QString, QList<QJsonObject>>& components);

    // Chooses a fan controller object from the dataset and returns it as a QJsonObject
    virtual const QJsonObject choseFanController() const;

    // Chooses an os object from the dataset and returns it as a QJsonObject. Overrides the method from the parent class
    virtual const QJsonObject choseOs() const override;

    // Calculates the total TDP of the setup. Overrides the method from the parent class
    void calculateTdp() override;

    // Assembles the setup by choosing components from the dataset. Overrides the method from the parent class
    void assemble() override;

    // Allocates the budget for each component. Overrides the method from the parent class
    void allocateBudget() override;
};


#endif // GAMING_STREAMING_H
