#include <full_setup.h>

Full_Setup::Full_Setup(int id, QString inputName, int inputBudget): Pc(id, inputName, inputBudget) {
    budget["Headphones"] = 0;
    budget["Keyboard"] = 0;
    budget["Monitor"] = 0;
    budget["Mouse"] = 0;
    budget["Os"] = 0;
    budget["VideoCard"] = 0;
    budget["WirelessNetworkCard"] = 0;

    components["Headphones"];
    components["Keyboard"];
    components["Monitor"];
    components["Mouse"];
    components["Os"];
    components["VideoCard"];
    components["WirelessNetworkCard"];
}

Full_Setup::Full_Setup(int id, QString& name, int total_budget, int total_tdp, QMap<QString, double>& budget, QMap<QString, QList<QJsonObject>>& components):
    Pc(id, name, total_budget, total_tdp, budget, components){}

Full_Setup::Full_Setup(){};

// Method to get the budget map
const QMap<QString, double>& Full_Setup::getBudget() const{
    return budget;
}

// Method to choose the best headphones based on the budget and rating
const QJsonObject Full_Setup::choseHeadphones() const{

    // Read the headphones dataset
    QJsonArray myArr = File_Reader::readDataset("headphones.json");

    // Calculate the maximum price for headphones based on the budget
    double maxPrice = total_budget * (budget["Headphones"]/100);
    double deltaPrice = 0;
    double tempdeltaPrice = 0;

    // Object to store the best headphones
    QJsonObject bestHeadphones;
    QJsonObject obj;

    // Loop through all objects in the array
    for(auto it = myArr.begin(); it != myArr.end(); it++){
        obj = (*it).toObject();

        // Calculate the difference between the maximum price and the current object's price
        tempdeltaPrice = maxPrice - obj["price_usd"].toDouble();

        // Check if this is the first valid object or if it has a better rating than the current best headphones
        if(!deltaPrice && obj["price_usd"].toDouble() <= maxPrice){
            bestHeadphones = obj;
            deltaPrice = tempdeltaPrice;
        }
        else if(deltaPrice && bestHeadphones["rating"].toDouble() <= obj["rating"].toDouble() && obj["price_usd"].toDouble() <= maxPrice && tempdeltaPrice < deltaPrice){

            // Update the best headphones
            bestHeadphones = obj;
        }
    }

    return bestHeadphones;
}

// Method to choose the best keyboard based on the budget and rating
const QJsonObject Full_Setup::choseKeyboard() const{

    // Read the keyboard dataset
    QJsonArray myArr = File_Reader::readDataset("keyboard.json");

    // Calculate the maximum price for a keyboard based on the budget
    double maxPrice = total_budget * (budget["Keyboard"]/100);
    double deltaPrice = 0;
    double tempdeltaPrice = 0;

    // Object to store the best keyboard
    QJsonObject bestKeyboard;
    QJsonObject obj;

    // Loop through all objects in the array
    for(auto it = myArr.begin(); it != myArr.end(); it++){
        obj = (*it).toObject();

        // Calculate the difference between the maximum price and the current object's price
        tempdeltaPrice = maxPrice - obj["price_usd"].toDouble();

        // Check if this is the first valid object or if it has a better rating than the current best keyboard
        if(!deltaPrice && obj["price_usd"].toDouble() <= maxPrice){
            bestKeyboard = obj;
            deltaPrice = tempdeltaPrice;
        }
        else if(deltaPrice && bestKeyboard["rating"].toDouble() <= obj["rating"].toDouble() && obj["price_usd"].toDouble() <= maxPrice && tempdeltaPrice < deltaPrice){

            // Update the best keyboard
            bestKeyboard = obj;
        }
    }

    return bestKeyboard;
}

// Method to choose the best monitor based on the budget and rating
const QJsonObject Full_Setup::choseMonitor() const{

    // Read the monitor dataset
    QJsonArray myArr = File_Reader::readDataset("monitor.json");

    // Calculate the maximum price for a monitor based on the budget
    double maxPrice = total_budget * (budget["Monitor"]/100);
    double deltaPrice = 0;
    double tempdeltaPrice = 0;

    // Object to store the best monitor
    QJsonObject bestMonitor;
    QJsonObject obj;

    // Loop through all objects in the array
    for(auto it = myArr.begin(); it != myArr.end(); it++){
        obj = (*it).toObject();

        // Calculate the difference between the maximum price and the current object's price
        tempdeltaPrice = maxPrice - obj["price_usd"].toDouble();

        // Check if this is the first valid object or if it has a better rating than the current best monitor
        if(!deltaPrice && obj["price_usd"].toDouble() <= maxPrice){
            bestMonitor = obj;
            deltaPrice = tempdeltaPrice;
        }
        else if(deltaPrice && bestMonitor["rating"].toDouble() <= obj["rating"].toDouble() && obj["price_usd"].toDouble() <= maxPrice && tempdeltaPrice < deltaPrice){

            // Update the best monitor
            bestMonitor = obj;
        }
    }

    return bestMonitor;
}

// Method to choose the best mouse based on the budget and rating
const QJsonObject Full_Setup::choseMouse() const{

    // Read the mouse dataset
    QJsonArray myArr = File_Reader::readDataset("mouse.json");

    // Calculate the maximum price for a mouse based on the budget
    double maxPrice = total_budget * (budget["Mouse"]/100);
    double deltaPrice = 0;
    double tempdeltaPrice = 0;

    // Object to store the best mouse
    QJsonObject bestMouse;
    QJsonObject obj;

    // Loop through all objects in the array
    for(auto it = myArr.begin(); it != myArr.end(); it++){
        obj = (*it).toObject();

        // Calculate the difference between the maximum price and the current object's price
        tempdeltaPrice = maxPrice - obj["price_usd"].toDouble();

        // Check if this is the first valid object or if it has a better rating than the current best mouse
        if(!deltaPrice && obj["price_usd"].toDouble() <= maxPrice){
            bestMouse = obj;
            deltaPrice = tempdeltaPrice;
        }
        else if(deltaPrice && bestMouse["rating"].toDouble() <= obj["rating"].toDouble() && obj["price_usd"].toDouble() <= maxPrice && tempdeltaPrice < deltaPrice){

            // Update the best mouse
            bestMouse = obj;
        }
    }

    return bestMouse;
}

// Method to choose the best operating system based on the budget and rating
const QJsonObject Full_Setup::choseOs() const{

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

        // Check if this is the first valid object or if it has a better rating than the current best operating system
        if(!deltaPrice && obj["price_usd"].toDouble() <= maxPrice){
            bestOs = obj;
            deltaPrice = tempdeltaPrice;
        }
        else if(deltaPrice && bestOs["rating"].toDouble() <= obj["rating"].toDouble() && obj["price_usd"].toDouble() <= maxPrice && tempdeltaPrice < deltaPrice){

            // Update the best operating system
            bestOs = obj;
        }
    }

    return bestOs;
}

// Method to choose the best video card based on the budget, rating, number of video cards and minimum VRAM requirement
const QJsonObject Full_Setup::choseVideoCard(int numVideoCards, int minVram) const{

    // Read the video card dataset and clean it
    QJsonArray myArr = File_Reader::readDataset("video-card.json");
    myArr = File_Reader::cleanDataset_VideoCard(myArr);

    // Calculate the maximum price for a single video card based on the budget and number of video cards
    double maxPrice = total_budget * (budget["VideoCard"]/100);
    maxPrice = maxPrice/numVideoCards;

    double deltaPrice = 0;
    double tempdeltaPrice = 0;

    // Object to store the best video card
    QJsonObject bestVideoCard;
    QJsonObject obj;

    // Loop through all objects in the array
    for(auto it = myArr.begin(); it != myArr.end(); it++){
        obj = (*it).toObject();

        // Calculate the difference between the maximum price and the current object's price
        tempdeltaPrice = maxPrice - obj["price_usd"].toDouble();

        // Check if this is the first valid object or if it has a better rating than the current best video card and meets the minimum VRAM requirement
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

// Method to choose the best wireless network card based on the budget and rating
const QJsonObject Full_Setup::choseWirelessNetworkCard() const{

    // Read the wireless network card dataset
    QJsonArray myArr = File_Reader::readDataset("wireless-network-card.json");

    // Calculate the maximum price for a wireless network card based on the budget
    double maxPrice = total_budget * (budget["WirelessNetworkCard"]/100);
    double deltaPrice = 0;
    double tempdeltaPrice = 0;

    // Object to store the best wireless network card
    QJsonObject bestWirelessNetworkCard;
    QJsonObject obj;

    // Loop through all objects in the array
    for(auto it = myArr.begin(); it != myArr.end(); it++){
        obj = (*it).toObject();

        // Calculate the difference between the maximum price and the current object's price
        tempdeltaPrice = maxPrice - obj["price_usd"].toDouble();

        // Check if this is the first valid object or if it has a better rating than the current best wireless network card
        if(!deltaPrice && obj["price_usd"].toDouble() <= maxPrice){
            bestWirelessNetworkCard = obj;
            deltaPrice = tempdeltaPrice;
        }
        else if(deltaPrice && bestWirelessNetworkCard["rating"].toDouble() <= obj["rating"].toDouble() && obj["price_usd"].toDouble() <= maxPrice && tempdeltaPrice < deltaPrice){

            // Update the best wireless network card
            bestWirelessNetworkCard = obj;
        }
    }

    return bestWirelessNetworkCard;
}

// Method to calculate the total TDP of all components in the setup
void Full_Setup::calculateTdp() {

    // Call the calculateTdp method of the base class
    Pc::calculateTdp();

    // Add the TDP of all headphones
    total_tdp += components["Headphones"].count() * 5;

    // Add the TDP of all keyboards
    total_tdp += components["Keyboard"].count() * 2;

    // Add the TDP of all mice
    total_tdp += components["Mouse"].count() * 2;

    // Add the TDP of all video cards
    total_tdp += components["VideoCard"].count() * 250;

    // Add the TDP of all wireless network cards
    total_tdp += components["WirelessNetworkCard"].count() * 5;
}




