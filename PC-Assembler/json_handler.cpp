#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include "json_handler.h"
#include "standard.h"
#include "artificial_intelligence.h"
#include "gaming_streaming.h"
#include "mixed.h"
#include "office.h"
#include "workstation.h"

// Method to save a linked list of PCs to a JSON file
void JsonHandler::saveListToJson(const Linked_list& list, const QString& fileName) const {

    // Create a JSON array to store all PCs
    QJsonArray jsonArray;

    // Get the first node in the linked list
    Node* node = list.getFirst();

    // Loop through all nodes in the linked list
    while (node != nullptr) {

        // Create a JSON object to store the current PC
        QJsonObject jsonObject;
        Pc* pc = node->getPc();

        // Save basic information about the PC
        jsonObject["id"] = pc->getID();
        jsonObject["name"] = pc->getName();
        jsonObject["total_budget"] = pc->getTotalBudget();
        jsonObject["total_tdp"] = pc->getTotalTdp();

        // Save the budget QMap
        QJsonObject budgetObject;
        auto budget = pc->getBudget();
        for (auto it = budget.begin(); it != budget.end(); ++it) {
            budgetObject[it.key()] = it.value();
        }
        jsonObject["budget"] = budgetObject;

        // Save the components QMap
        QJsonObject componentsObject;
        auto components = pc->getComponents();
        for (auto it = components.begin(); it != components.end(); ++it) {
            QJsonArray componentArray;
            for (const auto& component : it.value()) {
                componentArray.append(component);
            }
            componentsObject[it.key()] = componentArray;
        }
        jsonObject["components"] = componentsObject;

        // Save type information by checking the dynamic type of the PC object
        QString type;
        if (dynamic_cast<Server*>(pc) != nullptr) {

            if (dynamic_cast<Standard*>(pc) != nullptr) {
                type = "Standard";
            }
            else if (dynamic_cast<Artificial_Intelligence*>(pc) != nullptr) {
                type = "Artificial_Intelligence";
            }
        }
        else if (dynamic_cast<Full_Setup*>(pc) != nullptr) {

            if (dynamic_cast<Productivity*>(pc) != nullptr) {

                if(dynamic_cast<Workstation*>(pc) != nullptr) {
                    type = "Workstation";
                }
                else if (dynamic_cast<Office*>(pc) != nullptr) {
                    type = "Office";
                }
            }
            else if (dynamic_cast<Mixed*>(pc) != nullptr) {
                type = "Mixed";
            }
            else if (dynamic_cast<Gaming_Streaming*>(pc) != nullptr) {
                type = "Gaming_Streaming";
            }
            else if (dynamic_cast<Gaming*>(pc) != nullptr) {
                type = "Gaming";
            }
            else if (dynamic_cast<Streaming*>(pc) != nullptr) {
                type = "Streaming";
            }
        }

        jsonObject["type"] = type;

        // Append the JSON object to the JSON array
        jsonArray.append(jsonObject);

        // Move to the next node in the linked list
        node = node->getNext();
    }

    // Create a JSON document from the JSON array
    QJsonDocument jsonDoc(jsonArray);

    // Open the file and write the JSON document to it
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(jsonDoc.toJson());
    }
}


// Method to read a linked list of PCs from a JSON file
Linked_list JsonHandler::readListFromJson(const QString& fileName) const {

    // Create an empty linked list
    Linked_list list;

    // Open the file
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly)) {

        // Read all data from the file
        QByteArray data = file.readAll();

        // Create a JSON document from the data
        QJsonDocument jsonDoc(QJsonDocument::fromJson(data));

        // Get the JSON array from the JSON document
        QJsonArray jsonArray = jsonDoc.array();

        // Loop through all items in the JSON array
        for (const auto& item : jsonArray) {
            QJsonObject jsonObject = item.toObject();

            // Read basic information about the PC
            int id = jsonObject["id"].toInt();
            QString name = jsonObject["name"].toString();
            double totalBudget = jsonObject["total_budget"].toDouble();
            double totalTdp = jsonObject["total_tdp"].toDouble();

            // Read the budget QMap
            QMap<QString, double> budget;
            QJsonObject budgetObject = jsonObject["budget"].toObject();
            for (auto it = budgetObject.begin(); it != budgetObject.end(); ++it) {
                budget[it.key()] = it.value().toDouble();
            }

            // Read the components QMap
            QMap<QString, QList<QJsonObject>> components;
            QJsonObject componentsObject = jsonObject["components"].toObject();
            for (auto it = componentsObject.begin(); it != componentsObject.end(); ++it) {
                QList<QJsonObject> componentList;
                QJsonArray componentArray = it.value().toArray();
                for (const auto& component : componentArray) {
                    componentList.append(component.toObject());
                }
                components[it.key()] = componentList;
            }

            // Read type information and create a new PC object of the appropriate type
            QString typeString = jsonObject["type"].toString();
            Pc* pc = nullptr;
            if (typeString == "Standard") {
                pc = new Standard(id, name, totalBudget, totalTdp, budget, components);
            }
            else if (typeString == "Artificial_Intelligence") {
                pc = new Artificial_Intelligence(id, name, totalBudget, totalTdp, budget, components);
            }
            else if (typeString == "Workstation") {
                pc = new Workstation(id, name, totalBudget, totalTdp, budget, components);
            }
            else if (typeString == "Office") {
                pc = new Office(id, name, totalBudget, totalTdp, budget, components);
            }
            else if (typeString == "Mixed") {
                pc = new Mixed(id, name, totalBudget, totalTdp, budget, components);
            }
            else if (typeString == "Gaming_Streaming") {
                pc = new Gaming_Streaming(id, name, totalBudget, totalTdp, budget, components);
            }
            else if (typeString == "Gaming") {
                pc = new Gaming(id, name, totalBudget, totalTdp, budget, components);
            }
            else if (typeString == "Streaming") {
                pc = new Streaming(id, name, totalBudget, totalTdp, budget, components);
            }

            list.append(pc);
        }
    }
    return list;
}



