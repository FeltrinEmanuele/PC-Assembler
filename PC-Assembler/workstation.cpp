#include <workstation.h>

Workstation::Workstation(int id, QString inputName, int inputBudget): Productivity(id, inputName, inputBudget) {}

Workstation::Workstation(int id, QString& name, int total_budget, int total_tdp, QMap<QString, double>& budget, QMap<QString, QList<QJsonObject>>& components):
    Productivity(id, name, total_budget, total_tdp, budget, components){}

void Workstation::allocateBudget(){
    budget["Case"] = 3;
    budget["CaseFan"] = 3;
    budget["Cpu"] = 15;
    budget["CpuCooler"] = 4;
    budget["InternalStorage"] = 7;
    budget["Memory"] = 9;
    budget["Motherboard"] = 7;
    budget["PowerSupply"] = 5;
    budget["ThermalPaste"] = 1;
    budget["Headphones"] = 4;
    budget["Keyboard"] = 2;
    budget["Monitor"] = 4;
    budget["Mouse"] = 2;
    budget["Os"] = 5;
    budget["VideoCard"] = 16;
    budget["WirelessNetworkCard"] = 2;
    budget["OpticalDrive"] = 2;
    budget["ExternalHardDrive"] = 9;

}

// This function assembles the computer by selecting and adding components to it
void Workstation::assemble(){

    // Allocate the budget for each component
    allocateBudget();

    // Select and add components from the PC class
    components["Case"].append(choseCase());
    components["Cpu"].append(choseCpu());
    components["Motherboard"].append(choseMotherboard());
    components["Memory"].append(choseMemory());
    components["CpuCooler"].append(choseCpuCooler());
    components["ThermalPaste"].append(choseThermalPaste());
    QJsonObject suppCaseFan = choseCaseFan(6);
    components["CaseFan"].append(suppCaseFan);
    components["CaseFan"].append(suppCaseFan);
    components["CaseFan"].append(suppCaseFan);
    components["CaseFan"].append(suppCaseFan);
    components["CaseFan"].append(suppCaseFan);
    components["CaseFan"].append(suppCaseFan);
    double tempBudgetStorage = (budget["InternalStorage"]/100) * total_budget;
    QJsonObject suppSSD = choseInternalStorage("SSD", tempBudgetStorage * 0.30);
    components["InternalStorage"].append(suppSSD);
    components["InternalStorage"].append(suppSSD);
    QJsonObject suppRPM = choseInternalStorage("RPM", tempBudgetStorage * 0.20);
    components["InternalStorage"].append(suppRPM);
    components["InternalStorage"].append(suppRPM);

    // Select and add components from the Full Setup class
    components["Headphones"].append(choseHeadphones());
    components["Keyboard"].append(choseKeyboard());
    components["Monitor"].append(choseMonitor());
    components["Mouse"].append(choseMouse());
    components["Os"].append(choseOs());
    components["VideoCard"].append(choseVideoCard(1,12));
    components["WirelessNetworkCard"].append(choseWirelessNetworkCard());

    // Select and add an optical drive and an external hard drive from the Productivity class
    components["OpticalDrive"].append(choseOpticalDrive());
    components["ExternalHardDrive"].append(choseExternalHardDrive());

    // Calculate the total TDP and select and add a power supply unit (PSU)
    calculateTdp();
    components["PowerSupply"].append(chosePowerSupply());

}
