#include <streaming.h>

Streaming::Streaming(int id, QString inputName, int inputBudget): Full_Setup(id, inputName, inputBudget) {
    budget["Webcam"] = 0;
    components["Webcam"];
}

Streaming::Streaming() {
    budget["Webcam"] = 0;
    components["Webcam"];
}

Streaming::Streaming(int id, QString& name, int total_budget, int total_tdp, QMap<QString, double>& budget, QMap<QString, QList<QJsonObject>>& components):
    Full_Setup(id, name, total_budget, total_tdp, budget, components){}

void Streaming::allocateBudget(){
    budget["Case"] = 4;
    budget["CaseFan"] = 4;
    budget["Cpu"] = 15;
    budget["CpuCooler"] = 4;
    budget["InternalStorage"] = 5;
    budget["Memory"] = 10;
    budget["Motherboard"] = 5;
    budget["PowerSupply"] = 5;
    budget["ThermalPaste"] = 1;
    budget["Headphones"] = 4;
    budget["Keyboard"] = 3;
    budget["Monitor"] = 10;
    budget["Mouse"] = 4;
    budget["Os"] = 2;
    budget["VideoCard"] = 15;
    budget["WirelessNetworkCard"] = 2;
    budget["Webcam"] = 7;

}

// This function assembles the computer by selecting and adding components to it
void Streaming::assemble(){

    // Allocate the budget for each component
    allocateBudget();

    // Select and add components from the PC class
    components["Case"].append(choseCase());
    components["Cpu"].append(choseCpu());
    components["Motherboard"].append(choseMotherboard());
    components["Memory"].append(choseMemory());
    components["CpuCooler"].append(choseCpuCooler());
    components["ThermalPaste"].append(choseThermalPaste());
    QJsonObject suppCaseFan = choseCaseFan(3);
    components["CaseFan"].append(suppCaseFan);
    components["CaseFan"].append(suppCaseFan);
    components["CaseFan"].append(suppCaseFan);
    double tempBudgetStorage = (budget["InternalStorage"]/100) * total_budget;
    components["InternalStorage"].append(choseInternalStorage("SSD", tempBudgetStorage * 0.40));
    components["InternalStorage"].append(choseInternalStorage("RPM", tempBudgetStorage * 0.60));

    // Select and add components from the Full Setup class
    components["Headphones"].append(choseHeadphones());
    components["Keyboard"].append(choseKeyboard());
    components["Monitor"].append(choseMonitor());
    components["Mouse"].append(choseMouse());
    components["Os"].append(choseOs());
    components["VideoCard"].append(choseVideoCard(1,8));
    components["WirelessNetworkCard"].append(choseWirelessNetworkCard());

    // Select and add a webcam from the Streaming class
    components["Webcam"].append(choseWebcam());

    // Calculate the total TDP and select and add a power supply unit (PSU)
    calculateTdp();
    components["PowerSupply"].append(chosePowerSupply());

}

// This function selects the best webcam based on the given budget and focus type constraints
const QJsonObject Streaming::choseWebcam() const{

    // Read the dataset of webcams from a JSON file
    QJsonArray myArr = File_Reader::readDataset("webcam.json");

    // Calculate the maximum price for a webcam based on the total budget and the percentage allocated for a webcam
    double maxPrice = total_budget * (budget["Webcam"]/100);
    double deltaPrice = 0;
    double tempdeltaPrice = 0;
    QJsonObject bestWebcam;
    QJsonObject obj;

    // Iterate over all webcams in the dataset
    for(auto it = myArr.begin(); it != myArr.end(); it++){
        obj = (*it).toObject();
        tempdeltaPrice = maxPrice - obj["price_usd"].toDouble();
        // If this is the first webcam that meets the price and focus type constraints, select it as the best one
        if(!deltaPrice && obj["price_usd"].toDouble() <= maxPrice && obj["focus_type"].toString() != "Manual"){
            bestWebcam = obj;
            deltaPrice = tempdeltaPrice;
        }
        // If this is not the first webcam that meets the price and focus type constraints, check if it has a better rating than the current best one and if its price is closer to the maximum price
        else if(deltaPrice && bestWebcam["rating"].toDouble() <= obj["rating"].toDouble() && obj["price_usd"].toDouble() <= maxPrice && tempdeltaPrice < deltaPrice && obj["focus_type"].toString() != "Manual"){

            bestWebcam = obj;
        }

    }
    // Return the selected webcam
    return bestWebcam;
}

// This function calculates the total thermal design power (TDP) of the computer by adding the TDP of the webcam to the TDP calculated by the Full Setup class
void Streaming::calculateTdp() {
    Full_Setup::calculateTdp();
    total_tdp += components["Webcam"].count() * 5;
}
