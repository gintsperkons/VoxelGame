#pragma once
#include <string>
#include <map>
#include <GLM/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"

class Shader;

class ShaderManager
{
private:
	std::string shaderPath;
	Shader* currentShader;
	std::string getShaderName(std::string vertexFileName, std::string FragmentFileName);

public:
	std::map<std::string, Shader*> shaderList;

	ShaderManager();

	void CreateFromFiles(const char *vertexLocation, const char *fragmentLocation);

	void UseShader(std::string shaderName);
	void SetMat4(std::string type, glm::mat4 *matrix);
	void SetUniform3(std::string type, glm::vec3 *vector);
	void SetUniform1(std::string type, float value);
	bool uniformExists(std::string uniformName);
	void ClearShaderList();
	~ShaderManager();





	static ShaderManager *GetInstance();

	private:
		//Base shader for if no file found
	// Vertex Shader
		



};



