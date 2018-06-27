#include "Terrain.hpp"
#include <utility>
#include "marching.hpp"

static constexpr unsigned int MAX_VERTS_PER_MESH = 30000;

TerrainVoxel::TerrainVoxel(float density, Biome biome, float biomeEdge) : biome{std::move(biome)}, density{density}, biomeEdge{biomeEdge}
{ }

std::vector<glm::vec3> genTerrainOffsets(int octaves, glm::vec3 offset)
{
    std::vector<glm::vec3> terrainOffsets;

    for (int octave = 0; octave < octaves; octave++)
    {
        float offX = core::randomInt(-10000, 10000) + offset.x;
        float offY = core::randomInt(-10000, 10000) + offset.y;
        float offZ = core::randomInt(-10000, 10000) + offset.z;

        terrainOffsets.emplace_back(offX, offY, offZ);
    }

    return terrainOffsets;
}

std::vector<glm::vec2> genBiomeOffsets(int octaves, glm::vec3 offset)
{
    std::vector<glm::vec2> biomeOffsets;

    for (int octave = 0; octave < octaves; octave++)
    {
        float offX = core::randomInt(-10000, 10000) + offset.x;
        float offY = core::randomInt(-10000, 10000) + offset.y;

        biomeOffsets.emplace_back(offX, offY);
    }

    return biomeOffsets;
}

float getDensity(int x, int y, int z, unsigned int octaves, float scale, float persistance, float lacunarity, std::vector<glm::vec3> offsets)
{
    float density = -y / 2.0f + 6;
    float halfSize = Terrain::size / 2.0f;
    float amplitude = 1;
    float frequency = 1;

    for (unsigned int octave = 0; octave < octaves; octave++)
    {
        float sampleX = (x - halfSize + offsets.at(octave).x) / scale * frequency;
        float sampleY = (y - halfSize + offsets.at(octave).y) / scale * frequency;
        float sampleZ = (z - halfSize + offsets.at(octave).z) / scale * frequency;

        float noiseValue = core::simplex(sampleX, sampleY, sampleZ) * 2 - 1;

        density += noiseValue * amplitude;

        amplitude *= persistance;
        frequency *= lacunarity;
    }

    return density;
}

std::vector<ColoredModelData> Terrain::generateModelData()
{
    glm::vec3 offset(this->x, this->y, this->z);

    if (voxels.empty())
    {
        std::vector<TerrainVoxel*> tmpVoxels(size * size * size);
        const int biomeOctaves = 5;


        std::vector<glm::vec3> terrainOffsets = genTerrainOffsets(biomes::getHighestOctaveCount(), offset);
        std::vector<glm::vec2> biomeOffsets = genBiomeOffsets(biomeOctaves, offset);

        for (unsigned int x = 0; x < size; x++)
        {
            for (unsigned int y = 0; y < size; y++)
            {
                for (unsigned int z = 0; z < size; z++)
                {

                    //float biomeDensity = getDensity(x, y, z, /* octaves */ 8, /* scale */ 50, /* persitance */ 0.6f, /* lacunarity */ 2.01f, terrainOffsets);
                    float biomeDensity = ((genBiomeDensity(x, z, biomeOctaves, 500, 0.5f, 2, biomeOffsets) + 1) / 2.0f) * 100;

                    Biome lowerBiome = biomes::getByHeight(biomeDensity);
                    Biome higherBiome = biomes::getByID(lowerBiome.id + 1);

                    float terrainDensityLower = lowerBiome.genTerrainDensity(x, (int) this->y + y, z, terrainOffsets) * lowerBiome.heightMultiplier;
                    float terrainDensityHigher = higherBiome.genTerrainDensity(x, (int) this->y + y, z, terrainOffsets) * higherBiome.heightMultiplier;

                    float alpha = std::abs(core::clamp((lowerBiome.maxHeight - biomeDensity) / 16.0f, 0, 1) - 1);
                    float interpolatedDensity = core::lerp(terrainDensityLower, terrainDensityHigher, alpha);

                    tmpVoxels.at(x + z * size + y * size * size) = new TerrainVoxel(interpolatedDensity, lowerBiome, alpha);
                }
            }
        }
        for (auto &tmpVoxel : tmpVoxels)
        {
            voxels.push_back(*tmpVoxel);
        }
    }
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec3> colors;

    // triangles should have SIZE - 1 ^ 3 entries in it, one for every voxel except the last x, y and z rows
    std::map<glm::vec3, std::vector<glm::vec3>> triangles;
    marching::generateMesh(voxels, size - 1, size - 1, size - 1, (int)this->y, &vertices, &normals, &colors, &triangles);

    int numMeshes = vertices.size() / MAX_VERTS_PER_MESH + 1;

    std::vector<ColoredModelData> models;

    for (unsigned int mesh = 0; mesh < numMeshes; mesh++)
    {
        std::vector<glm::vec3> splitVertices;
        std::vector<glm::vec3> splitNormals;
        std::vector<glm::vec3> splitColors;

        for (unsigned int vertex = 0; vertex < MAX_VERTS_PER_MESH; vertex++)
        {
            unsigned int index = mesh * MAX_VERTS_PER_MESH + vertex;

            if (index < vertices.size())
            {
                splitVertices.push_back(vertices.at(index));
                splitNormals.push_back(normals.at(index));
                splitColors.push_back(colors.at(index));
            }
        }

        if (splitVertices.empty())
        {
            continue;
        }

        models.emplace_back(splitVertices, splitNormals, splitColors);

    }


    return models;
}

float Terrain::genBiomeDensity(int x, int z, int octaves, float scale, float persistance, float lacunarity,
                               std::vector<glm::vec2> octaveOffsets)
{
    float density = 0;
    float halfSize = size / 2.0f;

    float frequency = 1;
    float amplitude = 1;

    for (unsigned int octave = 0; octave < octaves; octave++)
    {
        float sampleX = (x - halfSize + octaveOffsets.at(octave).x) / scale * frequency;
        float sampleZ = (z - halfSize + octaveOffsets.at(octave).y) / scale * frequency;
        float noiseValue = core::simplex(sampleX, sampleZ);
        density += noiseValue * amplitude;

        amplitude *= persistance;
        frequency *= lacunarity;
    }

    return density;
}

Terrain::Terrain(int gridX, int gridY, int gridZ)
{
    this->x = gridX * (size - 1);
    this->y = gridY * (size - 1);
    this->z = gridZ * (size - 1);

    // TODO: use a thread for this
    unprepared = std::move(generateModelData());

    // TODO: do this after the thread is done
    for (const ColoredModelData &mesh : unprepared)
    {
        models.emplace_back(mesh);
    }
}
