
#ifndef STREAMING_H
#define STREAMING_H
#include <full_setup.h>

class Streaming: public virtual Full_Setup{
public:
    // Constructor that takes an id, name, and budget as input
    // Adds a Webcam to the components QMap of the Pc class
    // Constraint: webcam.focus_type must not be 'Manual'
    Streaming(int id, QString inputName, int inputBudget);

    Streaming();

    Streaming(int id, QString& name, int total_budget, int total_tdp, QMap<QString, double>& budget, QMap<QString, QList<QJsonObject>>& components);

    // Virtual function that returns a QJsonObject representing a webcam
    virtual const QJsonObject choseWebcam() const;

    // Override the calculateTdp function from the Full_Setup class
    void calculateTdp() override;

    // Override the assemble function from the Full_Setup class
    void assemble() override;

    // Override the allocateBudget function from the Full_Setup class
    void allocateBudget() override;
};


#endif // STREAMING_H
