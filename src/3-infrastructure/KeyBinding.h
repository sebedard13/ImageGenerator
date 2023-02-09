#pragma once

#include <string>
#include <unordered_map>

class KeyBinding {
public:
    KeyBinding(const KeyBinding &other) = delete;

    KeyBinding(KeyBinding &&other) noexcept = delete;

    KeyBinding &operator=(const KeyBinding &other) = delete;

    KeyBinding &operator=(KeyBinding &&other) noexcept = delete;

    ~KeyBinding() = default;

    static std::string get(const std::string &value);

private:
    KeyBinding();
    static KeyBinding *instance;
    std::string language{"undefined-language"};
    std::unordered_map<std::string, std::string> textTable{};
};