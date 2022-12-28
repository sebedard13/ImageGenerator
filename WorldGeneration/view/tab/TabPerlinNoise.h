#pragma once
#include <QComboBox>
#include <QLabel>
#include <QMainWindow>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QWidget>

class TabPerlinNoise : public QWidget
{
public:
	TabPerlinNoise() = default;
	TabPerlinNoise(const TabPerlinNoise& other) = delete;
	TabPerlinNoise(TabPerlinNoise&& other) noexcept = delete;
	TabPerlinNoise& operator=(const TabPerlinNoise& other) = delete;
	TabPerlinNoise& operator=(TabPerlinNoise&& other) noexcept = delete;

	QVBoxLayout* verticalLayout_6;
	QScrollArea* scrollArea;
	QWidget* scrollAreaWidgetContents;
	QVBoxLayout* verticalLayout_7;
	QLabel* label_18;
	QWidget* widget;
	QVBoxLayout* verticalLayout_9;
	QLabel* label_2;
	QComboBox* comboBox;
	QLabel* label_5;
	QLabel* label_6;
	QLabel* label_7;
	QLabel* label_8;
	QLabel* label_9;
	QLabel* label_10;
	QLabel* label_11;
	QLabel* label_12;
	QLabel* label_13;
	QLabel* label_14;
	QLabel* label_15;
	QLabel* label_16;
	QLabel* label_17;
	QSpacerItem* verticalSpacer;

	void setupUi(QMainWindow* ViewRootClass);

	void retranslateUi(QMainWindow* ViewRootClass);
};

