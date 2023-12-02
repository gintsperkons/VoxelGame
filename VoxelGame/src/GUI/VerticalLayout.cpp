#include "VerticalLayout.h"

VerticalLayout::VerticalLayout(std::string name) :BaseElement(name, ElementType::VLayout)
{}

VerticalLayout::~VerticalLayout()
{}

// Add an element to the layout
void VerticalLayout::AddElement(BaseElement *element)
{
	allChildren.push_back(element);
}

// Render the layout and all of its children
void VerticalLayout::Render()
{

	int totalHeight = 0;
	totalHeight += padding_top;

	// Render all children in the layout and calculate the total height of rendered children to not overlap them
	for (BaseElement *element : allChildren)
	{
		element->space_top = totalHeight;
		element->Render();
		totalHeight += element->GetBoundingBox().y;
	}
	int i = 0;
}

void VerticalLayout::Clear()
{}
