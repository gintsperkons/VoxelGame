#include "BaseElement.h"
#include "../WindowManager.h"

BaseElement::BaseElement(std::string name,int type) :type(type), elementName(name), padding_left(0), padding_right(0), padding_top(0), padding_bottom(0),
verticalAlignment(Align::Top), horizontalAlignment(Align::Left), location(0, 0)
{

}

BaseElement::~BaseElement()
{}

int BaseElement::GetType()
{
	return type;
}

void BaseElement::SetLocation(float x, float y)
{
	float width = WindowManager::GetInstance()->getBufferWidth();
	float height = WindowManager::GetInstance()->getBufferHeight();
	location.x = x / width;
	location.y = y / height;
}

void BaseElement::SetPositionRelative(float x, float y)
{
	location.x = x;
	location.y = y;
}
void BaseElement::GetPadding(float &left, float &right, float &top, float &bottom)
{
	left = padding_left;
	right = padding_right;
	top = padding_top;
	bottom = padding_bottom;
}

void BaseElement::SetPadding(float left, float right, float top, float bottom)
{
	padding_left = left;
	padding_right = right;
	padding_top = top;
	padding_bottom = bottom;
}

glm::vec2 BaseElement::GetBoundingBox()
{
	int w = 0;
	int h = 0;
	w += padding_left + padding_right;
	h += padding_top + padding_bottom;

	return glm::vec2(w, h);
}