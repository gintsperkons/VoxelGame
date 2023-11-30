#include "Line.h"
#include <GLAD/glad.h>
#include "../ShaderManager.h"




Line::Line(glm::vec3 start, glm::vec3 end, glm::vec3 color)
{
	this->startPoint = start;
	this->endPoint = end;
	this->color = color;

	vertices = {
		 start.x, start.y, start.z,
		 end.x, end.y, end.z,
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void Line::Render()
{
	ShaderManager::GetInstance()->SetUniform3("color", &color);
	glm::mat4 model(1.0f);
	ShaderManager::GetInstance()->SetMat4("model", &model);
	glBindVertexArray(VAO);
	glDrawArrays(GL_LINES, 0, 2);
	glBindVertexArray(0);
}



void Line::Clear()
{
	if (VAO != 0)
		glDeleteVertexArrays(1, &VAO);
	if (VBO != 0)
		glDeleteBuffers(1, &VBO);
}

Line::~Line()
{
	Clear();
}
