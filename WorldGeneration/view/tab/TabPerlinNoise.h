#pragma once
#include <QComboBox>
#include <QLabel>
#include <QMainWindow>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QWidget>

#include "input/InputDouble.h"
#include "input/InputInteger.h"

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
	QVBoxLayout* mainLayout;
	QLabel* tile;

	QWidget* sizeContainer;
	QVBoxLayout* sizeContainerLayout;
	QLabel* sizeLabel;
	QComboBox* sizeComboBox;

	InputInteger* cellSizeInput;
	InputInteger* octavesInput;
	InputDouble* persistenceInput;

	QSpacerItem* verticalSpacer;



	void setupUi(QMainWindow* ViewRootClass);

	void retranslateUi(QMainWindow* ViewRootClass);
};

