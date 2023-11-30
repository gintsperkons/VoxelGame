#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

#include<GLM/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>
#include <string>

#include "BaseElement.h"

class Text: public BaseElement
{
	FT_Library  library;
	FT_Face face;
	unsigned int VAO, VBO;


	struct Character
	{
		unsigned int TextureID;  // ID handle of the glyph texture
		glm::ivec2   Size;       // Size of glyph
		glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
		unsigned int Advance;    // Offset to advance to next glyph
	};

	std::map<char, Character> Characters;
	glm::mat4 GetProjectionMatrics();





	


	float scale = 1.0f;
	glm::vec3 color;
	std::string text;

public:
	glm::vec2 GetBoundingBox();
	Text(std::string name);
	void Init();
	void Render();

	void SetText(std::string text);
	void SetColor(glm::vec3 color);
	void SetScale(float scale);

	~Text();




	
	void Clear();

};

