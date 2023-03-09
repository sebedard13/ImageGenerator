#include <iostream>
#include <fstream>
#include "Localization.h"


Localization *Localization::instance = nullptr;
const std::filesystem::path Localization::folder = "localization";

Localization::Localization(const std::string &language)
        : language(language) {

    std::string filename =  std::string().append(language).append(".po");
    std::filesystem::path file = folder / filename;

    if (std::filesystem::exists(file)) {
        this->language = language;
        textTable.clear();
        std::ifstream fileStream(file.string());
        std::string lineStream;

        //Basic .po file reader and insert key in table
        while (getline (fileStream, lineStream)) {
            if(lineStream.find_first_of("mgsid",0)!=std::string::npos){
                std::string id = lineStream.erase(0,7);
                id = id.erase(id.size()-1,1);
                if(getline (fileStream, lineStream)){
                    if(lineStream.find("msgstr",0,6)!=std::string::npos){
                        std::string value = lineStream.erase(0, 8);
                        value = value.erase(value.size() - 1, 1);

                        textTable.insert(std::pair(id, value));
                    }
                }

            }
        }
    }
    else{
        std::cout<< "Localization file does not exists for language: "<<language<<std::endl;
        this->language = "none";
    }

}

std::string Localization::get(const std::string &value) {
    std::string keyValue = std::string().append(value);
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

std::vector<std::string> Localization::getAllLanguages() {
    std::vector<std::string> rtn {};
    if(std::filesystem::exists(folder)){
        for (const auto & entry : std::filesystem::directory_iterator(folder)) {
            const std::filesystem::path& path = entry.path();
            std::string filename = path.filename().string();
            auto indexPo = filename.find('.');
            if(filename.find(".po",indexPo)){
                filename = filename.substr(0,indexPo);
                rtn.push_back(filename);
            }
        }
    }
        
    return std::move(rtn);
}
