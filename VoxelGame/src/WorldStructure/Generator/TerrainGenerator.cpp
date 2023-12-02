#include "TerrainGenerator.h"

// Singleton instance of TerrainGenerator class (only one instance of TerrainGenerator can exist)
static TerrainGenerator *instance = nullptr;
TerrainGenerator *TerrainGenerator::GetInstance()
{
	if (instance == nullptr)
		instance = new TerrainGenerator();
	return instance;
}



TerrainGenerator::TerrainGenerator()
{
	surfaceNoiseOutput = std::vector<float>();
	fnSurfaceNoise = FastNoise::New<FastNoise::Perlin>();
}

// Generates a chunk surface level of terrain using the FastNoise library
std::vector<std::vector<float>> TerrainGenerator::GenerateChunkSurface(int xStart, int yStart, int xSize, int ySize, int seed)
{
	// Clear the surface noise output vector and set it to the correct size
	surfaceNoiseOutput.clear();
	surfaceNoiseOutput = std::vector<float>(xSize * ySize);
	int terrainLowest = 0;
	int terrainHighest = 30;

	// Clear the chunk surface vector and initialises it to 2D vector
	chunkSurface.clear();
	chunkSurface = std::vector<std::vector<float>>(0);

	// Generate the surface noise using the FastNoise library
	fnSurfaceNoise->GenUniformGrid2D(surfaceNoiseOutput.data(), xStart, yStart, xSize, ySize, 0.01f, seed);

	// Loop through the surface noise output and add the values to the chunk surface 2D vector
	for (int x = 0; x < xSize; x++)
	{
		std::vector<float> row;
		for (int y = 0; y < ySize; y++)
		{
			//sets block height to be between height and lowest from 0-1
			//row id * rows size + collumn element index
			float blockHeight = ((surfaceNoiseOutput[x * xSize + y] * (terrainHighest - terrainLowest))) + terrainLowest;
			row.push_back(blockHeight);
		}
		chunkSurface.push_back(row);
	}
	// Return the chunk surface hightmap 2D vector
	return chunkSurface;
}

TerrainGenerator::~TerrainGenerator()
{}
