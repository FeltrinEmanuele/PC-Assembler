#include <gaming.h>

Gaming::Gaming(int id, QString inputName, int inputBudget): Full_Setup(id, inputName, inputBudget) {}
Gaming::Gaming() {}

Gaming::Gaming(int id, QString& name, int total_budget, int total_tdp, QMap<QString, double>& budget, QMap<QString, QList<QJsonObject>>& components):
    Full_Setup(id, name, total_budget, total_tdp, budget, components){}

void Gaming::allocateBudget(){
    budget["Case"] = 5;
    budget["CaseFan"] = 7;
    budget["Cpu"] = 12;
    budget["CpuCooler"] = 3;
    budget["InternalStorage"] = 5;
    budget["Memory"] = 9;
    budget["Motherboard"] = 6;
    budget["PowerSupply"] = 6;
    budget["ThermalPaste"] = 1;
    budget["Headphones"] = 4;
    budget["Keyboard"] = 3;
    budget["Monitor"] = 10;
    budget["Mouse"] = 4;
    budget["Os"] = 2;
    budget["VideoCard"] = 21;
    budget["WirelessNetworkCard"] = 2;

}

// Method to choose the best case fan based on the budget, rating and number of fans
const QJsonObject Gaming::choseCaseFan(int fanNumber) const{

    // Read the case fan dataset and clean it
    QJsonArray myArr = File_Reader::readDataset("case-fan.json");
    myArr = File_Reader::cleanDataset_CaseFan(myArr);

    // Calculate the maximum price for a single case fan based on the budget and number of fans
    double maxPrice = total_budget * (budget["CaseFan"]/100);
    maxPrice = maxPrice/fanNumber;

    double deltaPrice = 0;
    double tempdeltaPrice = 0;

    // Object to store the best case fan
    QJsonObject bestCaseFan;
    QJsonObject obj;

    // Loop through all objects in the array
    for(auto it = myArr.begin(); it != myArr.end(); it++){
        obj = (*it).toObject();

        // Calculate the difference between the maximum price and the current object's price
        tempdeltaPrice = maxPrice - obj["price_usd"].toDouble();

        // Check if this is the first valid object or if it has a better rating than the current best case fan and has RGB lighting
        if(!deltaPrice && obj["price_usd"].toDouble() <= maxPrice && obj["name"].toString().contains("RGB")){
            bestCaseFan = obj;
            deltaPrice = tempdeltaPrice;
        }
        else if(deltaPrice && bestCaseFan["rating"].toDouble() <= obj["rating"].toDouble() && obj["price_usd"].toDouble() <= maxPrice && tempdeltaPrice < deltaPrice && obj["name"].toString().contains("RGB")){

            // Update the best case fan
            bestCaseFan = obj;
        }

    }

    return bestCaseFan;
}

// Method to assemble a gaming setup
void Gaming::assemble(){

    // Allocate the budget for each component
    allocateBudget();

    // Call methods from the Pc class to choose components
    components["Case"].append(choseCase());
    components["Cpu"].append(choseCpu());
    components["Motherboard"].append(choseMotherboard());
    components["Memory"].append(choseMemory());
    components["CpuCooler"].append(choseCpuCooler());
    components["ThermalPaste"].append(choseThermalPaste());

    // Choose 4 RGB case fans
    QJsonObject suppCaseFan = choseCaseFan(4);
    components["CaseFan"].append(suppCaseFan);
    components["CaseFan"].append(suppCaseFan);
    components["CaseFan"].append(suppCaseFan);
    components["CaseFan"].append(suppCaseFan);

    // Calculate the budget for internal storage and choose an SSD and two RPM drives
    double tempBudgetStorage = (budget["InternalStorage"]/100) * total_budget;
    components["InternalStorage"].append(choseInternalStorage("SSD", tempBudgetStorage * 0.50));

    QJsonObject suppRPM = choseInternalStorage("RPM", tempBudgetStorage * 0.25);
    components["InternalStorage"].append(suppRPM);
    components["InternalStorage"].append(suppRPM);

    // Call methods from the Full_Setup class to choose additional components
    components["Headphones"].append(choseHeadphones());
    components["Keyboard"].append(choseKeyboard());
    components["Monitor"].append(choseMonitor());
    components["Mouse"].append(choseMouse());
    components["Os"].append(choseOs());

    // Choose a video card with at least 6GB of VRAM
    components["VideoCard"].append(choseVideoCard(1,6));

    // Choose a wireless network card
    components["WirelessNetworkCard"].append(choseWirelessNetworkCard());

    // Calculate the total TDP and choose a power supply
    calculateTdp();
    components["PowerSupply"].append(chosePowerSupply());

}

// Method to calculate the total TDP of all components in the gaming setup
void Gaming::calculateTdp() {

    // Call the calculateTdp method of the base class
    Full_Setup::calculateTdp();

    // Add the TDP of all case fans
    total_tdp += components["CaseFan"].count() * 1;
}

