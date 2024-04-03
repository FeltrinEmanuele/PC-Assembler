#include <mixed.h>

Mixed::Mixed(int id, QString inputName, int inputBudget): Full_Setup(id, inputName, inputBudget) {

    components["OpticalDrive"];
    components["ExternalHardDrive"];
    components["Webcam"];

}

Mixed::Mixed(int id, QString& name, int total_budget, int total_tdp, QMap<QString, double>& budget, QMap<QString, QList<QJsonObject>>& components):
    Full_Setup(id, name, total_budget, total_tdp, budget, components){}

// This function assembles a mixed PC build
void Mixed::assemble(){

    // Before calling this function, the "CombineBudget" function must have been called

    // Call the "chose" functions from the Pc class to select components for the build
    components["Case"].append(choseCase());
    components["Cpu"].append(choseCpu());
    components["Motherboard"].append(choseMotherboard());
    components["Memory"].append(choseMemory());
    components["CpuCooler"].append(choseCpuCooler());
    components["ThermalPaste"].append(choseThermalPaste());
    QJsonObject suppCaseFan = choseCaseFan(3); //no
    components["CaseFan"].append(suppCaseFan);
    components["CaseFan"].append(suppCaseFan);
    components["CaseFan"].append(suppCaseFan);
    double tempBudgetStorage = (budget["InternalStorage"]/100) * total_budget;
    QJsonObject suppSSD = choseInternalStorage("SSD", tempBudgetStorage * 0.60);
    components["InternalStorage"].append(suppSSD);
    QJsonObject suppRPM = choseInternalStorage("RPM", tempBudgetStorage * 0.40);
    components["InternalStorage"].append(suppRPM);

    // Call the "chose" functions from the Full Setup class to select additional components for the build
    components["Headphones"].append(choseHeadphones());
    components["Keyboard"].append(choseKeyboard());
    components["Monitor"].append(choseMonitor());
    components["Mouse"].append(choseMouse());
    components["Os"].append(choseOs());
    components["VideoCard"].append(choseVideoCard(1,6));
    components["WirelessNetworkCard"].append(choseWirelessNetworkCard());

    // Call the "chose" functions from the Mixed class to select additional components for the build
    components["OpticalDrive"].append(choseOpticalDrive());
    components["ExternalHardDrive"].append(choseExternalHardDrive());
    components["Webcam"].append(choseWebcam()); //no

    // Calculate the TDP and select a power supply for the build
    calculateTdp();
    components["PowerSupply"].append(chosePowerSupply());

}

// This function selects an optical drive for the build
const QJsonObject Mixed::choseOpticalDrive() const{

    // Read the optical drive dataset
    QJsonArray myArr = File_Reader::readDataset("optical-drive.json");

    // Calculate the maximum price for the optical drive based on the budget
    double maxPrice = total_budget * (budget["OpticalDrive"]/100);
    double deltaPrice = 0;
    double tempdeltaPrice = 0;
    QJsonObject bestOpticalDrive;
    QJsonObject obj;

    // Loop through all optical drives in the dataset
    for(auto it = myArr.begin(); it != myArr.end(); it++){
        obj = (*it).toObject();
        tempdeltaPrice = maxPrice - obj["price_usd"].toDouble();
        // Check if this is the first optical drive that fits within the budget
        if(!deltaPrice && obj["price_usd"].toDouble() <= maxPrice){
            bestOpticalDrive = obj;
            deltaPrice = tempdeltaPrice;
        }
        // Check if this optical drive has a higher rating and fits within the budget
        else if(deltaPrice && bestOpticalDrive["rating"].toDouble() <= obj["rating"].toDouble() && obj["price_usd"].toDouble() <= maxPrice && tempdeltaPrice < deltaPrice){

            bestOpticalDrive = obj;
        }

    }
    return bestOpticalDrive;
}

// This function selects an external hard drive for the build
const QJsonObject Mixed::choseExternalHardDrive() const {

    // Read the external hard drive dataset
    QJsonArray myArr = File_Reader::readDataset("external-hard-drive.json");

    // Calculate the maximum price for the external hard drive based on the budget
    double maxPrice = total_budget * (budget["ExternalHardDrive"]/100);
    double deltaPrice = 0;
    double tempdeltaPrice = 0;
    QJsonObject bestExternalHardDrive;
    QJsonObject obj;

    // Loop through all external hard drives in the dataset
    for(auto it = myArr.begin(); it != myArr.end(); it++){
        obj = (*it).toObject();
        tempdeltaPrice = maxPrice - obj["price_usd"].toDouble();
        // Check if this is the first external hard drive that fits within the budget and has a capacity of at least 200GB
        if(!deltaPrice && obj["price_usd"].toDouble() <= maxPrice && obj["capacity"].toString().remove("GB").toInt() >= 200){
            bestExternalHardDrive = obj;
            deltaPrice = tempdeltaPrice;
        }
        // Check if this external hard drive has a higher rating, fits within the budget, and has a capacity of at least 200GB
        else if(deltaPrice &&
                 obj["capacity"].toString().remove("GB").toInt() >= 200 &&
                 bestExternalHardDrive["rating"].toDouble() <= obj["rating"].toDouble() && obj["price_usd"].toDouble() <= maxPrice && tempdeltaPrice < deltaPrice){

            bestExternalHardDrive = obj;
        }

    }
    return bestExternalHardDrive;

}

// This function selects a webcam for the build
const QJsonObject Mixed::choseWebcam() const {
    // Read the webcam dataset
    QJsonArray myArr = File_Reader::readDataset("webcam.json");

    // Calculate the maximum price for the webcam based on the budget
    double maxPrice = total_budget * (budget["Webcam"] / 100);
    double deltaPrice = 0;
    double tempdeltaPrice = 0;
    QJsonObject bestWebcam;
    QJsonObject obj;

    // Loop through all webcams in the dataset
    for (auto it = myArr.begin(); it != myArr.end(); it++) {
        obj = (*it).toObject();
        tempdeltaPrice = maxPrice - obj["price_usd"].toDouble();

        // Check if this is the first webcam that fits within the budget and has a non-manual focus type
        if (!deltaPrice && obj["price_usd"].toDouble() <= maxPrice && obj["focus_type"].toString() != "Manual") {
            bestWebcam = obj;
            deltaPrice = tempdeltaPrice;
        }
        // Check if this webcam has a higher rating, fits within the budget, and has a non-manual focus type
        else if (deltaPrice && bestWebcam["rating"].toDouble() <= obj["rating"].toDouble() && obj["price_usd"].toDouble() <= maxPrice && tempdeltaPrice < deltaPrice && obj["focus_type"].toString() != "Manual") {
            bestWebcam = obj;
        }
    }

    return bestWebcam;
}


// This function selects a case fan for the build
const QJsonObject Mixed::choseCaseFan(int fanNumber) const{

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
        // Check if this is the first case fan that fits within the budget and has RGB and PWM
        if(!deltaPrice && obj["price_usd"].toDouble() <= maxPrice && (obj["name"].toString().contains("RGB") && obj["pwm"].toBool() == true)){
            bestCaseFan = obj;
            deltaPrice = tempdeltaPrice;
        }
        // Check if this case fan has a higher rating, fits within the budget, and has RGB and PWM
        else if(deltaPrice && bestCaseFan["rating"].toDouble() <= obj["rating"].toDouble() && obj["price_usd"].toDouble() <= maxPrice && tempdeltaPrice < deltaPrice && (obj["name"].toString().contains("RGB") && obj["pwm"].toBool() == true)){

            bestCaseFan = obj;
        }

    }
    return bestCaseFan;
}


// This function combines the budgets of two Full_Setup objects
void Mixed::combineBudget(Full_Setup& pc1, Full_Setup& pc2){

    // The budgets can only be combined for the Gaming, Streaming, Office, and Workstation classes

    // Allocate the budgets for the two Full_Setup objects
    pc1.allocateBudget();
    pc2.allocateBudget();

    // Get the budget maps for the two Full_Setup objects
    QMap<QString, double> mapPc1(pc1.getBudget());
    QMap<QString, double> mapPc2(pc2.getBudget());

    // Combine the budgets for each component type by averaging the values from the two Full_Setup objects
    budget["Case"] = (mapPc1["Case"] + mapPc2["Case"]) / 2;
    budget["CaseFan"] = (mapPc1["CaseFan"] + mapPc2["CaseFan"]) / 2;
    budget["Cpu"] = (mapPc1["Cpu"] + mapPc2["Cpu"]) / 2;
    budget["CpuCooler"] = (mapPc1["CpuCooler"] + mapPc2["CpuCooler"]) / 2;
    budget["InternalStorage"] = (mapPc1["InternalStorage"] + mapPc2["InternalStorage"]) / 2;
    budget["Memory"] = (mapPc1["Memory"] + mapPc2["Memory"]) / 2;
    budget["Motherboard"] = (mapPc1["Motherboard"] + mapPc2["Motherboard"]) / 2;
    budget["PowerSupply"] = (mapPc1["PowerSupply"] + mapPc2["PowerSupply"]) / 2;
    budget["ThermalPaste"] = (mapPc1["ThermalPaste"] + mapPc2["ThermalPaste"]) / 2;
    budget["Headphones"] = (mapPc1["Headphones"] + mapPc2["Headphones"]) / 2;
    budget["Keyboard"] = (mapPc1["Keyboard"] + mapPc2["Keyboard"]) / 2;
    budget["Monitor"] = (mapPc1["Monitor"] + mapPc2["Monitor"]) / 2;
    budget["Mouse"] = (mapPc1["Mouse"] + mapPc2["Mouse"]) / 2;
    budget["Os"] = (mapPc1["Os"] + mapPc2["Os"]) / 2;
    budget["VideoCard"] = (mapPc1["VideoCard"] + mapPc2["VideoCard"]) / 2;
    budget["WirelessNetworkCard"] = (mapPc1["WirelessNetworkCard"] + mapPc2["WirelessNetworkCard"]) / 2;

    if((mapPc1.contains("OpticalDrive")) || (mapPc2.contains("OpticalDrive"))){
        if(!(mapPc1.contains("OpticalDrive"))){mapPc1["OpticalDrive"] = 0;}
        if(!(mapPc2.contains("OpticalDrive"))){mapPc2["OpticalDrive"] = 0;}
        if(mapPc1.contains("OpticalDrive") && mapPc2.contains("OpticalDrive")){
        budget["OpticalDrive"] = (mapPc1["OpticalDrive"] + mapPc2["OpticalDrive"]) / 2;
        }
    }

    if((mapPc1.contains("ExternalHardDrive")) || (mapPc2.contains("ExternalHardDrive"))){
        if(!(mapPc1.contains("ExternalHardDrive"))){
        mapPc1["ExternalHardDrive"] = 0;
        }
        if(!(mapPc2.contains("ExternalHardDrive"))){
        mapPc2["ExternalHardDrive"] = 0;
        }
        if(mapPc1.contains("ExternalHardDrive") && mapPc2.contains("ExternalHardDrive")){
        budget["ExternalHardDrive"] = (mapPc1["ExternalHardDrive"] + mapPc2["ExternalHardDrive"]) / 2;
        }
    }

    if((mapPc1.contains("Webcam")) || (mapPc2.contains("Webcam"))){
        if(!(mapPc1.contains("Webcam"))){
            mapPc1["Webcam"] = 0;
        }
        if(!(mapPc2.contains("Webcam"))){
            mapPc2["Webcam"] = 0;
        }
        if(mapPc1.contains("Webcam") && mapPc2.contains("Webcam")){
            budget["Webcam"] = (mapPc1["Webcam"] + mapPc2["Webcam"]) / 2;
        }
    }

}

void Mixed::calculateTdp() {
    Full_Setup::calculateTdp();
    total_tdp += components["Webcam"].count() * 5;
    total_tdp += components["CaseFan"].count() * 1;
    total_tdp += components["OpticalDrive"].count() * 15;
    total_tdp += components["ExternalHardDrive"].count() * 10;
}
