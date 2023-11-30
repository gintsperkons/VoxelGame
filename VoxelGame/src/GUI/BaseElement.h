#pragma once
#include <GLM/glm.hpp>
#include <string>
#include <vector>

class BaseElement
{

protected:
	std::vector<BaseElement *> allChildren;

	std::string elementName;
	int type;
	glm::vec2 location;
	float padding_left;
	float padding_right;
	float padding_top;
	float padding_bottom;


	int verticalAlignment;
	int horizontalAlignment;

	
public:
	float space_left = 0;
	float space_right = 0;
	float space_top = 0;
	float space_bottom = 0;
	BaseElement(std::string name, int type);
	~BaseElement();
	
	enum Align
	{
		Top = 0,
		Bottom = 1,
		Left = 2,
		Right = 3,
		Center = 4,
		None = 5
	};

	void SetLocation(float x, float y);
	void SetPositionRelative(float x, float y);//0 - 1 in procentage
	void GetPadding(float &left, float &right, float &top, float &bottom);
	void SetPadding(float left, float right, float top, float bottom);
	virtual void Render() = 0;
	virtual void Clear() = 0;
	int GetType();
	virtual glm::vec2 GetBoundingBox();
	BaseElement* GetChild(std::string name);
	std::string GetName();

	
	enum ElementType
	{
		GUI_Manager = 0,
		TextObj = 1,
		VLayout = 2
	};


};

