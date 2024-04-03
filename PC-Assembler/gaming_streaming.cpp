#include <gaming_streaming.h>

Gaming_Streaming::Gaming_Streaming(int id, QString& name, int total_budget):
    Full_Setup(id,name,total_budget),
    Gaming(id,name,total_budget),
    Streaming(id,name,total_budget)
{
    budget["FanController"] = 0;
    components["FanController"];
}

Gaming_Streaming::Gaming_Streaming(int id, QString& name, int total_budget, int total_tdp, QMap<QString, double>& budget, QMap<QString, QList<QJsonObject>>& components):

    Full_Setup(id,name,total_budget,total_tdp,budget,
               components),
    Gaming(id,name,total_budget,total_tdp,budget,
             components),
    Streaming(id,name,total_budget,total_tdp,budget,
              components) {
    qDebug() << "Gaming_Streaming constructor called";
}

void Gaming_Streaming::allocateBudget(){
    budget["Case"] = 4;
    budget["CaseFan"] = 3;
    budget["Cpu"] = 13;
    budget["CpuCooler"] = 4;
    budget["InternalStorage"] = 5;
    budget["Memory"] = 8;
    budget["Motherboard"] = 5;
    budget["PowerSupply"] = 5;
    budget["ThermalPaste"] = 1;
    budget["Headphones"] = 5;
    budget["Keyboard"] = 3;
    budget["Monitor"] = 14;
    budget["Mouse"] = 3;
    budget["Os"] = 4;
    budget["VideoCard"] = 16;
    budget["WirelessNetworkCard"] = 2;
    budget["Webcam"] = 3;
    budget["FanController"] = 2;

}


// Method to assemble a gaming and streaming setup
void Gaming_Streaming::assemble(){

    // Allocate the budget for each component
    allocateBudget();

    // Call methods from the Pc class to choose components
    components["Case"].append(choseCase());
    components["Cpu"].append(choseCpu());
    components["Motherboard"].append(choseMotherboard());
    components["Memory"].append(choseMemory());
    components["CpuCooler"].append(choseCpuCooler());
    components["ThermalPaste"].append(choseThermalPaste());

    // Choose 5 RGB case fans
    QJsonObject suppCaseFan = choseCaseFan(5);
    components["CaseFan"].append(suppCaseFan);
    components["CaseFan"].append(suppCaseFan);
    components["CaseFan"].append(suppCaseFan);
    components["CaseFan"].append(suppCaseFan);
    components["CaseFan"].append(suppCaseFan);

    // Calculate the budget for internal storage and choose an RPM drive and two SSDs
    double tempBudgetStorage = (budget["InternalStorage"]/100) * total_budget;
    components["InternalStorage"].append(choseInternalStorage("RPM", tempBudgetStorage * 0.28));

    QJsonObject suppSSD = choseInternalStorage("SSD", tempBudgetStorage * 0.36);
    components["InternalStorage"].append(suppSSD);
    components["InternalStorage"].append(suppSSD);

    // Call methods from the Full_Setup class to choose additional components
    components["Headphones"].append(choseHeadphones());
    components["Keyboard"].append(choseKeyboard());
    components["Monitor"].append(choseMonitor());
    components["Mouse"].append(choseMouse());

    // Choose a Pro version of an operating system
    components["Os"].append(choseOs());

    // Choose a video card with at least 10GB of VRAM
    components["VideoCard"].append(choseVideoCard(1,10));

    // Choose a wireless network card
    components["WirelessNetworkCard"].append(choseWirelessNetworkCard());

    // Call methods from the Streaming class to choose additional components
    components["Webcam"].append(choseWebcam());

    components["FanController"].append(choseFanController());

    calculateTdp();
    components["PowerSupply"].append(chosePowerSupply());

}


// Method to choose the best fan controller based on the budget and rating
const QJsonObject Gaming_Streaming::choseFanController() const{

    // Read the fan controller dataset
    QJsonArray myArr = File_Reader::readDataset("fan-controller.json");

    // Calculate the maximum price for a fan controller based on the budget
    double maxPrice = total_budget * (budget["FanController"]/100);
    double deltaPrice = 0;
    double tempdeltaPrice = 0;

    // Object to store the best fan controller
    QJsonObject bestFanController;
    QJsonObject obj;

    // Loop through all objects in the array
    for(auto it = myArr.begin(); it != myArr.end(); it++){
        obj = (*it).toObject();

        // Calculate the difference between the maximum price and the current object's price
        tempdeltaPrice = maxPrice - obj["price_usd"].toDouble();

        // Check if this is the first valid object or if it has a better rating than the current best fan controller
        if(!deltaPrice && obj["price_usd"].toDouble() <= maxPrice){
            bestFanController = obj;
            deltaPrice = tempdeltaPrice;
        }
        else if(deltaPrice && bestFanController["rating"].toDouble() <= obj["rating"].toDouble() && obj["price_usd"].toDouble() <= maxPrice && tempdeltaPrice < deltaPrice){

            // Update the best fan controller
            bestFanController = obj;
        }

    }

    return bestFanController;
}

// Method to choose the best Pro version of an operating system based on the budget and rating
const QJsonObject Gaming_Streaming::choseOs() const{

    // Read the operating system dataset
    QJsonArray myArr = File_Reader::readDataset("os.json");

    // Calculate the maximum price for an operating system based on the budget
    double maxPrice = total_budget * (budget["Os"]/100);
    double deltaPrice = 0;
    double tempdeltaPrice = 0;

    // Object to store the best operating system
    QJsonObject bestOs;
    QJsonObject obj;

    // Loop through all objects in the array
    for(auto it = myArr.begin(); it != myArr.end(); it++){
        obj = (*it).toObject();

        // Calculate the difference between the maximum price and the current object's price
        tempdeltaPrice = maxPrice - obj["price_usd"].toDouble();

        // Check if this is the first valid object or if it has a better rating than the current best operating system and is a Pro version
        if(!deltaPrice && obj["price_usd"].toDouble() <= maxPrice && obj["name"].toString().contains("Pro")){
            bestOs = obj;
            deltaPrice = tempdeltaPrice;
        }
        else if(deltaPrice && bestOs["rating"].toDouble() <= obj["rating"].toDouble() && obj["price_usd"].toDouble() <= maxPrice && tempdeltaPrice < deltaPrice && obj["name"].toString().contains("Pro")){

            // Update the best operating system
            bestOs = obj;
        }
    }

    return bestOs;
}

// Method to calculate the total TDP of all components in a gaming and streaming setup
void Gaming_Streaming::calculateTdp() {

    // Call the calculateTdp method of the base class
    Gaming::calculateTdp();

    // Add the TDP of all webcams and fan controllers
    total_tdp += components["Webcam"].count() * 5;
    total_tdp += components["FanController"].count() * 2;
}

