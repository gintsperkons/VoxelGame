#pragma once
#include "Text.h"
#include "VerticalLayout.h"
#include <vector>

class GUI_Manager : public BaseElement
{

public:
	GUI_Manager();
	~GUI_Manager();
	Text *CreateTextElement(std::string name);
	VerticalLayout *CreateVerticalLayout(std::string name);
	void Render();
	void AddElement(BaseElement *element);
	void Clear();

	static GUI_Manager *GetInstance();
};

