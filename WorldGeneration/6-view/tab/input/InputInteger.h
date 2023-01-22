#pragma once
#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>
#include <qwidget.h>
class InputInteger :
	public QWidget
{
public:

	InputInteger(const std::string& textId, int defaultValue, int min = INT32_MIN, int max = INT32_MAX)
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


	[[nodiscard]] int getValue() const { return value; }
private:
	QVBoxLayout* containerLayout;
	QLabel* label;
	QLineEdit* input;
	void setValue(int v);

	const std::string textID;
	const int min;
	const int max;
	const int defaultV;
	int value;





};

