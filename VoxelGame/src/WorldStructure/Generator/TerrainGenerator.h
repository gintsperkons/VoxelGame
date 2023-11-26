#pragma once
#include <FastNoise/FastNoise.h>

class TerrainGenerator
{
	std::vector<float> surfaceNoiseOutput;
	FastNoise::SmartNode<FastNoise::Perlin> fnSurfaceNoise;
	std::vector<std::vector<float>> chunkSurface;

public:
	TerrainGenerator();

	std::vector <std::vector <float>> GenerateChunkSurface(int xStart, int yStart, int xSize, int ySize, int seed);

	~TerrainGenerator();

	static TerrainGenerator* GetInstance();
};

