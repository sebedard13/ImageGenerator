#pragma once
#include <string>
#include <unordered_map>
#include <memory>

class Localization
{
public:
	Localization() = delete;
	Localization(const Localization& other) = delete;
	Localization(Localization&& other) noexcept = delete;
	Localization& operator=(const Localization& other) = delete;
	Localization& operator=(Localization&& other) noexcept = delete;

	Localization(const std::string& language);
	static std::wstring get(const std::string& value);
	static void setLanguage(const std::string& language); //ISO 639-1
	static std::string getLanguage(); //ISO 639-1

private:
	static Localization* instance;
	std::string language{ "undefined-language" };
	std::unordered_map<std::string, std::wstring> textTable{};
};
