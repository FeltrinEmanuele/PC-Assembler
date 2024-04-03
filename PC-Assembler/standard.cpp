#include <standard.h>

Standard::Standard(int id, QString inputName, int inputBudget): Server(id, inputName, inputBudget) {
    budget["ExternalHardDrive"] = 0;
    components["ExternalHardDrive"];
}

Standard::Standard(int id, QString& name, int total_budget, int total_tdp, QMap<QString, double>& budget, QMap<QString, QList<QJsonObject>>& components):
    Server(id, name, total_budget, total_tdp, budget, components){}

void Standard::allocateBudget(){
    budget["Case"] = 10;
    budget["CaseFan"] = 5;
    budget["Cpu"] = 20;
    budget["CpuCooler"] = 6;
    budget["InternalStorage"] = 18;
    budget["Memory"] = 14;
    budget["Motherboard"] = 8;
    budget["PowerSupply"] = 8;
    budget["ThermalPaste"] = 2;
    budget["OpticalDrive"] = 4;
    budget["ExternalHardDrive"] = 5;

}

// This function selects the best external hard drive based on the given budget and capacity constraints
const QJsonObject Standard::choseExternalHardDrive() const{

    // Read the dataset of external hard drives from a JSON file
    QJsonArray myArr = File_Reader::readDataset("external-hard-drive.json");

    // Calculate the maximum price for an external hard drive based on the total budget and the percentage allocated for an external hard drive
    double maxPrice = total_budget * (budget["ExternalHardDrive"]/100);
    double deltaPrice = 0;
    double tempdeltaPrice = 0;
    QJsonObject bestExternalHardDrive;
    QJsonObject obj;

    // Iterate over all external hard drives in the dataset
    for(auto it = myArr.begin(); it != myArr.end(); it++){
        obj = (*it).toObject();
        tempdeltaPrice = maxPrice - obj["price_usd"].toDouble();
        // If this is the first external hard drive that meets the price and capacity constraints, select it as the best one
        if(!deltaPrice && obj["price_usd"].toDouble() <= maxPrice && obj["capacity"].toString().remove("GB").toInt() >= 200){
            bestExternalHardDrive = obj;
            deltaPrice = tempdeltaPrice;
        }
        // If this is not the first external hard drive that meets the price and capacity constraints, check if it has a better rating than the current best one and if its price is closer to the maximum price
        else if(deltaPrice &&
                 obj["capacity"].toString().remove("GB").toInt() >= 200 &&
                 bestExternalHardDrive["rating"].toDouble() <= obj["rating"].toDouble() && obj["price_usd"].toDouble() <= maxPrice && tempdeltaPrice < deltaPrice){

            bestExternalHardDrive = obj;
        }

    }
    // Return the selected external hard drive
    return bestExternalHardDrive;
}


// This function calculates the total thermal design power (TDP) of the computer by adding the TDP of the external hard drive to the TDP calculated by the Server class
void Standard::calculateTdp() {
    Server::calculateTdp();
    total_tdp += components["ExternalHardDrive"].count() * 10;
}

// This function assembles the computer by selecting and adding components to it
void Standard::assemble(){

    // Allocate the budget for each component
    allocateBudget();

    // Select and add components from the PC class
    components["Case"].append(choseCase());
    components["Cpu"].append(choseCpu());
    components["Motherboard"].append(choseMotherboard());
    components["Memory"].append(choseMemory());
    components["CpuCooler"].append(choseCpuCooler());
    components["ThermalPaste"].append(choseThermalPaste());
    QJsonObject suppCaseFan = choseCaseFan(2);
    components["CaseFan"].append(suppCaseFan);
    components["CaseFan"].append(suppCaseFan);
    double tempBudgetStorage = (budget["InternalStorage"]/100) * total_budget;
    components["InternalStorage"].append(choseInternalStorage("SSD", tempBudgetStorage * 0.30));
    QJsonObject suppRPM = choseInternalStorage("RPM", tempBudgetStorage * 0.35);
    components["InternalStorage"].append(suppRPM);
    components["InternalStorage"].append(suppRPM);

    // Select and add components from the Server class
    components["OpticalDrive"].append(choseOpticalDrive());

    // Select and add components from the Standard class
    components["ExternalHardDrive"].append(choseExternalHardDrive());

    // Calculate the total TDP and select and add a power supply unit (PSU)
    calculateTdp();
    components["PowerSupply"].append(chosePowerSupply());

}
