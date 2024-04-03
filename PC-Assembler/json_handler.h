#ifndef JSON_HANDLER_H
#define JSON_HANDLER_H

#include <QString>
#include "linked_list.h"

class JsonHandler {
public:
    // Saves a Linked_list object to a JSON file specified by the fileName argument
    void saveListToJson(const Linked_list& list, const QString& fileName) const;

    // Reads a Linked_list object from a JSON file specified by the fileName argument and returns it
    Linked_list readListFromJson(const QString& fileName) const;
};


#endif
