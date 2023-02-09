#pragma once

#include <QString>

#include "../3-infrastructure/Localization.h"

class ViewsUtils {
public:
    ViewsUtils() = delete;

    ViewsUtils(const ViewsUtils &other) = delete;

    ViewsUtils(ViewsUtils &&other) noexcept = delete;

    ViewsUtils &operator=(const ViewsUtils &other) = delete;

    ViewsUtils &operator=(ViewsUtils &&other) noexcept = delete;

    ~ViewsUtils() = default;

    static QString local(const std::string& key) {
        return QString::fromStdString(Localization::get(key));
    }

};
