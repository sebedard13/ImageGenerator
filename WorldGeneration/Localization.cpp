#include "Localization.h"

#include <codecvt>

Localization* Localization::instance = nullptr;

Localization::Localization(const std::string& language) :language(language)
{
	this->language = "fr";
	textTable.insert(std::pair("fr-menu", L"Menu"));
	textTable.insert(std::pair("fr-languages", L"Langues"));
	textTable.insert(std::pair("fr-localizationTest", L"Test de la localisation"));
}

std::wstring Localization::get(const std::string& value)
{
	std::string keyValue = std::string().append(instance->language).append("-").append(value);
	auto pair = instance->textTable.find(keyValue);
	if (pair == instance->textTable.end())
	{
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		return converter.from_bytes(keyValue);
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
