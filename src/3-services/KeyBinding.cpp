#include "KeyBinding.h"

KeyBinding *KeyBinding::instance = new KeyBinding();

KeyBinding::KeyBinding() {
    textTable.insert(std::pair("btnSave", "Ctrl+S"));
    textTable.insert(std::pair("btnLoad", "Ctrl+O"));
    textTable.insert(std::pair("btnQuit", "Ctrl+Q"));
    textTable.insert(std::pair("btnGenerateMap", "Ctrl+G"));
}

std::string KeyBinding::get(const std::string &value) {
    auto pair = instance->textTable.find(value);
    if (pair == instance->textTable.end()) {
        return "";
    }

    return pair->second;
}
