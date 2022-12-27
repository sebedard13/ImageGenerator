#include "Localization.h"

#include <codecvt>

Localization* Localization::instance = nullptr;

Localization::Localization(const std::string& language) :language(language)
{
	if (language == "fr")
	{
		this->language = "fr";
		textTable.insert(std::pair("fr-mainWindowName", "Application Génération de Monde"));
		textTable.insert(std::pair("fr-btnSave", "Sauvegarder"));
		textTable.insert(std::pair("fr-btnLoad", "Charger"));
		textTable.insert(std::pair("fr-btnQuit", "Quitter"));
		textTable.insert(std::pair("fr-btnSeeAbout", "Voir"));
		textTable.insert(std::pair("fr-worldSize1", "5000x5000"));
		textTable.insert(std::pair("fr-worldSize2", "10000x10000"));
		textTable.insert(std::pair("fr-btnGenerateMap", "Générer"));
		textTable.insert(std::pair("fr-btnFile", "Fichier"));
		textTable.insert(std::pair("fr-btnAbout", "À propos"));
		textTable.insert(std::pair("fr-tipNothing", "En attente de l'utilisateur"));
		textTable.insert(std::pair("fr-tipLoading", "Chargement..."));
	}

}

std::string Localization::get(const std::string& value)
{
	std::string keyValue = std::string().append(instance->language).append("-").append(value);
	auto pair = instance->textTable.find(keyValue);
	if (pair == instance->textTable.end())
	{
		return keyValue;
	}

	return pair->second;
}

void Localization::setLanguage(const std::string& language)
{
	if (!instance || getLanguage() != language)
	{
		delete instance;
		instance = new Localization(language);
	}
}


std::string Localization::getLanguage()
{
	return instance->language;
}
