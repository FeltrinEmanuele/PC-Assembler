#ifndef PC_H
#define PC_H
#include <QMap>
#include <QList>
#include <file_reader.h>


class Linked_list;

class Pc {

protected:
    int id;
    QString name;
    int total_budget; // Total budget. 1 int corresponds to 1 dollar. For example, the value 600 corresponds to a budget of 600 dollars
    int total_tdp;
    QMap<QString, double> budget; // QMap containing the portion of the budget allocated to each component of the class
    QMap<QString, QList<QJsonObject>> components; // QMap containing a QList of QJsonObject for all components of the class

public:
    // Assembles the setup by choosing the most suitable component for each component in the class based on the budget. Pure virtual method
    virtual void assemble() =0;

    // Returns a QList of QPairs containing the name and type of all components in the setup
    QList<QPair<QString, QString>> getNameAndTypeForAllComponents() const;

    // Returns a QList of doubles containing the price of all components in the setup
    QList<double> getPriceForAllComponents() const;

    // Returns a QList of ints containing the rating of all components in the setup
    QList<int> getRatingForAllComponents() const;

    // Performs a final check on the setup and returns true if it passes and false if it fails
    bool lastCheck();

    // Calculates and returns the effective price of the setup
    double calculateEffectivePrice() const;

    // Constructor that takes an id, input name, and input budget as arguments
    Pc(int id, QString inputName, int inputBudget);

    Pc(int id, QString& name, int total_budget, int total_tdp, QMap<QString, double>& budget, QMap<QString, QList<QJsonObject>>& components);

    Pc();

    // Virtual destructor
    virtual ~Pc();

    // Allocates the default budget to each component. Virtual method
    virtual void allocateBudget();

    // Chooses a case object from the dataset and returns it as a QJsonObject. Virtual method
    virtual const QJsonObject choseCase() const;

    // Chooses a case fan object from the dataset based on the number of case fans specified by the argument and returns it as a QJsonObject. Virtual method
    virtual const QJsonObject choseCaseFan(int n) const;

    // Chooses a CPU object from the dataset and returns it as a QJsonObject. Virtual method
    virtual const QJsonObject choseCpu() const;

    // Chooses a CPU cooler object from the dataset and returns it as a QJsonObject. Virtual method
    virtual const QJsonObject choseCpuCooler() const;

    // Chooses an internal storage object from the dataset based on the type and maximum price specified by the arguments and returns it as a QJsonObject. Virtual method
    virtual const QJsonObject choseInternalStorage(QString type, double maxPrice) const;

    // Chooses a memory object from the dataset and returns it as a QJsonObject. Virtual method
    virtual const QJsonObject choseMemory() const;

    // Chooses a motherboard object from the dataset and returns it as a QJsonObject. Virtual method
    virtual const QJsonObject choseMotherboard() const;
    // Chooses a power supply object from the dataset and returns it as a QJsonObject. Virtual method
    virtual const QJsonObject chosePowerSupply() const;

    // Chooses a thermal paste object from the dataset and returns it as a QJsonObject. Virtual method
    virtual const QJsonObject choseThermalPaste() const;

    // Calculates the total TDP of the setup. Virtual method
    virtual void calculateTdp();

    // Checks if the specified standard is compatible with the case and motherboard and returns 1 if it is and 0 if it is not
    int checkStandard_Motherboard_Case(QString s) const;

    // Checks if the specified standard is compatible with the CPU and motherboard
    QString checkStandard_Motherboard_Cpu(QString s) const;

    // Checks if the specified standard is compatible with the memory and motherboard
    QString checkStandard_Motherboard_Memory(QString s) const;

    // Checks if the specified standard is compatible with the power supply and case
    int checkStandard_PowerSupply_Case(QString s) const;

    // Returns the id of the Pc object
    int getID() const;

    // Returns the name of the Pc object
    QString getName() const;

    // Sets the name of the Pc object
    void setName(QString name);

    // Returns the total budget of the Pc object
    int getTotalBudget() const;

    // Returns the total TDP of the Pc object
    int getTotalTdp() const;

    // Returns a QMap containing the portion of the budget allocated to each component of the class
    QMap<QString, double> getBudget() const;

    // Returns a QMap containing a QList of QJsonObject for all components of the class
    QMap<QString, QList<QJsonObject>> getComponents() const;
};


#endif // PC_H
