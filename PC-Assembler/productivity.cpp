#include <productivity.h>

Productivity::Productivity(int id, QString inputName, int inputBudget): Full_Setup(id, inputName, inputBudget) {
    budget["OpticalDrive"] = 0;
    budget["ExternalHardDrive"] = 0;

    components["OpticalDrive"];
    components["ExternalHardDrive"];
}

Productivity::Productivity(int id, QString& name, int total_budget, int total_tdp, QMap<QString, double>& budget, QMap<QString, QList<QJsonObject>>& components):
    Full_Setup(id, name, total_budget, total_tdp, budget, components){}

// This function selects an optical drive for the build
const QJsonObject Productivity::choseOpticalDrive() const{

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
const QJsonObject Productivity::choseExternalHardDrive() const{

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
        // Check if this is the first external hard drive that fits within the budget and has at least 200GB of capacity
        if(!deltaPrice && obj["price_usd"].toDouble() <= maxPrice && obj["capacity"].toString().remove("GB").toInt() >= 200){
            bestExternalHardDrive = obj;
            deltaPrice = tempdeltaPrice;
        }
        // Check if this external hard drive has a higher rating, fits within the budget, and has at least 200GB of capacity
        else if(deltaPrice &&
                 obj["capacity"].toString().remove("GB").toInt() >= 200 &&
                 bestExternalHardDrive["rating"].toDouble() <= obj["rating"].toDouble() && obj["price_usd"].toDouble() <= maxPrice && tempdeltaPrice < deltaPrice){

            bestExternalHardDrive = obj;
        }

    }
    return bestExternalHardDrive;
}

// This function calculates the total TDP for a productivity build
void Productivity::calculateTdp(){
    // Call calculateTdp from Full_Setup to calculate the TDP for all components except optical drives and external hard drives
    Full_Setup::calculateTdp();
    // Add the TDP for each optical drive in the build
    total_tdp += components["OpticalDrive"].count() * 15;
    // Add the TDP for each external hard drive in the build
    total_tdp += components["ExternalHardDrive"].count() * 10;

};



