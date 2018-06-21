#include "Terrain.hpp"

#define MAX_VERTS_PER_MESH = 30000;

TerrainVoxel::TerrainVoxel(float density, Biome *biome, float biomeEdge)
{
    this->density = density;
    this->biome = biome;
    this->biomeEdge = biomeEdge;
}



std::vector<ColoredModelData> Terrain::generateModelData()
{/*
    glm::vec3 offset(this->x, this->y, this->z);

    if (voxels == nullptr)
    {
        voxels = new std::vector<TerrainVoxel>(size * size * size);

        const int biomeOctaves = 5;

        std::vector<glm::vec3> terrainOffsets = generateTerrainOffsets(BiomeRegistry.getHighestOctaveCount(), offset);
        std::vector<glm::vec2> biomeOffsets = generateBiomeOffsets(biomeOctaves, offset);

        for (int x = 0; x < size; x++)
        {
            for (int y = 0; y < size; y++)
            {
                for (int z = 0; z < size; z++)
                {

                    float biomeDensity = ((genBiomeDensity(x, z, biomeOctaves, 500, 0.5f, 2f, biomeOffsets) + 1) / 2f) * 100f;

                    Biome *lowerBiome = BiomeRegistry.getByHeight(biomeDensity);
                    Biome *higherBiome = BiomeRegistry.getByID(lowerBiome->getID() + 1);

                    float terrainDensityLower = lowerBiome->genTerrainDensity(x, (int)this->y + y, z, lowerBiome->noiseOctaves, lowerBiome->noiseScale, lowerBiome->noisePersistance, lowerBiome->noiseLacunarity, lowerBiome->baseHeight, terrainOffsets) * lowerBiome->heightMultiplier;
                    float terrainDensityHigher = higherBiome->genTerrainDensity(x, (int)this->y + y, z, higherBiome->noiseOctaves, higherBiome->noiseScale, higherBiome->noisePersistance, higherBiome->noiseLacunarity, higherBiome->baseHeight, terrainOffsets) * higherBiome->heightMultiplier;

                    float alpha = std::abs((float) std::clamp((lowerBiome->maxHeight - biomeDensity) / 16f, 0f, 1f) - 1);
                    float interpolatedDensity = core::lerp(terrainDensityLower, terrainDensityHigher, alpha);

                    voxels->at(x + y * size + z * size * size) = TerrainVoxel(interpolatedDensity, lowerBiome, alpha);
                }
            }
        }
    }
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec3> colors;


    MarchingCubesGenerator generator = new MarchingCubesGenerator();

    // triangles should have SIZE - 1 ^ 3 entries in it, one for every voxel except the last x, y and z rows
    triangles = new HashMap<>();
    generator.generateMesh(voxels, size, size, size, (int)this.y, vertices, normals, colors, triangles);

    int numMeshes = vertices.size() / MAX_VERTS_PER_MESH + 1;

    List<TerrainMeshData> models = new ArrayList<>();

    for (int mesh = 0; mesh < numMeshes; mesh++)
    {
        List<Vector3f> splitVertices = new ArrayList<>();
        List<Vector3f> splitNormals = new ArrayList<>();
        List<Vector3f> splitColors = new ArrayList<>();
        List<Integer> splitIndices = new ArrayList<>();

        for (int vertex = 0; vertex < MAX_VERTS_PER_MESH; vertex++)
        {
            int index = mesh * MAX_VERTS_PER_MESH + vertex;

            if (index < vertices.size())
            {
                splitVertices.add(vertices.get(index));
                splitNormals.add(normals.get(index));
                splitColors.add(colors.get(index));
                splitIndices.add(indices.get(index));
            }
        }

        if (splitVertices.size() == 0)
        {
            continue;
        }

        float[] splitVerticesArray = new float[splitVertices.size() * 3];
        float[] splitNormalsArray = new float[splitNormals.size() * 3];
        float[] splitColorsArray = new float[splitColors.size() * 3];
        int[] splitIndicesArray = new int[splitIndices.size()];

        for (int index = 0; index < splitIndices.size(); index++)
        {
            splitVerticesArray[index * 3] = splitVertices.get(index).x;
            splitVerticesArray[index * 3 + 1] = splitVertices.get(index).y;
            splitVerticesArray[index * 3 + 2] = splitVertices.get(index).z;

            splitNormalsArray[index * 3] = splitNormals.get(index).x;
            splitNormalsArray[index * 3 + 1] = splitNormals.get(index).y;
            splitNormalsArray[index * 3 + 2] = splitNormals.get(index).z;

            splitColorsArray[index * 3] = splitColors.get(index).x;
            splitColorsArray[index * 3 + 1] = splitColors.get(index).y;
            splitColorsArray[index * 3 + 2] = splitColors.get(index).z;

            splitIndicesArray[index] = indices.get(index);
        }
        if (models.size() < mesh)
        {
            //models.get(mesh).updateTerrain(splitVerticesArray, splitNormalsArray, splitColorsArray, splitIndicesArray, loader);
        } else
        {
            models.add(new TerrainMeshData(splitVerticesArray, splitNormalsArray, splitColorsArray, splitIndicesArray));
        }
    }

    return models;*/
}

float Terrain::genBiomeDensity(int x, int z, int octaves, float scale, float persistance, float lacunarity,
                               std::vector<glm::vec2> octaveOffsets)
{
    float density = 0;
    float halfSize = size / 2;

    float frequency = 1;
    float amplitude = 1;

    for (int octave = 0; octave < octaves; octave++)
    {
        float sampleX = (x - halfSize + octaveOffsets[octave].x) / scale * frequency;
        float sampleZ = (z - halfSize + octaveOffsets[octave].y) / scale * frequency;
        //TODO: this line
        //float noiseValue = (float) core::getNoise().Evaluate(sampleX, sampleZ);
        float noiseValue = 1;
        density += noiseValue * amplitude;

        amplitude *= persistance;
        frequency *= lacunarity;
    }

    return density;
}
