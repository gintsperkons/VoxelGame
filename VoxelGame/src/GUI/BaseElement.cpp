#include "BaseElement.h"
#include "../WindowManager.h"

BaseElement::BaseElement(std::string name, int type) :type(type), elementName(name), padding_left(0), padding_right(0), padding_top(0), padding_bottom(0),
verticalAlignment(Align::Top), horizontalAlignment(Align::Left), location(0, 0)
{}

BaseElement::~BaseElement()
{}

//returns type of the element
int BaseElement::GetType()
{
	return type;
}

//sets the location of the element in pixels
void BaseElement::SetLocation(float x, float y)
{
	//get the width and height of the screen drawable area
	float width = WindowManager::GetInstance()->getBufferWidth();
	float height = WindowManager::GetInstance()->getBufferHeight();

	location.x = x / width;
	location.y = y / height;
}

//sets the location of the element in procentages of the screen
void BaseElement::SetPositionRelative(float x, float y)
{
	location.x = x;
	location.y = y;
}

//sets the padding of the element in pixels
void BaseElement::SetPadding(float left, float right, float top, float bottom)
{
	padding_left = left;
	padding_right = right;
	padding_top = top;
	padding_bottom = bottom;
}

//returns the padding of the element in pixels
void BaseElement::GetPadding(float &left, float &right, float &top, float &bottom)
{
	left = padding_left;
	right = padding_right;
	top = padding_top;
	bottom = padding_bottom;
}

//returns the bounding box of the element
glm::vec2 BaseElement::GetBoundingBox()
{
	int w = 0;
	int h = 0;
	w += padding_left + padding_right;
	h += padding_top + padding_bottom;

	return glm::vec2(w, h);
}

//returns the child with the given name fro the list of allChildren
BaseElement *BaseElement::GetChild(std::string name)
{
	for (BaseElement *element : allChildren)
	{
		if (element->GetName() == name)
			return element;
	}
	return nullptr;
}

//returns the name of the element
std::string BaseElement::GetName()
{
	return elementName;
}