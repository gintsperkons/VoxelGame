#include "FileHandler.h"
#include <fstream>
#include <iostream>
#include <filesystem>


std::string FileHandler::gameName = "voxelGame";

std::string FileHandler::GetGameDirectory()
{
	char *pvalue;
	size_t len = 500;
	_dupenv_s(&pvalue, &len, "appdata");
	Create_directories(std::string(pvalue)+"\\."+gameName);
	return std::string(pvalue) + "\\." + gameName;

}


bool FileHandler::FileExists(const std::string fileLocation)
{
	return std::filesystem::exists(fileLocation);
}

bool FileHandler::IsDirectory(std::string  directory)
{
	return std::filesystem::is_directory(directory);
}


bool FileHandler::Exists(std::string  directory)
{
	return std::filesystem::exists(directory);
}

bool FileHandler::Create_directories(std::string directory)
{
	return std::filesystem::create_directories(directory);
}

std::vector<std::string> FileHandler::GetFilesInDirectory(std::string directory)
{
	std::vector<std::string> files;
	for (const auto &entry : std::filesystem::directory_iterator(directory))
		files.push_back(entry.path().string());
	return files;
}


std::string FileHandler::ReadFile(std::string  fileLocation)
{
	std::string content;
	std::ifstream fileStream(fileLocation, std::ios::in);

	if (!fileStream.is_open())
	{
		printf("Failed to read %s! File doesn't exist.", fileLocation.c_str());
		return "";
	}

	std::string line = "";
	while (!fileStream.eof())
	{
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}
