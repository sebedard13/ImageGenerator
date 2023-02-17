#include <iostream>
#include "Localization.h"

Localization *Localization::instance = nullptr;

Localization::Localization(const std::string &language)
        : language(language) {
    if (language == "fr") {
        this->language = "fr";
        textTable.insert(std::pair("fr-mainWindowName", "Application Génération de Monde"));

        textTable.insert(std::pair("fr-btnSave", "Sauvegarder"));
        textTable.insert(std::pair("fr-saveRtnEmpty", "Impossible de sauvegarder l'image, l'image est vide"));
        textTable.insert(std::pair("fr-saveRtnGood", "Image sauvegardée avec succès"));
        textTable.insert(std::pair("fr-saveRtnBad", "Impossible de sauvegarder l'image"));
        textTable.insert(std::pair("fr-saveRtnCompression", "Compression de l'image"));


        textTable.insert(std::pair("fr-btnLoad", "Charger"));
        textTable.insert(std::pair("fr-btnQuit", "Quitter"));
        textTable.insert(std::pair("fr-btnSeeAbout", "Voir"));
        textTable.insert(std::pair("fr-btnGenerateMap", "Générer"));
        textTable.insert(std::pair("fr-btnFile", "Fichier"));
        textTable.insert(std::pair("fr-btnAbout", "À propos"));
        textTable.insert(std::pair("fr-btnPerformance", "Performance"));
        textTable.insert(std::pair("fr-btnThreadNumberTitle", "Nombre de thread"));

        textTable.insert(std::pair("fr-tipNothing", "En attente de l'utilisateur"));
        textTable.insert(std::pair("fr-tipLoading", "Chargement..."));
        textTable.insert(std::pair("fr-tipLoadingPerlinNoise", "Génération bruit Perlin"));
        textTable.insert(std::pair("fr-tipLoadingRandomVoronoi", "Génération diagramme de Voronoi"));
        textTable.insert(std::pair("fr-tipLoadView", "Génération de l'image"));
        textTable.insert(std::pair("fr-tipAlgoDistanceFromCenter", "Calcul des distances"));

        //Algo Perlin Noise
        textTable.insert(std::pair("fr-algoPerlinNoiseName", "Bruit de Perlin"));
        textTable.insert(std::pair("fr-algoRandomVoronoiName", "Voronoi Aléatoire"));

        textTable.insert(std::pair("fr-labelSize", "Taille de l'image"));
        textTable.insert(std::pair("fr-labelSeed", "Germe aléatoire"));
        textTable.insert(std::pair("fr-labelCellSize", "Taille du plus grande cellule"));
        textTable.insert(std::pair("fr-labelOctaves", "Octaves pour augmenter les détails"));
        textTable.insert(std::pair("fr-labelPersistence", "Persistance dans les octaves"));
        textTable.insert(std::pair("fr-size100", "100x100"));
        textTable.insert(std::pair("fr-size500", "500x500"));
        textTable.insert(std::pair("fr-size1000", "1000x1000"));
        textTable.insert(std::pair("fr-size2500", "2500x2500"));
        textTable.insert(std::pair("fr-size5000", "5000x5000"));


        textTable.insert(std::pair("fr-labelNbPoints", "Nombre de points"));
    }

}

std::string Localization::get(const std::string &value) {
    std::string keyValue = std::string().append(instance->language).append("-").append(value);
    auto pair = instance->textTable.find(keyValue);
    if (pair == instance->textTable.end()) {
        std::cout<<"Warning: Localization missing: "<<keyValue<<std::endl;
        return keyValue;
    }

    return pair->second;
}

void Localization::setLanguage(const std::string &language) {
    if (!instance || getLanguage() != language) {
        delete instance;
        instance = new Localization(language);
    }
}


std::string Localization::getLanguage() {
    return instance->language;
}
