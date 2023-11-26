#include "TerrainGenerator.h"
#include <iostream>

static TerrainGenerator* instance = nullptr;
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

std::vector<std::vector<float>> TerrainGenerator::GenerateChunkSurface(int xStart, int yStart, int xSize, int ySize, int seed)
{
	surfaceNoiseOutput.clear();
	surfaceNoiseOutput = std::vector<float>(xSize * ySize);
	int terrainLowest = 0;
	int terrainHighest = 30;

	chunkSurface.clear();
	chunkSurface = std::vector<std::vector<float>>(0);


	std ::cout << "xStart: " << xStart << std::endl;
	std::cout << "yStart: " << yStart << std::endl;
	std::cout << "seed: " << seed << std::endl;


	fnSurfaceNoise->GenUniformGrid2D(surfaceNoiseOutput.data(), xStart, yStart, xSize, ySize, 0.01f,seed);



	for (int x = 0; x < xSize; x++)
	{
		std::vector<float> row;
		for (int y = 0; y < ySize; y++)
		{
			float blockHeight = (( surfaceNoiseOutput[x *xSize + y] * (terrainHighest-terrainLowest)))+terrainLowest;
			row.push_back(blockHeight);

		}
		chunkSurface.push_back(row);
	}

	


	return chunkSurface;
}

TerrainGenerator::~TerrainGenerator()
{}
