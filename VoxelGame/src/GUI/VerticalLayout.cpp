#include "VerticalLayout.h"
#include "Text.h"

#include <iostream>

VerticalLayout::VerticalLayout(std::string name):BaseElement(name, ElementType::VLayout)
{}

VerticalLayout::~VerticalLayout()
{}

void VerticalLayout::AddElement(BaseElement *element)
{
	elements.push_back(element);
}

void VerticalLayout::Render()
{

	int totalHeight = 0;
	totalHeight += padding_top;
	for (BaseElement *element : elements)
	{
		element->space_top = totalHeight;
		element->Render();
		totalHeight += element->GetBoundingBox().y;
	}
	int i = 0;
}

void VerticalLayout::Clear()
{}
