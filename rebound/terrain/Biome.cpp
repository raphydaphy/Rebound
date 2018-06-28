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
    unsigned int lastBiomeID = 0;
    unsigned int lastRegionID = 0;
    unsigned int highestOctaveCount = 0;

    std::shared_ptr<Biome> highestBiome;

    std::map<unsigned int, Biome> biomeMap;
    std::map<unsigned int, BiomeRegion> regionMap;
};

BiomeRegion::BiomeRegion(std::string name, float maxHeight, float r, float g, float b) : name{std::move(name)}, maxHeight{maxHeight}, color{glm::vec3(r, g, b)}, id(BiomeData::get().lastRegionID++)
{
    BiomeData::get().regionMap.insert(std::pair<int, BiomeRegion>(this->id, *this));
}

BiomeRegion BiomeRegion::getByID(unsigned int id)
{
    if (BiomeData::get().regionMap.find(id) != BiomeData::get().regionMap.end())
    {
        return BiomeData::get().regionMap.at(id);
    }
    return BiomeData::get().regionMap.at(BiomeData::get().lastRegionID - 1);
}

Biome::Biome(float maxHeightIn, float heightMulIn, float baseHeightIn, unsigned int noiseOctavesIn, float noiseScaleIn,
             float noisePersistanceIn, float noiseLacunarityIn, std::initializer_list<BiomeRegion> regionsIn) :
        maxHeight{maxHeightIn}, heightMultiplier{heightMulIn}, baseHeight{baseHeightIn}, noiseOctaves{noiseOctavesIn},
        noiseScale{noiseScaleIn}, noisePersistance{noisePersistanceIn}, noiseLacunarity{noiseLacunarityIn},
        id(BiomeData::get().lastBiomeID++), regions{std::vector<BiomeRegion>(regionsIn)}
{

    BiomeData::get().biomeMap.insert(std::pair<int, Biome>(id, *this));

    if (BiomeData::get().highestBiome == nullptr || maxHeight > BiomeData::get().highestBiome->maxHeight)
    {
        BiomeData::get().highestBiome = std::make_shared<Biome>(*this);
    }

    if (noiseOctavesIn > BiomeData::get().highestOctaveCount)
    {
        BiomeData::get().highestOctaveCount = noiseOctaves;
    }
}

float Biome::genTerrainDensity(int x, int y, int z, std::vector<glm::vec3> octaveOffsets)
{

    float density = getBaseDensity(x, y, z);
    float halfSize = Terrain::size / 2.0f;

    float amplitude = 2;
    float frequency = 1.5f;

    for (unsigned int octave = 0; octave < noiseOctaves; octave++)
    {
        float sampleX = (x - halfSize + octaveOffsets.at(octave).x) / noiseScale * frequency;
        float sampleY = (y - halfSize + octaveOffsets.at(octave).y) / noiseScale * frequency;
        float sampleZ = (z - halfSize + octaveOffsets.at(octave).z) / noiseScale * frequency;

        float noiseValue = evaulateOctave(sampleX, sampleY, sampleZ);

        density += noiseValue * amplitude;

        amplitude *= noisePersistance;
        frequency *= noiseLacunarity;
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
    baseHeight;
    if (y == 0)
    {
        return baseHeight;
    }
    return -y / 2.0f + baseHeight;
}

bool Biome::operator==(const Biome &rhs)
{
    return id == rhs.id;
}

BiomeRegion Biome::getRegionFromID(unsigned int id)
{
    if (id >= 0 && id < regions.size())
    {
        return regions.at(id);
    }
    return regions.at(regions.size() - 1);
}

BiomeRegion Biome::getRegionFromHeight(float height)
{
    for (BiomeRegion region : regions)
    {
        if (region.maxHeight > height)
        {
            return region;
        }
    }
    return regions.at(BiomeData::get().lastBiomeID - 1);
}

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

    Biome &getByID(unsigned int id)
    {
        if (BiomeData::get().biomeMap.find(id) != BiomeData::get().biomeMap.end())
        {
            return BiomeData::get().biomeMap.at(id);;
        }
        return BiomeData::get().biomeMap.at(BiomeData::get().lastBiomeID - 1);
    }

    Biome &getByHeight(float height)
    {
        for (auto &biome : BiomeData::get().biomeMap)
        {
            if (height < biome.second.maxHeight)
            {
                return biome.second;
            }
        }
        return BiomeData::get().biomeMap.at(BiomeData::get().lastBiomeID - 1);
    }

    void init()
    {
        auto savanna = std::make_unique<Biome>(Biome(30, 1, 10, 12, 250, 0.5f, 2,
                {BiomeRegion("Tall Grass", 30, 179 / 255.0f, 191 / 255.0f, 143 / 255.0f),
                 BiomeRegion("Trees", 13, 138 / 255.0f, 147 / 255.0f, 75 / 255.0f)}));



        auto forest = std::make_unique<Biome>(Biome(80, 2, 10, 10, 250, 0.6f, 2,
                {BiomeRegion("Grass", 45, 0.0431372549f, 0.91764705882f, 0.23921568627f),
                 BiomeRegion("Forest", 80, 0.0431372549f, 0.91764705882f, 0.23921568627f)}));
    }
}