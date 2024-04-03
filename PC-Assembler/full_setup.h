
#ifndef FULL_SETUP_H
#define FULL_SETUP_H
#include <pc.h>

class Full_Setup : public Pc{
public:
    // Constructor that takes an id, input name, and input budget as arguments and adds headphones, keyboard, monitor, mouse, os, video-card, and wireless-network-card to the components QMap of the Pc class
    Full_Setup(int id, QString inputName, int inputBudget);

    Full_Setup();

    Full_Setup(int id, QString& name, int total_budget, int total_tdp, QMap<QString, double>& budget, QMap<QString, QList<QJsonObject>>& components);

    // Returns the budget QMap
    virtual const QMap<QString, double>& getBudget() const;

    // Chooses a headphones object from the dataset and returns it as a QJsonObject
    virtual const QJsonObject choseHeadphones() const;

    // Chooses a keyboard object from the dataset and returns it as a QJsonObject
    virtual const QJsonObject choseKeyboard() const;

    // Chooses a monitor object from the dataset and returns it as a QJsonObject
    virtual const QJsonObject choseMonitor() const;

    // Chooses a mouse object from the dataset and returns it as a QJsonObject
    virtual const QJsonObject choseMouse() const;

    // Chooses an os object from the dataset and returns it as a QJsonObject
    virtual const QJsonObject choseOs() const;

    // Chooses a video card object from the dataset based on the number of video cards and minimum VRAM specified by the arguments and returns it as a QJsonObject
    virtual const QJsonObject choseVideoCard(int numVideoCard, int minVram) const;

    // Chooses a wireless network card object from the dataset and returns it as a QJsonObject
    virtual const QJsonObject choseWirelessNetworkCard() const;

    // Calculates the total TDP of the setup
    void calculateTdp() override;
};


#endif // FULL_SETUP_H
