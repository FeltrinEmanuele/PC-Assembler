#include <office.h>

Office::Office(int id, QString inputName, int inputBudget): Productivity(id, inputName, inputBudget) {}

Office::Office(int id, QString& name, int total_budget, int total_tdp, QMap<QString, double>& budget, QMap<QString, QList<QJsonObject>>& components):
    Productivity(id, name, total_budget, total_tdp, budget, components){}

void Office::allocateBudget(){
    budget["Case"] = 5;
    budget["CaseFan"] = 7;
    budget["Cpu"] = 16;
    budget["CpuCooler"] = 3;
    budget["InternalStorage"] = 10;
    budget["Memory"] = 8;
    budget["Motherboard"] = 8;
    budget["PowerSupply"] = 5;
    budget["ThermalPaste"] = 1;
    budget["Headphones"] = 4;
    budget["Keyboard"] = 3;
    budget["Monitor"] = 7;
    budget["Mouse"] = 2;
    budget["Os"] = 3;
    budget["VideoCard"] = 9;
    budget["WirelessNetworkCard"] = 2;
    budget["OpticalDrive"] = 3;
    budget["ExternalHardDrive"] = 4;

}

// This function assembles an office PC build
void Office::assemble(){

    // Allocate the budget for the build
    allocateBudget();

    // Call the "chose" functions from the Pc class to select components for the build
    components["Case"].append(choseCase());
    components["Cpu"].append(choseCpu());
    components["Motherboard"].append(choseMotherboard());
    components["Memory"].append(choseMemory());
    components["CpuCooler"].append(choseCpuCooler());
    components["ThermalPaste"].append(choseThermalPaste());
    QJsonObject suppCaseFan = choseCaseFan(1); // PWM fan
    components["CaseFan"].append(suppCaseFan);
    double tempBudgetStorage = (budget["InternalStorage"]/100) * total_budget;
    components["InternalStorage"].append(choseInternalStorage("SSD", tempBudgetStorage * 0.25));
    components["InternalStorage"].append(choseInternalStorage("RPM", tempBudgetStorage * 0.75));

    // Call the "chose" functions from the Full Setup class to select additional components for the build
    components["Headphones"].append(choseHeadphones());
    components["Keyboard"].append(choseKeyboard());
    components["Monitor"].append(choseMonitor());
    components["Mouse"].append(choseMouse());
    components["Os"].append(choseOs());
    components["VideoCard"].append(choseVideoCard(1,2));
    components["WirelessNetworkCard"].append(choseWirelessNetworkCard());

    // Call the "chose" functions from the Productivity class to select additional components for the build
    components["OpticalDrive"].append(choseOpticalDrive());
    components["ExternalHardDrive"].append(choseExternalHardDrive());

    // Calculate the TDP and select a power supply for the build
    calculateTdp();
    components["PowerSupply"].append(chosePowerSupply());

}

// This function selects a case fan for the build
const QJsonObject Office::choseCaseFan(int fanNumber) const{

    // Read the case fan dataset and clean it
    QJsonArray myArr = File_Reader::readDataset("case-fan.json");
    myArr = File_Reader::cleanDataset_CaseFan(myArr);

    // Calculate the maximum price for each case fan based on the budget and the number of fans
    double maxPrice = total_budget * (budget["CaseFan"]/100);
    maxPrice = maxPrice/fanNumber;
    double deltaPrice = 0;
    double tempdeltaPrice = 0;
    QJsonObject bestCaseFan;
    QJsonObject obj;

    // Loop through all case fans in the dataset
    for(auto it = myArr.begin(); it != myArr.end(); it++){
        obj = (*it).toObject();
        tempdeltaPrice = maxPrice - obj["price_usd"].toDouble();
        // Check if this is the first case fan that fits within the budget and has PWM
        if(!deltaPrice && obj["price_usd"].toDouble() <= maxPrice && obj["pwm"].toBool() == true){
            bestCaseFan = obj;
            deltaPrice = tempdeltaPrice;
        }
        // Check if this case fan has a higher rating, fits within the budget, and has PWM
        else if(deltaPrice && bestCaseFan["rating"].toDouble() <= obj["rating"].toDouble() && obj["price_usd"].toDouble() <= maxPrice && tempdeltaPrice < deltaPrice && obj["pwm"].toBool() == true){

            bestCaseFan = obj;
        }

    }
    return bestCaseFan;
}


