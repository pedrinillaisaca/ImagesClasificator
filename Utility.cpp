//
// Created by leo on 9/11/20.
//

#include "ReadImages.hpp"


Utility::Utility() {        
    cout << "Ingrese el directorio root: ";        
    cin >>directorioRoot;    
    cout << endl;
    //cout<<"pedro: "<<*directorioRoot<<endl;
}

map<string, map<string, list<string>>> Utility::getSubdirectorios() {
    
    map<string, map<string, list<string>>> mapSubdirectoioImagenes; // Mapa para almacenar el nombre del subdirectorio y la lista de imagenes         
    for (const auto &entry: filesystem::directory_iterator(directorioRoot)) {        
        if (!filesystem::is_regular_file(entry.path()))
            mapSubdirectoioImagenes[entry.path()] = getImagenes(entry.path());
    }
    return mapSubdirectoioImagenes;
}


map<string, list<string>> Utility::getImagenes(const string& subdirectorio) {
    list<string> imagenesList;
    list<string> test;
    map<string, list<string>> mapaTrainTest;
    for (const auto &entry : filesystem::directory_iterator(subdirectorio)) {
        imagenesList.emplace_back(entry.path());
    }
    test.splice(test.begin(), imagenesList, imagenesList.begin(), next(imagenesList.begin(), calcularSplitting(imagenesList.size())));
    mapaTrainTest["TRAIN"] = imagenesList;
    mapaTrainTest["TEST"] = test;

    return mapaTrainTest;
}

int Utility::calcularSplitting(int size) {
    return (int) (size/0.8);
}