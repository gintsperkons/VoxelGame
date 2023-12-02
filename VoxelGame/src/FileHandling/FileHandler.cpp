#include "FileHandler.h"
#include <fstream>
#include <filesystem>

// the name of the game
std::string FileHandler::gameName = "voxelGame";

// creates a directory at a given location and returns true if successful
bool FileHandler::Create_directories(std::string directory)
{
	return std::filesystem::create_directories(directory);
}

// checks if a given location is a directory
bool FileHandler::IsDirectory(std::string  directory)
{
	return std::filesystem::is_directory(directory);
}

// checks if a directory exists
bool FileHandler::Exists(std::string  directory)
{
	return std::filesystem::exists(directory);
}

// checks if a given file exists
bool FileHandler::FileExists(const std::string fileLocation)
{
	return std::filesystem::exists(fileLocation);
}

// returns the directory where the game is stored
std::string FileHandler::GetGameDirectory()
{
	char *pvalue;
	size_t len = 500;
	_dupenv_s(&pvalue, &len, "appdata");
	Create_directories(std::string(pvalue) + "\\." + gameName);
	return std::string(pvalue) + "\\." + gameName;

}

// returns a vector of all the files in a given directory
std::vector<std::string> FileHandler::GetFilesInDirectory(std::string directory)
{
	std::vector<std::string> files;
	for (const auto &entry : std::filesystem::directory_iterator(directory))
		files.push_back(entry.path().string());
	return files;
}

// reads a file from a given location and return the contents as a string
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
