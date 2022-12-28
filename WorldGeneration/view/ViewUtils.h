#pragma once
#include <QString>

#include "../Localization.h"

class ViewsUtils
{
public:
	ViewsUtils() = delete;
	ViewsUtils(const ViewsUtils& other) = delete;
	ViewsUtils(ViewsUtils&& other) noexcept = delete;
	ViewsUtils& operator=(const ViewsUtils& other) = delete;
	ViewsUtils& operator=(ViewsUtils&& other) noexcept = delete;
	~ViewsUtils() = default;

	static QString local(std::string key)
	{
		return QString::fromStdString(Localization::get(key));
	}
};