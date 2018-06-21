#include "Terrain.hpp"

#define MAX_VERTS_PER_MESH = 30000;

TerrainVoxel::TerrainVoxel(float density, Biome *biome, float biomeEdge)
{
    this->density = density;
    this->biome = biome;
    this->biomeEdge = biomeEdge;
}

std::vector<ColoredModelData> Terrain::generateModelData()
{
    glm::vec3 offset(x, y, z);
/*
    if (voxels == null)
    {
        voxels = new TerrainVoxel[SIZE * SIZE * SIZE];

        final int biomeOctaves = 5;

        Vector3f[] terrainOffsets = generateTerrainOffsets(BiomeRegistry.getHighestOctaveCount(), offset);
        Vector2f[] biomeOffsets = generateBiomeOffsets(biomeOctaves, offset);

        for (int x = 0; x < SIZE; x++)
        {
            for (int y = 0; y < SIZE; y++)
            {
                for (int z = 0; z < SIZE; z++)
                {

                    float biomeDensity = ((genBiomeDensity(x, z, biomeOctaves, 500, 0.5f, 2f, biomeOffsets) + 1) / 2f) * 100f;

                    Biome lowerBiome = BiomeRegistry.getByHeight(biomeDensity);
                    Biome higherBiome = BiomeRegistry.getByID(lowerBiome.getID() + 1);

                    float terrainDensityLower = lowerBiome.genTerrainDensity(noise, x, (int)this.y + y, z, lowerBiome.noiseOctaves, lowerBiome.noiseScale, lowerBiome.noisePersistance, lowerBiome.noiseLacunarity, lowerBiome.baseHeight, terrainOffsets) * lowerBiome.heightMultiplier;
                    float terrainDensityHigher = higherBiome.genTerrainDensity(noise, x, (int)this.y + y, z, higherBiome.noiseOctaves, higherBiome.noiseScale, higherBiome.noisePersistance, higherBiome.noiseLacunarity, higherBiome.baseHeight, terrainOffsets) * higherBiome.heightMultiplier;

                    float alpha = Math.abs((float) MathUtils.clamp((lowerBiome.maxHeight - biomeDensity) / 16f, 0f, 1f) - 1);
                    float interpolatedDensity = MathUtils.interpolate(terrainDensityLower, terrainDensityHigher, alpha);

                    voxels[x + y * SIZE + z * SIZE * SIZE] = new TerrainVoxel(interpolatedDensity, lowerBiome, alpha);
                }
            }
        }
    }
    List<Vector3f> vertices = new ArrayList<>();
    List<Vector3f> normals = new ArrayList<>();
    List<Vector3f> colors = new ArrayList<>();
    List<Integer> indices = new ArrayList<>();

    MarchingCubesGenerator generator = new MarchingCubesGenerator();

    // triangles should have SIZE - 1 ^ 3 entries in it, one for every voxel except the last x, y and z rows
    triangles = new HashMap<>();
    generator.generateMesh(voxels, SIZE, SIZE, SIZE, (int)this.y, vertices, normals, colors, indices, triangles);

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
