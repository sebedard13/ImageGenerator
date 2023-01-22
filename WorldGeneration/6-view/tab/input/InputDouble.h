#pragma once
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <qwidget.h>
class InputDouble :
	public QWidget
{
public:

	InputDouble(const std::string& textId, double defaultValue, double min = 0, double max = 1)
		: textID(textId),
		min(min),
		max(max),
		defaultV((defaultValue >= min && defaultValue <= max) ? defaultValue : min)
	{
		setupUi();
	}

	void setupUi();

	void retranslateUi();

	void changeInput();

	[[nodiscard]] double getValue() const { return value; }
private:
	QVBoxLayout* containerLayout;
	QLabel* label;
	QLineEdit* input;
	void setValue(double v);

	const std::string textID;
	const double min;
	const double max;
	const double defaultV;
	double value;

};
