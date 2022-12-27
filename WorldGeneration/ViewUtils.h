#pragma once
#include <QString>

#include "Localization.h"

class ViewsUtils
{
public:
	static QString local(std::string key)
	{
		return QString::fromStdString(Localization::get(key));
	}
};
