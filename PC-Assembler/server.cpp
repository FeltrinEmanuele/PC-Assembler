#include <server.h>

Server::Server(int id, QString inputName, int inputBudget): Pc(id, inputName, inputBudget) {
    budget["OpticalDrive"] = 0;
    components["OpticalDrive"];
}

Server::Server(int id, QString& name, int total_budget, int total_tdp, QMap<QString, double>& budget, QMap<QString, QList<QJsonObject>>& components):
    Pc(id, name, total_budget, total_tdp, budget, components){}


// This function selects an optical drive for a server build
const QJsonObject Server::choseOpticalDrive() const{

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

// This function calculates the total TDP for a server build
void Server::calculateTdp(){
    // Call calculateTdp from Pc to calculate the TDP for all components except optical drives
    Pc::calculateTdp();
    // Add the TDP for each optical drive in the build
    total_tdp += components["OpticalDrive"].count() * 15;

};
