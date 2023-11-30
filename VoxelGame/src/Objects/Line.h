#pragma once
#include <vector>
#include <GLM/glm.hpp>



class Line
{
	unsigned int VBO, VAO;
	std::vector<float> vertices;
	glm::vec3 startPoint;
	glm::vec3 endPoint;
	glm::vec3 color;
public:
	Line(glm::vec3 start, glm::vec3 end, glm::vec3 color);
	

	

	void Render();

	void Clear();
	


	~Line();
	
};


