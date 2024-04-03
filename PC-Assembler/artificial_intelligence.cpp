#include <artificial_intelligence.h>

Artificial_Intelligence::Artificial_Intelligence(int id, QString inputName, int inputBudget): Server(id, inputName, inputBudget) {
    budget["VideoCard"] = 0;
    components["VideoCard"];
}

Artificial_Intelligence::Artificial_Intelligence(int id, QString& name, int total_budget, int total_tdp, QMap<QString, double>& budget, QMap<QString, QList<QJsonObject>>& components):
    Server(id, name, total_budget, total_tdp, budget, components){}

// Method for allocating the budget for various components
void Artificial_Intelligence::allocateBudget(){
    // Set the values for various keys in the budget QMap. The values represent percentages of the total budget
    budget["Case"] = 3;
    budget["CaseFan"] = 3;
    budget["Cpu"] = 6;
    budget["CpuCooler"] = 3;
    budget["InternalStorage"] = 4;
    budget["Memory"] = 4;
    budget["Motherboard"] = 5;
    budget["PowerSupply"] = 12;
    budget["ThermalPaste"] = 1;
    budget["OpticalDrive"] = 2;
    budget["VideoCard"] = 57;
}

// Method for choosing a video card based on a given number of video cards and a minimum amount of VRAM
const QJsonObject Artificial_Intelligence::choseVideoCard(int numVideoCards, int minVram) const{

    // Read the dataset of video cards from a file and clean it
    QJsonArray myArr = File_Reader::readDataset("video-card.json");
    myArr = File_Reader::cleanDataset_VideoCard(myArr);

    // Calculate the maximum price for a video card based on the total budget and the percentage allocated to video cards
    double maxPrice = total_budget * (budget["VideoCard"]/100);
    maxPrice = maxPrice/numVideoCards;

    // Initialize variables for finding the best video card
    double deltaPrice = 0;
    double tempdeltaPrice = 0;
    QJsonObject bestVideoCard;
    QJsonObject obj;

    // Iterate over the array of video cards
    for(auto it = myArr.begin(); it != myArr.end(); it++){
        obj = (*it).toObject();
        tempdeltaPrice = maxPrice - obj["price_usd"].toDouble();
        if(!deltaPrice && obj["price_usd"].toDouble() <= maxPrice && obj["memory"].toString().remove("GB").toInt() >= minVram){
            bestVideoCard = obj;
            deltaPrice = tempdeltaPrice;
        }
        else if(deltaPrice && obj["memory"].toString().remove("GB").toInt() >= minVram && bestVideoCard["rating"].toDouble() <= obj["rating"].toDouble() && obj["price_usd"].toDouble() <= maxPrice && tempdeltaPrice < deltaPrice){

            bestVideoCard = obj;
        }

    }
    return bestVideoCard;
}


// Method for calculating the total TDP (Thermal Design Power) of the system
void Artificial_Intelligence::calculateTdp() {
    // Call the calculateTdp method of the base class Server
    Server::calculateTdp();
    // Add the TDP of the video cards to the total TDP
    total_tdp += components["VideoCard"].count() * 250;
}

// Method for assembling the system
void Artificial_Intelligence::assemble(){
    // Allocate the budget for various components
    allocateBudget();

    // Choose and add components to the system using methods from the Pc class
    components["Case"].append(choseCase());
    components["Cpu"].append(choseCpu());
    components["Motherboard"].append(choseMotherboard());
    components["Memory"].append(choseMemory());
    components["CpuCooler"].append(choseCpuCooler());

    // Choose and add video cards to the system using the choseVideoCard method
    QJsonObject suppVideoCard = choseVideoCard(2,12);
    components["VideoCard"].append(suppVideoCard);
    components["VideoCard"].append(suppVideoCard);

    // Choose and add more components to the system using methods from the Pc class
    components["ThermalPaste"].append(choseThermalPaste());
    QJsonObject suppCaseFan = choseCaseFan(3);
    components["CaseFan"].append(suppCaseFan);
    components["CaseFan"].append(suppCaseFan);
    components["CaseFan"].append(suppCaseFan);
    double tempBudgetStorage = (budget["InternalStorage"]/100) * total_budget;
    components["InternalStorage"].append(choseInternalStorage("SSD", tempBudgetStorage * 0.60));
    components["InternalStorage"].append(choseInternalStorage("RPM", tempBudgetStorage * 0.40));

    // Choose and add an optical drive to the system using a method from the Server class
    components["OpticalDrive"].append(choseOpticalDrive());

    // Calculate the total TDP of the system and choose and add a power supply to the system using the calculateTdp and chosePowerSupply methods
    calculateTdp();
    components["PowerSupply"].append(chosePowerSupply());

}
