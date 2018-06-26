#include "Terrain.hpp"
#include "marching.hpp"
#include "../../engine/lib/OpenSimplexNoise.hpp"
static constexpr int MAX_VERTS_PER_MESH = 30000;

OpenSimplexNoise noise(3);

TerrainVoxel::TerrainVoxel(float density, Biome *biome, float biomeEdge)
{
    this->density = density;
    this->biome = biome;
    this->biomeEdge = biomeEdge;
}

std::vector<glm::vec3> genTerrainOffsets(unsigned int octaves, glm::vec3 offset)
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

float getDensity(int x, int y, int z, unsigned int octaves, float scale, float persitance, float lacunarity, std::vector<glm::vec3> offsets)
{
    float density = -y / 2.0f + 6;
    float halfSize = Terrain::size / 2.0f;
    float amplitude = 1;
    float frequency = 1;

    for (unsigned int octave = 0; octave < octaves; octave++)
    {
        double sampleX = (x - halfSize + offsets[octave].x) / scale * frequency;
        double sampleY = (y - halfSize + offsets[octave].y) / scale * frequency;
        double sampleZ = (z - halfSize + offsets[octave].z) / scale * frequency;

        float noiseValue = (float)noise.Evaluate(sampleX, sampleY, sampleZ) * 2 - 1;

        density += noiseValue * amplitude;

        amplitude *= persitance;
        frequency *= lacunarity;
    }

    return density * halfSize;
}

std::vector<IndexedModelData> Terrain::generateModelData()
{
    glm::vec3 offset(this->x, this->y, this->z);

    if (voxels.empty())
    {
        voxels = std::vector<float>(size * size * size);
        const int biomeOctaves = 5;

        const unsigned int octaves = 8;

        std::vector<glm::vec3> offsets = genTerrainOffsets(octaves, offset);

        for (unsigned int x = 0; x < size; x++)
        {
            for (unsigned int y = 0; y < size; y++)
            {
                for (unsigned int z = 0; z < size; z++)
                {
                    float density = getDensity(x, y, z, octaves, 50, 0.6f, 2.01f, offsets);

                    voxels.at(x + y * size + z * size * size) = density;
                }
            }
        }
    }

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<unsigned int> indices;

    marching::generateMesh(voxels, size - 1, size - 1, size - 1, &vertices, &normals, &indices);

    std::vector<IndexedModelData> models;

    models.emplace_back(vertices, normals, indices);

    return models;
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
    for (const IndexedModelData &mesh : unprepared)
    {
        models.emplace_back(mesh);
    }
}
