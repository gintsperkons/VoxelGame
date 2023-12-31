#pragma once
#include "BaseElement.h"
#include <string>

class VerticalLayout: public BaseElement
{

public:
	VerticalLayout(std::string name);
	~VerticalLayout();

	void AddElement(BaseElement *element);
	void Render();
	void Clear();

};

