#include <file_reader.h>
#include <QCoreApplication>
#include <QDebug>
#include <QDir>

// Method to read a dataset from a file and return it as a QJsonArray
QJsonArray File_Reader::readDataset(QString s){

    QString jsonStr;
    QJsonArray myArr;

    // Get the application directory and construct the file path
    QString appDir = QCoreApplication::applicationDirPath();
    QString filePath = QDir(appDir).filePath("../PC-Assembler/data/" + s);
    qDebug() << "File path:" << filePath;

    QFile myFile(filePath);

    // Check if the file exists
    if (myFile.exists()){
        // Open the file for reading
        if (myFile.open(QIODevice::ReadOnly | QIODevice::Text)){
            // Read the entire file into a string
            jsonStr = myFile.readAll();
            myFile.close();

            // Parse the JSON string into a QJsonDocument
            QJsonDocument myDoc = QJsonDocument::fromJson(jsonStr.toUtf8());

            // Get the JSON array from the document
            myArr = myDoc.array();

            // Clean the dataset
            myArr = cleanDataset(myArr);
        }
    }
    return myArr;
}

// Method to clean a dataset by removing invalid entries
QJsonArray File_Reader::cleanDataset(QJsonArray myArr){
    QJsonObject obj;

    // Loop through all objects in the array
    for(auto it = myArr.begin(); it != myArr.end(); it++){
        obj = (*it).toObject();

        // Check if any of the fields are invalid
        if(obj["rating"] == "null" ||
            obj["rating"] == "0" ||
            obj["rating"].toDouble() == 0 ||
            obj["rating_count"] == "null" ||
            obj["rating_count"] == "0" ||
            obj["rating_count"].toDouble() < 5 ||
            obj["price_usd"] == "null" ||
            obj["price_usd"] == "0" ||
            obj["price_usd"].toDouble() == 0 ||
            obj["name"] == "null"){

            // Remove the object from the array
            myArr.erase(it);

            // Decrement the iterator to account for the removed object
            it--;
        }
    }

    return myArr;
}

// Method to clean a dataset of cases by removing invalid entries
QJsonArray File_Reader::cleanDataset_Case(QJsonArray myArr){
    QJsonObject obj;

    // Loop through all objects in the array
    for(auto it = myArr.begin(); it != myArr.end(); it++){
        obj = (*it).toObject();

        // Check if the type field is invalid
        if(obj["type"] == "null"){

            // Remove the object from the array
            myArr.erase(it);

            // Decrement the iterator to account for the removed object
            it--;
        }
    }

    return myArr;
}

// Method to clean a dataset of memory modules by removing invalid entries
QJsonArray File_Reader::cleanDataset_Memory(QJsonArray myArr){
    QJsonObject obj;

    // Loop through all objects in the array
    for(auto it = myArr.begin(); it != myArr.end(); it++){
        obj = (*it).toObject();

        // Check if any of the fields are invalid or if the speed contains DDR2
        if(obj["speed"].toString().contains("DDR2") ||
            obj["speed"] == "null" ||
            obj["speed"] == "0"){

            // Remove the object from the array
            myArr.erase(it);

            // Decrement the iterator to account for the removed object
            it--;
        }
    }

    return myArr;
}

// Method to clean a dataset of case fans by removing invalid entries
QJsonArray File_Reader::cleanDataset_CaseFan(QJsonArray myArr){
    QJsonObject obj;

    // Loop through all objects in the array
    for(auto it = myArr.begin(); it != myArr.end(); it++){
        obj = (*it).toObject();

        // Check if the name contains "Pack"
        if(obj["name"].toString().contains("Pack")){

            // Remove the object from the array
            myArr.erase(it);

            // Decrement the iterator to account for the removed object
            it--;
        }
    }

    return myArr;
}

// Method to clean a dataset of video cards by removing invalid entries
QJsonArray File_Reader::cleanDataset_VideoCard(QJsonArray myArr){
    QJsonObject obj;

    // Loop through all objects in the array
    for(auto it = myArr.begin(); it != myArr.end(); it++){
        obj = (*it).toObject();

        // Check if any of the fields are invalid
        if(obj["memory"] == "null" ||
            obj["memory"] == "0" ||
            obj["chipset"] == "null"){

            // Remove the object from the array
            myArr.erase(it);

            // Decrement the iterator to account for the removed object
            it--;
        }
    }

    return myArr;
}
