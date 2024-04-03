
#ifndef FILE_READER_H
#define FILE_READER_H
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>


class File_Reader{
public:
    // Reads a dataset from a file specified by the QString argument and returns it as a QJsonArray
    static QJsonArray readDataset(QString s);

    // Cleans a dataset represented as a QJsonArray and returns the cleaned dataset as a QJsonArray
    static QJsonArray cleanDataset(QJsonArray s);

    // Cleans a dataset represented as a QJsonArray by removing invalid case data and returns the cleaned dataset as a QJsonArray
    static QJsonArray cleanDataset_Case(QJsonArray s);

    // Cleans a dataset represented as a QJsonArray by removing invalid memory data and returns the cleaned dataset as a QJsonArray
    static QJsonArray cleanDataset_Memory(QJsonArray s);

    // Cleans a dataset represented as a QJsonArray by removing invalid case fan data and returns the cleaned dataset as a QJsonArray
    static QJsonArray cleanDataset_CaseFan(QJsonArray s);

    // Cleans a dataset represented as a QJsonArray by removing invalid video card data and returns the cleaned dataset as a QJsonArray
    static QJsonArray cleanDataset_VideoCard(QJsonArray s);
};


#endif // FILE_READER_H
