#pragma once
#include <string>
#include <vector>

class FileHandler
{
	static std::string gameName;
public:
	static bool Create_directories(std::string directory);
	static bool IsDirectory(std::string directory);
	static bool Exists(std::string directory);
	static bool FileExists(std::string fileLocation);
	static std::string GetGameDirectory();
	static std::vector<std::string> GetFilesInDirectory(std::string fileLocation);
	static std::string ReadFile(std::string fileLocation);

};

