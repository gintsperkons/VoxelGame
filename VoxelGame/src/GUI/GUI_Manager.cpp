#include <iostream>

#include "GUI_Manager.h"


//Singleton instance of the GUI_Manager
static GUI_Manager *instance = new GUI_Manager();
GUI_Manager *GUI_Manager::GetInstance()
{
	if (instance == nullptr)
		instance = new GUI_Manager();
	return instance;
}

GUI_Manager::GUI_Manager() : BaseElement("GUI_Manager", ElementType::GUI_Manager)
{}

GUI_Manager::~GUI_Manager()
{
	Clear();
}

//Render call for its children
void GUI_Manager::Render()
{
	for (BaseElement *element : allChildren)
	{
		element->Render();
	}
}

//Add a child to the list of children
void GUI_Manager::AddElement(BaseElement *element)
{
	allChildren.push_back(element);
}


//Create a text element
Text *GUI_Manager::CreateTextElement(std::string name)
{
	Text *text = new Text(name);
	text->Init();
	return text;
}

//Create a vertical layout element
VerticalLayout *GUI_Manager::CreateVerticalLayout(std::string name)
{
	VerticalLayout *layout = new VerticalLayout(name);
	return layout;
}

//Clear all children
void GUI_Manager::Clear()
{
	for (BaseElement *element : allChildren)
	{
		element->Clear();
	}
}




