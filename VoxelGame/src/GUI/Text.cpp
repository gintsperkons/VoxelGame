#include <iostream>

#include <GLAD/glad.h>  

#include "../WindowManager.h"
#include "../ShaderManager.h"
#include "Text.h"

// Returns the projection matrix required for the text to be rendered on the screen
glm::mat4 Text::GetProjectionMatrics()
{
	float width = WindowManager::GetInstance()->getBufferWidth();
	float height = WindowManager::GetInstance()->getBufferHeight();
	return glm::ortho(0.0f, width, 0.0f, height);
}

Text::Text(std::string name) :VAO(0), VBO(0),
face(nullptr), library(nullptr),
color(1.0f, 1.0f, 1.0f),
scale(1.0f),
text("Text Holder"), BaseElement(name, ElementType::TextObj)
{
	//init freetype
	FT_Library library;
	if (FT_Init_FreeType(&library))
	{
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
	}

	// load font as face
	if (FT_New_Face(library, "fonts/arial.ttf", 0, &face))
	{
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
	}

	// set size to load glyphs as
	FT_Set_Pixel_Sizes(face, 0, 12);

}

//Initializes the text object by loading the font and creating the VAO and VBO
void Text::Init()
{
	for (unsigned char c = 0; c < 128; c++)
	{
		// load character glyph 
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}
		// generate texture
		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);
		// set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// store character for later use
		Character character = {
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};
		Characters.insert(std::pair<char, Character>(c, character));
	}
	// configure VAO/VBO for texture quads
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// releases FreeType resources
	FT_Done_Face(face);
	FT_Done_FreeType(library);
}

//Renders the text on the screen
void Text::Render()
{
	// disable face culling (one side rendering) and depth mask
	bool faceCullEnabled = glIsEnabled(GL_CULL_FACE);
	glDepthMask(GL_FALSE);
	glDisable(GL_CULL_FACE);

	// activate corresponding render state	
	glm::mat4 projection = GetProjectionMatrics();
	//gets the shader and sets the projection matrix and the color
	ShaderManager::GetInstance()->UseShader("text");
	ShaderManager::GetInstance()->SetMat4("projection", &projection);
	ShaderManager::GetInstance()->SetUniform3("textColor", &color);

	//activates the texture
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);

	// get the width and height of the window drawable area
	float width = WindowManager::GetInstance()->getBufferWidth();
	float height = WindowManager::GetInstance()->getBufferHeight();

	//get the bounding box of the text element
	glm::vec2 bbox = GetBoundingBox();

	int x = 0;
	int y = 0;

	//calculate the x and y position of the text based on the alignment and add the padding
	//vertical alignment calculation
	if (verticalAlignment == Align::None)
		y = location.y;
	if (verticalAlignment == Align::Top)
	{
		y = height - bbox.y + padding_top;
		y -= space_top;
	}
	if (verticalAlignment == Align::Center)
		y = width - (bbox.y / 2);
	if (verticalAlignment == Align::Bottom)
	{
		y = padding_bottom;
		y += space_bottom;
	}

	//horizontal alignment calculation
	if (horizontalAlignment == Align::None)
		x = location.x;
	if (horizontalAlignment == Align::Left)
	{
		x = padding_left;
		x += space_left;
	}
	if (horizontalAlignment == Align::Center)
		x = width - (bbox.x / 2);
	if (horizontalAlignment == Align::Right)
	{
		x = width - bbox.x + padding_right;
		x -= space_right;
	}

	// iterate through all characters of text
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = Characters[*c];

		//calculate the x and y position of the character in the text
		float xpos = x + ch.Bearing.x * scale;
		float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

		//calculate the width and height of the character based on the scale
		float w = ch.Size.x * scale;
		float h = ch.Size.y * scale;

		// update VBO for each character
		float vertices[6][4] = {
			{ xpos,     ypos + h,   0.0f, 0.0f },
			{ xpos,     ypos,       0.0f, 1.0f },
			{ xpos + w, ypos,       1.0f, 1.0f },

			{ xpos,     ypos + h,   0.0f, 0.0f },
			{ xpos + w, ypos,       1.0f, 1.0f },
			{ xpos + w, ypos + h,   1.0f, 0.0f }
		};

		// render char texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);

		// update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
	}

	//unbind the VAO and the texture
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);

	//reactivate the face culling and depth mask if needed
	if (faceCullEnabled)
		glEnable(GL_CULL_FACE);
	glDepthMask(GL_TRUE);
}

//Returns the bounding box of the text element
glm::vec2 Text::GetBoundingBox()
{
	int w = 0;
	int h = 0;

	// iterate through all characters of text and gets biggest height and total width 
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = Characters[*c];
		if (ch.Size.y > h)
			h = ch.Size.y * scale;
		w += (ch.Advance >> 6) * scale;

	}

	//add the padding to the width and height
	w += padding_left + padding_right;
	h += padding_top + padding_bottom;

	return glm::vec2(w, h);
}

//Clears the VAO and VBO 
void Text::Clear()
{
	if (VAO != 0)
		glDeleteVertexArrays(1, &VAO);
	if (VBO != 0)
		glDeleteBuffers(1, &VBO);
}

//Sets the text to be rendered
void Text::SetText(std::string text)
{
	this->text = text;
}

//Sets the color of the text
void Text::SetColor(glm::vec3 color)
{
	this->color = color;
}

//Sets the scale of the text
void Text::SetScale(float scale)
{
	this->scale = scale;
}

Text::~Text()
{
	Clear();
}
