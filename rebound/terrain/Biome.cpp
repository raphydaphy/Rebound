#include "Biome.hpp"
#include "Terrain.hpp"

class BiomeData
{
public:
    static BiomeData &get()
    {
        static BiomeData data;
        return data;
    }
private:
    BiomeData() = default;
public:
    int lastBiomeID = 0;
    int lastRegionID = 0;
    int highestOctaveCount = 0;

    std::shared_ptr<Biome> highestBiome;

    std::map<int, Biome> biomeMap;
    std::map<int, BiomeRegion> regionMap;
};

BiomeRegion::BiomeRegion(std::string name, float maxHeight, float r, float g, float b)
{
    this->name = std::move(name);
    this->maxHeight = maxHeight;
    this->color = glm::vec3(r, g, b);

    this->id = BiomeData::get().lastRegionID++;

    BiomeData::get().regionMap.insert(std::pair<int, BiomeRegion>(this->id, *this));
}

BiomeRegion BiomeRegion::getByID(int id)
{
    if (BiomeData::get().regionMap.find(id) != BiomeData::get().regionMap.end())
    {
        return BiomeData::get().regionMap.at(id);
    }
}

Biome::Biome(float maxHeight, float heightMultiplier, float baseHeight, int noiseOctaves, float noiseScale,
             float noisePersistance, float noiseLacunarity, std::initializer_list<BiomeRegion> regions)
{
    this->maxHeight = maxHeight;
    this->heightMultiplier = heightMultiplier;
    this->baseHeight = baseHeight;
    this->noiseOctaves = noiseOctaves;
    this->noiseScale = noiseScale;
    this->noisePersistance = noisePersistance;
    this->noiseLacunarity = noiseLacunarity;

    this->regions = std::vector<BiomeRegion>(regions);

    this->id = (BiomeData::get().lastBiomeID)++;

    BiomeData::get().biomeMap.insert(std::pair<int, Biome>(this->id, *this));

    if (BiomeData::get().highestBiome == nullptr || this->maxHeight > BiomeData::get().highestBiome->maxHeight)
    {
        BiomeData::get().highestBiome = std::make_shared<Biome>(*this);
    }

    if (this->noiseOctaves > BiomeData::get().highestOctaveCount)
    {
        BiomeData::get().highestOctaveCount = this->noiseOctaves;
    }
}

int Biome::getID()
{
    return this->id;
}

float Biome::genTerrainDensity(int x, int y, int z, int octaves, float scale, float persistance, float lacunarity,
                               float baseHeight, std::vector<glm::vec3> octaveOffsets)
{
    float density = getBaseDensity(x, y, z);
    float halfSize = Terrain::size / 2.0f;

    float amplitude = 2;
    float frequency = 1.5f;

    for (int octave = 0; octave < octaves; octave++)
    {
        float sampleX = (x - halfSize + octaveOffsets[octave].x) / scale * frequency;
        float sampleY = (y - halfSize + octaveOffsets[octave].y) / scale * frequency;
        float sampleZ = (z - halfSize + octaveOffsets[octave].z) / scale * frequency;

        float noiseValue = evaulateOctave(sampleX, sampleY, sampleZ);

        density += noiseValue * amplitude;

        amplitude *= persistance;
        frequency *= lacunarity;
    }

    return evaulateNoise(x, y, z, density, halfSize);
}

float Biome::evaulateOctave(float sampleX, float sampleY, float sampleZ)
{
    return core::simplex(sampleX, sampleY, sampleZ) * 2 - 1;
}

float Biome::evaulateNoise(int x, int y, int z, float density, float halfSize)
{
    return density * halfSize;
}

float Biome::getBaseDensity(int x, int y, int z)
{
    return -y / 2.0f + baseHeight;
}

bool Biome::operator==(const Biome &rhs)
{
    return id == rhs.id;
}

ForestBiome::ForestBiome() : Biome(80, 2, 10, 10, 250, 0.6f, 2,
                                   {BiomeRegion("Grass", 10, 0.0431372549f, 0.91764705882f, 0.23921568627f),
                                    BiomeRegion("Forest", 13, 0.0431372549f, 0.91764705882f, 0.23921568627f)})
{ }

DesertBiome::DesertBiome() : Biome(20, 1, 10, 12, 250, 0.5f, 2,
                                   {BiomeRegion("Sand", 10, 210 / 256.0f, 219 / 256.0f, 111 / 256.0f)})
{ }

namespace biomes
{
    std::shared_ptr<Biome> getHighestBiome()
    {
        return BiomeData::get().highestBiome;
    }

    int getHighestOctaveCount()
    {
        return BiomeData::get().highestOctaveCount;
    }

    Biome getByID(int id)
    {
        if (BiomeData::get().biomeMap.find(id) != BiomeData::get().biomeMap.end())
        {
            return BiomeData::get().biomeMap.at(id);
        }
    }

    Biome getByHeight(float height)
    {
        for (auto biome : BiomeData::get().biomeMap)
        {
            if (height < biome.second.maxHeight)
            {
                return biome.second;
            }
        }
    }

    void init()
    {
        auto forest = std::make_unique<ForestBiome>(ForestBiome());
        auto desert = std::make_unique<DesertBiome>(DesertBiome());
    }
}