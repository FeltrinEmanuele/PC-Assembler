
#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QDebug>

// Constructor for the MainWindow class
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    // Create a user_input widget
    inputWidget = new user_input("Nome Build", "Max Budget Build", "Tipo Build", {"Server - Standard", "Server - AI", "Full Setup - Productivity Workstation"
                                                                                  , "Full Setup - Productivity Office", "Full Setup - Gaming", "Full Setup - Streaming"
                                                                                  , "Full Setup - Gaming & Streaming", "Mixed Full Setup - Gaming Office", "Mixed Full Setup - Gaming Workstation"
                                                                                  , "Mixed Full Setup - Streaming Office", "Mixed Full Setup - Streaming Workstation", "Mixed Full Setup - Workstation Office"}, "Crea Build", this);

    // Create a QListWidget
    listWidget = new QListWidget(this);

    // Create a save_load_widget
    saveLoadWidget = new save_load_widget("Salva File","Carica File", this);

    // Create a builds_widget
    buildsWidget = new builds_widget("Visualizza Build", this);

    // Create a layout for the left side of the window
    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->addWidget(inputWidget);
    leftLayout->addStretch();

    // Create a layout for the right side of the window
    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightLayout->addWidget(saveLoadWidget);
    rightLayout->addWidget(buildsWidget);

    // Create a main layout and add the left and right layouts to it
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(leftLayout);
    mainLayout->addWidget(listWidget);
    mainLayout->addLayout(rightLayout);

    // Create a central widget and set its layout to the main layout
    QWidget *centralWidget = new QWidget;
    centralWidget->setLayout(mainLayout);

    // Set the central widget of the main window
    setCentralWidget(centralWidget);

    // Create an empty linked list
    mainList = Linked_list();

    // Connect signals and slots
    connect(inputWidget, SIGNAL(create_build()), this, SLOT(handle_create_build()));
    connect(buildsWidget, SIGNAL(select_build()), this, SLOT(handle_select_build()));
    connect(saveLoadWidget, SIGNAL(save()), this, SLOT(handle_save()));
    connect(saveLoadWidget, SIGNAL(load()), this, SLOT(handle_load()));
    connect(buildsWidget, SIGNAL(delete_build), this, SLOT(handle_delete_build()));
    connect(buildsWidget, SIGNAL(rename_build()), this, SLOT(handle_rename_build()));
    connect(buildsWidget, SIGNAL(reset_all()), this, SLOT(handle_reset_all()));

    if (connect(buildsWidget, SIGNAL(delete_build()), this, SLOT(handle_delete_build()))) {
        qDebug() << "Connected delete_build signal to handle_delete_build slot";
    } else {
        qDebug() << "Failed to connect delete_build signal to handle_delete_build slot";
    }

    if (connect(buildsWidget, SIGNAL(rename_build()), this, SLOT(handle_rename_build()))) {
        qDebug() << "Connected rename_build signal to handle_rename_build slot";
    } else {
        qDebug() << "Failed to connect rename_build signal to handle_rename_build slot";
    }

    if (connect(buildsWidget, SIGNAL(reset_all()), this, SLOT(handle_reset_all()))) {
        qDebug() << "Connected reset_all signal to handle_reset_all slot";
    } else {
        qDebug() << "Failed to connect reset_all signal to handle_reset_all slot";
    }
}



// Function to generate a unique ID for a new PC object in the given linked list
int makeId(const Linked_list& list) {

    // Start with an ID of 0
    int id = 0;
    bool idFound = false;

    // Loop until a unique ID is found
    while (!idFound) {
        idFound = true;

        // Loop through all nodes in the linked list
        Node* current = list.getFirst();
        while (current != nullptr) {

            // Check if the current node's PC object has the same ID
            if (current->getPc()->getID() == id) {
                idFound = false;
                break;
            }

            // Move to the next node
            current = current->getNext();
        }

        // Increment the ID if it was not unique
        if (!idFound) {
            id++;
        }
    }

    // Return the unique ID
    return id;
}



// Slot to handle the create_build signal from the user_input widget
void MainWindow::handle_create_build()
{
    // Check if the budget value is a valid integer
    bool check;
    check = inputWidget->getDataWidgetPrice().toInt();
    if (!check)
    {
        // Show an error message if the budget value is not a valid integer
        QMessageBox::critical(this, "Errore nei dati forniti", "Si prega di fornire un valore numerico INTERO per il budget");
    }
    // Check if the name or budget fields are empty
    else if (inputWidget->getDataWidgetName().isEmpty() || inputWidget->getDataWidgetPrice().isEmpty())
    {
        // Show an error message if any field is empty
        QMessageBox::critical(this, "Errore nei dati forniti", "Si prega di compilare tutti i campi");
    }
    else
    {
        // Get the build type, name, and budget from the user_input widget
        QString buildType = inputWidget->getBuildText();
        QString buildName = inputWidget->getDataWidgetName();
        int buildBudget = inputWidget->getDataWidgetPrice().toInt();

        // Generate a unique ID for the new PC object
        int id = makeId(mainList);


        if(buildType == "Server - Standard"){
            Standard* standard = new Standard(id, buildName, buildBudget);
            standard->assemble();
            if(checkBuild(standard, this)){
                displayBuild(standard);
                mainList.append(standard);
            }
        }else if(buildType == "Server - AI"){
            Artificial_Intelligence* ai = new Artificial_Intelligence(id, buildName, buildBudget);
            ai->assemble();
            if(checkBuild(ai, this)){
                displayBuild(ai);
                mainList.append(ai);
            }
        }else if(buildType == "Full Setup - Productivity Workstation"){
            Workstation* workstation = new Workstation(id, buildName, buildBudget);
            workstation->assemble();
            if(checkBuild(workstation, this)){
                displayBuild(workstation);
                mainList.append(workstation);
            }
        }else if(buildType == "Full Setup - Productivity Office"){
            Office* office = new Office(id, buildName, buildBudget);
            office->assemble();
            if(checkBuild(office, this)){
                displayBuild(office);
                mainList.append(office);
            }
        }else if(buildType == "Full Setup - Gaming"){
            Gaming* gaming = new Gaming(id, buildName, buildBudget);
            gaming->assemble();
            if(checkBuild(gaming, this)){
                displayBuild(gaming);
                mainList.append(gaming);
            }
        }else if(buildType == "Full Setup - Streaming"){
            Streaming* streaming = new Streaming(id, buildName, buildBudget);
            streaming->assemble();
            if(checkBuild(streaming, this)){
                displayBuild(streaming);
                mainList.append(streaming);
            }
        }
        else if(buildType == "Full Setup - Gaming & Streaming"){
            Gaming_Streaming* gaming_streaming = new Gaming_Streaming(id, buildName, buildBudget);
            gaming_streaming->assemble();
            if(checkBuild(gaming_streaming, this)){
                displayBuild(gaming_streaming);
                mainList.append(gaming_streaming);
            }
        }else if(buildType == "Mixed Full Setup - Gaming Office"){
            Office office = Office(id, buildName, buildBudget);
            Gaming gaming = Gaming(id, buildName, buildBudget);

            Mixed* mixed = new Mixed(id, buildName, buildBudget);
            mixed->combineBudget(office,gaming);
            mixed->assemble();
            if (checkBuild(mixed,  this)) {
                displayBuild(mixed);
                mainList.append(mixed);
            }
        }else if(buildType == "Mixed Full Setup - Gaming Workstation"){
            Workstation workstation = Workstation(id, buildName, buildBudget);
            Gaming gaming = Gaming(id, buildName, buildBudget);

            Mixed* mixed = new Mixed(id, buildName, buildBudget);
            mixed->combineBudget(workstation,gaming);
            mixed->assemble();
            if(checkBuild(mixed, this)){
                displayBuild(mixed);
                mainList.append(mixed);
            }
        }else if(buildType == "Mixed Full Setup - Streaming Office"){
            Streaming streaming = Streaming(id, buildName, buildBudget);
            Office office = Office(id, buildName, buildBudget);

            Mixed* mixed = new Mixed(id, buildName, buildBudget);
            mixed->combineBudget(streaming,office);
            mixed->assemble();
            if(checkBuild(mixed, this)){
                displayBuild(mixed);
                mainList.append(mixed);
            }
        }else if(buildType == "Mixed Full Setup - Streaming Workstation"){
            Streaming streaming = Streaming(id, buildName, buildBudget);
            Workstation workstation = Workstation(id, buildName, buildBudget);

            Mixed* mixed = new Mixed(id, buildName, buildBudget);
            mixed->combineBudget(streaming,workstation);
            mixed->assemble();
            if(checkBuild(mixed, this)){
                displayBuild(mixed);
                mainList.append(mixed);
            }
        }else if(buildType == "Mixed Full Setup - Workstation Office"){
            Workstation workstation = Workstation(id, buildName, buildBudget);
            Office office = Office(id, buildName, buildBudget);

            Mixed* mixed = new Mixed(id, buildName, buildBudget);
            mixed->combineBudget(office,workstation);
            mixed->assemble();
            if(checkBuild(mixed, this)){
                displayBuild(mixed);
                mainList.append(mixed);
            }
        }
        buildsWidget->displayList(mainList);
    }
}

// This function displays the build of a PC object
void MainWindow::displayBuild(Pc* pc) const{
    // Get the name and type for all components in the PC
    QList<QPair<QString, QString>> nameForAllComponents = pc->getNameAndTypeForAllComponents();
    // Get the price for all components in the PC
    QList<double> priceForAllComponents = pc->getPriceForAllComponents();
    // Get the rating for all components in the PC
    QList<int> ratingForAllComponents =  pc->getRatingForAllComponents();
    QString itemText;

    // Clear the list widget
    listWidget->clear();
    // Loop through all components
    for (int i = 0; i < nameForAllComponents.size(); ++i) {
        // Get the component name and type
        QString componentName = nameForAllComponents.at(i).first;
        QString componentType = nameForAllComponents.at(i).second;
        // Format the item text with component information
        itemText = QString("%2 -> %1 -> Prezzo: %3 $, Rating: %4").arg(componentName).arg(componentType).arg(priceForAllComponents.at(i)).arg(ratingForAllComponents.at(i));
        // Add the item to the list widget
        listWidget->addItem(itemText);
    }
    // Add the effective price to the list widget
    itemText = QString("Prezzo Effettivo -> " + QString::number(pc->calculateEffectivePrice()) + " $");
    listWidget->addItem(itemText);
    // Add the total TDP to the list widget
    itemText = QString("TDP Totale -> " + QString::number(pc->getTotalTdp()) + " W");
    listWidget->addItem(itemText);
    // Add the build name to the list widget
    itemText = QString("Nome Build -> " + pc->getName());
    listWidget->addItem(itemText);
}

// This function checks if the build of a PC object is valid
bool MainWindow::checkBuild(Pc *pc, QWidget *parent) const {
    // Print debug message
    qDebug() << "Checking build for Pc" << pc;
    // Check if the last check for the PC failed
    if (pc->lastCheck() == false) {
        // Print debug message
        qDebug() << "Last check failed for Pc" << pc;
        // Show an error message to the user
        QMessageBox::critical(parent, "Errore nel Budget Massimo fornito", "Il Budget Massimo di input è troppo basso per fare una build");
            return false;
    }
    // Print debug message
    qDebug() << "Build check passed for Pc" << pc;
    return true;
}

// This function handles deleting a build
void MainWindow::handle_delete_build(){
    // Print debug message
    qDebug() << "In handle_delete_build"; // Add this line

    // Get the ID of the selected build from the builds widget
    int id = buildsWidget->getIdFromListWidget();
    if(id != -1){
        // Find the PC object with the given ID
        Pc* pc = mainList.findPcById(id);
        // Destroy the PC object from the main list
        mainList.destroy(mainList.findNode(pc));
        // Update the builds widget to display the updated main list
        buildsWidget->displayList(mainList);
        // Clear the list widget
        listWidget->clear();
    }
}

// This function handles renaming a build
void MainWindow::handle_rename_build(){
    // Print debug message
    qDebug() << "In handle_rename_build";

    // Get the ID of the selected build from the builds widget
    int id = buildsWidget->getIdFromListWidget();
    if(id != -1){
        // Prompt the user for a new name
        bool ok;
        QString newName = QInputDialog::getText(this, tr("Rename Build"),
                                                tr("Enter new name:"), QLineEdit::Normal,
                                                "", &ok);
        if (ok && !newName.isEmpty()) {
            // Update the build with the new name
            Pc* pc = mainList.findPcById(id);
            pc->setName(newName);
            // Update the builds widget to display the updated main list
            buildsWidget->displayList(mainList);
            // Display the updated build in the list widget
            displayBuild(pc);

        }
    }
}

// This function handles resetting all builds and user input
void MainWindow::handle_reset_all(){

    // Print debug message
    qDebug() << "In handle_reset_all";

    // Reset everything
    mainList.clear();
    listWidget->clear();
    buildsWidget->displayList(mainList);
    // Clear any user input in the inputWidget
    inputWidget->dataWidgetName->lineEdit->clear();
    inputWidget->dataWidgetPrice->lineEdit->clear();

}

// This function handles selecting a build
void MainWindow::handle_select_build() {
    // Get the ID of the selected build from the builds widget
    int id = buildsWidget->getIdFromListWidget();
    if(id != -1){
        // Find the PC object with the given ID
        Pc* pc = mainList.findPcById(id);
        // Display the build in the list widget
        displayBuild(pc);

    }
}

// This function handles saving the main list to a JSON file
void MainWindow::handle_save() {
    // Prompt the user to select a directory to save the file in
    QString dirName = QFileDialog::getExistingDirectory(this, tr("Select Directory"), "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if (dirName.isEmpty())
        return;

    // Prompt the user to enter a file name
    bool ok;
    QString fileName = QInputDialog::getText(this, tr("Enter File Name"), tr("File name:"), QLineEdit::Normal, "list", &ok);

    if (!ok || fileName.isEmpty())
        return;

    // Append the ".json" extension to the file name
    if (!fileName.endsWith(".json", Qt::CaseInsensitive))
        fileName += ".json";

    // Create a JsonHandler object
    JsonHandler jsonHandler;

    // Set the full file path
    QString filePath = dirName + "/" + fileName;

    // Save the list to the JSON file
    jsonHandler.saveListToJson(mainList, filePath);

}

// This function handles loading a main list from a JSON file
void MainWindow::handle_load() {

    // Prompt the user to select a JSON file to load from
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open File"), "",
                                                    tr("JSON Files (*.json);;All Files (*)"));
    if (fileName.isEmpty())
        return;

    // Create a JsonHandler object
    JsonHandler jsonHandler;

    // Reset everything before loading from the file
    handle_reset_all();

    // Load the list from the JSON file
    mainList = jsonHandler.readListFromJson(fileName);

    // Update the builds widget to display the loaded main list
    buildsWidget->displayList(mainList);

}



