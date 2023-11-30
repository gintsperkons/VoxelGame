#include "GUI_Manager.h"
#include <iostream>

static GUI_Manager *instance = new GUI_Manager();
GUI_Manager *GUI_Manager::GetInstance()
{
	if (instance == nullptr)
		instance = new GUI_Manager();
	return instance;
}

GUI_Manager::GUI_Manager()
{}

GUI_Manager::~GUI_Manager()
{
Clear();
}

void GUI_Manager::Render()
{
for(BaseElement* element : allElements)
{
	element->Render();
}
}

void GUI_Manager::AddElement(BaseElement *element)
{
	allElements.push_back(element);
}


Text *GUI_Manager::CreateTextElement(std::string name)
{
	Text *text = new Text(name);
	text->Init();
	return text;
}

VerticalLayout *GUI_Manager::CreateVerticalLayout(std::string name)
{
	VerticalLayout *layout = new VerticalLayout(name);
	return layout;
}

void GUI_Manager::Clear()
{
	for (BaseElement *text : allElements)
	{
		text->Clear();
	}
}


