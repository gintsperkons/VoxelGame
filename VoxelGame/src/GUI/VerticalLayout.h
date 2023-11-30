#pragma once
#include "BaseElement.h"
#include <vector>
#include <string>

class VerticalLayout: public BaseElement
{
	std::vector<BaseElement*> elements;

public:
	VerticalLayout(std::string name);
	~VerticalLayout();

	void AddElement(BaseElement *element);
	void Render();
	void Clear();

};
