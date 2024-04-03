#include <pc.h>
#include <linked_list.h>


Pc::Pc(int id, QString inputName, int inputBudget): id(id), name(inputName), total_budget(inputBudget)  {

    budget["Case"] = 0;
    budget["CaseFan"] = 0;
    budget["Cpu"] = 0;
    budget["CpuCooler"] = 0;
    budget["InternalStorage"] = 0;
    budget["Memory"] = 0;
    budget["Motherboard"] = 0;
    budget["PowerSupply"] = 0;
    budget["ThermalPaste"] = 0;

    components["Case"];
    components["CaseFan"];
    components["Cpu"];
    components["CpuCooler"];
    components["InternalStorage"];
    components["Memory"];
    components["Motherboard"];
    components["PowerSupply"];
    components["ThermalPaste"];

}

Pc::Pc(){};

Pc::~Pc(){};

void Pc::setName(QString name){
    this->name = name;
}

Pc::Pc(int id, QString& name, int total_budget, int total_tdp, QMap<QString, double>& budget, QMap<QString, QList<QJsonObject>>& components):
    id(id), name(name), total_budget(total_budget), total_tdp(total_tdp), budget(budget), components(components){}

int Pc::getID() const{
    return id;
};

QString Pc::getName() const{
    return name;
};

void Pc::allocateBudget(){};

int Pc::getTotalBudget() const{
    return total_budget;
}

int Pc::getTotalTdp() const{
    return total_tdp;
}

QMap<QString, double> Pc::getBudget() const{
    return budget;
}

double Pc::calculateEffectivePrice() const {
    double sum = 0.0;
    for (auto it = components.begin(); it != components.end(); ++it) {
        for (const QJsonObject& obj : it.value()) {
            if (obj.contains("price_usd") && obj["price_usd"].isDouble()) {
                sum += obj["price_usd"].toDouble();
            }
        }
    }
    return sum;
}

QMap<QString, QList<QJsonObject>> Pc::getComponents() const{
    return components;
}

// This function checks if all components in the build have a price
bool Pc::lastCheck() {
    bool allComponentsHavePrice = true;
    // Loop through all component types in the budget
    for (auto it = this->budget.begin(); it != this->budget.end(); ++it) {
        QString componentName = it.key();
        // Check if the build contains this component type
        if (this->components.contains(componentName)) {
            QList<QJsonObject> componentList = this->components.value(componentName);
            bool componentHasPrice = false;
            // Loop through all components of this type in the build
            for (const QJsonObject &component : componentList) {
                // Check if the component has a price
                if (component["price_usd"].toDouble() != 0) {
                    componentHasPrice = true;
                    break;
                }
            }
            // If no components of this type have a price, set allComponentsHavePrice to false and break out of the loop
            if (!componentHasPrice) {
                allComponentsHavePrice = false;
                qDebug() << "Component" << componentName << "has no price";
                break;
            }
        }
    }
    return allComponentsHavePrice;
}

// This function returns a list of pairs containing the name and type of all components in the build
QList<QPair<QString, QString>> Pc::getNameAndTypeForAllComponents() const{
    QList<QPair<QString, QString>> namesAndTypes;
    // Loop through all component types in the build
    for (const auto& [key, componentList] : components.toStdMap()) {
        // Loop through all components of this type in the build
        for (const QJsonObject& component : componentList) {
            // Check if the component has a name
            if (component.contains("name")) {
                QString name = component.value("name").toString();
                namesAndTypes.append(qMakePair(name, key));
            }
        }
    }
    return namesAndTypes;
}

// This function returns a list of prices for all components in the build
QList<double> Pc::getPriceForAllComponents() const {
    QList<double> prices;
    // Loop through all component types in the build
    for (const auto& [key, componentList] : components.toStdMap()) {
        // Loop through all components of this type in the build
        for (const QJsonObject& component : componentList) {
            // Check if the component has a price
            if (component.contains("price_usd")) {
                double price = component.value("price_usd").toDouble();
                prices.append(price);
            }
        }
    }
    return prices;
}


// This function returns a list of ratings for all components in the build
QList<int> Pc::getRatingForAllComponents() const{
    QList<int> ratings;
    // Loop through all component types in the build
    for (const auto& [key, componentList] : components.toStdMap()) {
        // Loop through all components of this type in the build
        for (const QJsonObject& component : componentList) {
            // Check if the component has a rating
            if (component.contains("rating")) {
                int rating = component.value("rating").toInt();
                ratings.append(rating);
            }
        }
    }
    return ratings;
}

// This function calculates the total TDP for the build
void Pc::calculateTdp(){// This method should only be called once the build is complete.
    int tdp = 0;
    // Add the TDP for the CPU
    tdp += components["Cpu"].at(0)["tdp"].toString().remove("W").toInt();   //CPU Watts
    // Add the TDP for the motherboard
    tdp += 50;   //Motherboard Watts
    // Add the TDP for the RAM
    tdp += 10;   //Ram Watts
    // Add the TDP for each case fan
    tdp += components["CaseFan"].count() * 5; //CaseFan Watts
    // Loop through all internal storage components in the build
    for (auto it = components["InternalStorage"].begin(); it != components["InternalStorage"].end(); it++ ){
        // Check if the internal storage is an RPM drive or an SSD and add the appropriate TDP
        if((*it)["type"].toString().contains("RPM")){
            tdp += 20; //Hard Disk Watts
        }
        else{
            tdp += 10; //SSD Watts
        }
    }

    // Add 30% to account for additional power draw from other components and inefficiencies
    tdp += 0.3 * tdp;

    Pc::total_tdp = tdp;
}

// This function selects a case for the build
const QJsonObject Pc::choseCase() const{     // We choose the case first, it will be important to remember what type of ATX standard it has.

    // Read and clean the case dataset
    QJsonArray myArr = File_Reader::readDataset("case.json");
    myArr = File_Reader::cleanDataset_Case(myArr);   // Removes cases that have a null "type" field.

    // Calculate the maximum price for the case based on the budget
    double maxPrice = total_budget * (budget["Case"]/100);
    double deltaPrice = 0;
    double tempdeltaPrice = 0;
    QJsonObject bestCase;
    QJsonObject obj;

    // Loop through all cases in the dataset
    for(auto it = myArr.begin(); it != myArr.end(); it++){
        obj = (*it).toObject();
        tempdeltaPrice = maxPrice - obj["price_usd"].toDouble();
        // Check if this is the first case that fits within the budget
        if(!deltaPrice && obj["price_usd"].toDouble() <= maxPrice){
            bestCase = obj;
            deltaPrice = tempdeltaPrice;
        }
        // Check if this case has a higher rating and fits within the budget
        else if(deltaPrice && bestCase["rating"].toDouble() <= obj["rating"].toDouble() && obj["price_usd"].toDouble() <= maxPrice && tempdeltaPrice < deltaPrice){

            bestCase = obj;
        }

    }
    return bestCase;
}


// This function selects a CPU for the build
const QJsonObject Pc::choseCpu() const{   // We choose the CPU second.
    // Read the CPU dataset
    QJsonArray myArr = File_Reader::readDataset("cpu.json");
    // Calculate the maximum price for the CPU based on the budget
    double maxPrice = total_budget * (budget["Cpu"]/100);
    double deltaPrice = 0;
    double tempdeltaPrice = 0;
    QJsonObject bestCpu;
    QJsonObject obj;

    // Loop through all CPUs in the dataset
    for(auto it = myArr.begin(); it != myArr.end(); it++){
        obj = (*it).toObject();
        tempdeltaPrice = maxPrice - obj["price_usd"].toDouble();
        // Check if this is the first CPU that fits within the budget and is not a Threadripper
        if(!deltaPrice && obj["price_usd"].toDouble() <= maxPrice && !obj["name"].toString().contains("Threadripper")){
            bestCpu = obj;
            deltaPrice = tempdeltaPrice;
        }
        // Check if this CPU has a higher rating, fits within the budget, and is not a Threadripper
        else if(deltaPrice &&
                 bestCpu["rating"].toDouble() <= obj["rating"].toDouble() &&
                 obj["price_usd"].toDouble() <= maxPrice &&
                 tempdeltaPrice < deltaPrice &&
                 !obj["name"].toString().contains("Threadripper")){

            bestCpu = obj;
        }

    }
    return bestCpu;
}

// This function checks if a given motherboard and case are compatible based on their ATX standard
int Pc::checkStandard_Motherboard_Case(QString s) const{

    // Check the ATX standard of the motherboard or case and return an integer representing its size
    if(s.left(4) == "Mini"){return 0;}
    if(s.left(5) == "Micro"){return 1;}
    if(s.left(3) == "ATX"){return 2;}
    if(s.left(4) == "EATX"){return 3;}
    if(s.left(2) == "XL"){return 4;}

    return -1;
}

// This function checks if a given motherboard and CPU are compatible based on their socket type
QString Pc::checkStandard_Motherboard_Cpu(QString s) const{

    // Check the socket type of the motherboard or CPU and return a string representing its manufacturer
    if(s.left(3) == "AMD" || s.left(3) == "AM4" ){return "AMD";}
    if(s.left(5) == "Intel" || s.left(3) == "LGA"){return "Intel";}

    return "-1";
}



// This function selects a motherboard for the build
const QJsonObject Pc::choseMotherboard() const{  // We choose the motherboard third. We need to make sure that the motherboard is compatible with the CPU and that its ATX standard is compatible with the case.
    // Read the motherboard dataset
    QJsonArray myArr = File_Reader::readDataset("motherboard.json");
    // Calculate the maximum price for the motherboard based on the budget
    double maxPrice = total_budget * (budget["Motherboard"]/100);
    double deltaPrice = 0;
    double tempdeltaPrice = 0;
    QJsonObject bestMotherboard;
    // Get the case that was already selected for the build
    QJsonObject objCase  = (components["Case"].at(0));
    // Get the ATX standard of the case
    QString typeCase = objCase["type"].toString().remove(" ");
    QJsonObject obj;
    QString formatMobo;
    int formatCase = checkStandard_Motherboard_Case(typeCase);
    // Get the CPU that was already selected for the build
    QJsonObject objCpu = (components["Cpu"].at(0));
    // Get the name of the CPU
    QString nameCpuSupp = objCpu["name"].toString().remove(" ");
    // Get the manufacturer of the CPU
    QString nameCpu = checkStandard_Motherboard_Cpu(nameCpuSupp); // Will be "AMD" or "Intel".
    QString socketMobo;

    // Loop through all motherboards in the dataset
    for(auto it = myArr.begin(); it != myArr.end(); it++){
        obj = (*it).toObject();
        tempdeltaPrice = maxPrice - obj["price_usd"].toDouble();
        // Get the ATX standard of the motherboard
        formatMobo = obj["form_factor"].toString().remove(" ");
        // Get the socket type of the motherboard
        socketMobo = obj["socket_/_cpu"].toString().remove(" ");

        // Check if this is the first motherboard that fits within the budget and is compatible with the case and CPU
        if(!deltaPrice && obj["price_usd"].toDouble() <= maxPrice &&
            formatCase >= checkStandard_Motherboard_Case(formatMobo) &&
            nameCpu == checkStandard_Motherboard_Cpu(socketMobo)){
            bestMotherboard = obj;
            deltaPrice = tempdeltaPrice;

        }
        // Check if this motherboard has a higher rating, fits within the budget, and is compatible with the case and CPU
        else if(deltaPrice &&
                 formatCase >= checkStandard_Motherboard_Case(formatMobo) &&
                 nameCpu == checkStandard_Motherboard_Cpu(socketMobo) &&
                 bestMotherboard["rating"].toDouble() <= obj["rating"].toDouble() &&
                 obj["price_usd"].toDouble() <= maxPrice &&
                 tempdeltaPrice < deltaPrice){

            bestMotherboard = obj;
        }

    }
    return bestMotherboard;
}




// This function checks if a given motherboard and memory are compatible based on their DDR standard
QString Pc::checkStandard_Motherboard_Memory(QString s) const{

    // Check the DDR standard of the motherboard or memory and return a string representing its DDR standard
    if(s.left(3) == "AM4" || s.left(7) == "LGA1200" || s.left(4) == "DDR4"){return "DDR4";}
    if(s.left(7) == "LGA1151" || s.left(4) == "DDR3" || s.left(3) == "LGA"){return "DDR3";}

    return "-1";
}

// This function selects memory for the build
const QJsonObject Pc::choseMemory() const{   // We choose the memory fourth. It will be important to remember the socket type.
    // Read and clean the memory dataset
    QJsonArray myArr = File_Reader::readDataset("memory.json");
    myArr = File_Reader::cleanDataset_Memory(myArr);
    // Calculate the maximum price for the memory based on the budget
    double maxPrice = total_budget * (budget["Memory"]/100);
    double deltaPrice = 0;
    double tempdeltaPrice = 0;
    QJsonObject bestRam;
    QJsonObject obj;
    // Get the motherboard that was already selected for the build
    QJsonObject objMobo  = (components["Motherboard"].at(0));
    // Get the socket type of the motherboard
    QString typeMobo = objMobo["socket_/_cpu"].toString().remove(" ");
    // Get the DDR standard of the motherboard
    typeMobo = checkStandard_Motherboard_Memory(typeMobo); // Will be DDR4 or DDR3.
    QString typeRam;

    // Loop through all memory in the dataset
    for(auto it = myArr.begin(); it != myArr.end(); it++){
        obj = (*it).toObject();
        tempdeltaPrice = maxPrice - obj["price_usd"].toDouble();
        // Get the DDR standard of the memory
        typeRam = obj["speed"].toString().remove(" ");

        // Check if this is the first memory that fits within the budget and is compatible with the motherboard
        if(!deltaPrice && obj["price_usd"].toDouble() <= maxPrice &&
            typeMobo == checkStandard_Motherboard_Memory(typeRam)){
            bestRam = obj;
            deltaPrice = tempdeltaPrice;
        }
        // Check if this memory has a higher rating, fits within the budget, and is compatible with the motherboard
        else if(deltaPrice &&
                 typeMobo == checkStandard_Motherboard_Memory(typeRam) &&
                 bestRam["rating"].toDouble() <= obj["rating"].toDouble() &&
                 obj["price_usd"].toDouble() <= maxPrice &&
                 tempdeltaPrice < deltaPrice){

            bestRam = obj;
        }

    }
    return bestRam;
}

// This function selects a CPU cooler for the build
const QJsonObject Pc::choseCpuCooler() const{

    // Read the CPU cooler dataset
    QJsonArray myArr = File_Reader::readDataset("cpu-cooler.json");

    // Calculate the maximum price for the CPU cooler based on the budget
    double maxPrice = total_budget * (budget["CpuCooler"]/100);
    double deltaPrice = 0;
    double tempdeltaPrice = 0;
    QJsonObject bestCpuCooler;
    QJsonObject obj;

    // Loop through all CPU coolers in the dataset
    for(auto it = myArr.begin(); it != myArr.end(); it++){
        obj = (*it).toObject();
        tempdeltaPrice = maxPrice - obj["price_usd"].toDouble();
        // Check if this is the first CPU cooler that fits within the budget
        if(!deltaPrice && obj["price_usd"].toDouble() <= maxPrice){
            bestCpuCooler = obj;
            deltaPrice = tempdeltaPrice;
        }
        // Check if this CPU cooler has a higher rating and fits within the budget
        else if(deltaPrice && bestCpuCooler["rating"].toDouble() <= obj["rating"].toDouble() && obj["price_usd"].toDouble() <= maxPrice && tempdeltaPrice < deltaPrice){

            bestCpuCooler = obj;
        }
    }
    return bestCpuCooler;
}


// This function selects thermal paste for the build
const QJsonObject Pc::choseThermalPaste() const{

    // Read the thermal paste dataset
    QJsonArray myArr = File_Reader::readDataset("thermal-paste.json");

    // Calculate the maximum price for the thermal paste based on the budget
    double maxPrice = total_budget * (budget["ThermalPaste"]/100);
    double deltaPrice = 0;
    double tempdeltaPrice = 0;
    QJsonObject bestThermalPaste;
    QJsonObject obj;

    // Loop through all thermal pastes in the dataset
    for(auto it = myArr.begin(); it != myArr.end(); it++){
        obj = (*it).toObject();
        tempdeltaPrice = maxPrice - obj["price_usd"].toDouble();
        // Check if this is the first thermal paste that fits within the budget
        if(!deltaPrice && obj["price_usd"].toDouble() <= maxPrice){
            bestThermalPaste = obj;
            deltaPrice = tempdeltaPrice;
        }
        // Check if this thermal paste has a higher rating and fits within the budget
        else if(deltaPrice && bestThermalPaste["rating"].toDouble() <= obj["rating"].toDouble() && obj["price_usd"].toDouble() <= maxPrice && tempdeltaPrice < deltaPrice){

            bestThermalPaste = obj;
        }

    }
    return bestThermalPaste;
}

// This function selects a case fan for the build
const QJsonObject Pc::choseCaseFan(int fanNumber) const{

    // Read and clean the case fan dataset
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
        // Check if this is the first case fan that fits within the budget
        if(!deltaPrice && obj["price_usd"].toDouble() <= maxPrice){
            bestCaseFan = obj;
            deltaPrice = tempdeltaPrice;
        }
        // Check if this case fan has a higher rating and fits within the budget
        else if(deltaPrice && bestCaseFan["rating"].toDouble() <= obj["rating"].toDouble() && obj["price_usd"].toDouble() <= maxPrice && tempdeltaPrice < deltaPrice){

            bestCaseFan = obj;
        }

    }
    return bestCaseFan;
}

// This function selects internal storage for the build
const QJsonObject Pc::choseInternalStorage(QString type, double maxPrice) const{

    // Read the internal storage dataset
    QJsonArray myArr = File_Reader::readDataset("internal-storage.json");
    double deltaPrice = 0;
    double tempdeltaPrice = 0;
    QJsonObject bestInternalStorage;
    QJsonObject obj;
    QString typeStorage;

    // Loop through all internal storage in the dataset
    for(auto it = myArr.begin(); it != myArr.end(); it++){
        obj = (*it).toObject();
        // Get the type of internal storage (SSD or RPM)
        typeStorage = obj["type"].toString().remove(" ");
        tempdeltaPrice = maxPrice - obj["price_usd"].toDouble();
        // Check if this is the first internal storage that fits within the budget and matches the desired type (SSD or RPM)
        if(!deltaPrice && obj["price_usd"].toDouble() <= maxPrice &&
            typeStorage.contains(type)){
            bestInternalStorage = obj;
            deltaPrice = tempdeltaPrice;
        }
        // Check if this internal storage has a higher rating, fits within the budget, and matches the desired type (SSD or RPM)
        else if(deltaPrice &&
                 typeStorage.contains(type) &&
                 bestInternalStorage["rating"].toDouble() <= obj["rating"].toDouble() &&
                 obj["price_usd"].toDouble() <= maxPrice &&
                 tempdeltaPrice < deltaPrice){

            bestInternalStorage = obj;
        }

    }
    return bestInternalStorage;
}

int Pc::checkStandard_PowerSupply_Case(QString s) const{

    if(s.left(3) == "SFX"){return 0;}
    else{
        return 2;
    }

}

// This function selects a power supply for the build
const QJsonObject Pc::chosePowerSupply() const{

    // Read the power supply dataset
    QJsonArray myArr = File_Reader::readDataset("power-supply.json");

    // Calculate the maximum price for the power supply based on the budget
    double maxPrice = total_budget * (budget["PowerSupply"]/100);
    double deltaPrice = 0;
    double tempdeltaPrice = 0;
    QJsonObject bestPowerSupply;
    QJsonObject obj;
    // Get the case that was already selected for the build
    QJsonObject objCase  = (components["Case"].at(0));
    // Get the ATX standard of the case
    QString typeCase = objCase["type"].toString().remove(" ");
    int formatCase = checkStandard_Motherboard_Case(typeCase);
    QString typePsu;

    // Loop through all power supplies in the dataset
    for(auto it = myArr.begin(); it != myArr.end(); it++){
        obj = (*it).toObject();
        tempdeltaPrice = maxPrice - obj["price_usd"].toDouble();
        // Get the ATX standard of the power supply
        typePsu = obj["form_factor"].toString().remove(" ");

        // Check if this is the first power supply that fits within the budget, is compatible with the case, and has enough wattage to support the build
        if(!deltaPrice && obj["price_usd"].toDouble() <= maxPrice &&
            formatCase >= checkStandard_PowerSupply_Case(typePsu) &&
            obj["wattage"].toString().remove("W").toInt() >= total_tdp){
            bestPowerSupply = obj;
            deltaPrice = tempdeltaPrice;
        }
        // Check if this power supply has a higher rating, fits within the budget, is compatible with the case, and has enough wattage to support the build
        else if(deltaPrice &&
                 formatCase >= checkStandard_PowerSupply_Case(typePsu) &&
                 obj["wattage"].toString().remove("W").toInt() >= total_tdp &&
                 bestPowerSupply["rating"].toDouble() <= obj["rating"].toDouble() &&
                 obj["price_usd"].toDouble() <= maxPrice && tempdeltaPrice < deltaPrice){

            bestPowerSupply = obj;
        }
    }
    return bestPowerSupply;
}

