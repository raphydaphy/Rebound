#ifndef BIOME_H
#define BIOME_H

class Biome
{
public:
    Biome(float maxHeight, float heightMultiplier, float baseHeight, int noiseOctaves, float noiseScale, float noisePersistance, float noiseLacunarity);
    int getID();
private:
    private int id;

    float maxHeight;
    float heightMultiplier;
    float baseHeight;

    int noiseOctaves;
    float noiseScale;
    float noisePersistance;
    float noiseLacunarity;
};

#endif