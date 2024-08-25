#ifndef SCENE_H
#define SCENE_H

#include <glm/glm.hpp>

#include <vector>

struct Material
{
    glm::vec3 Albido{1.0f};
    float Roughness = 1.0f;
    float Metallic = 0.0f;
};

struct Sphere
{
    glm::vec3 Position{0.0f};
    float Radius = 0.5f;

    int MaterialIndex = 0;
};

struct Scene
{
    std::vector<Sphere> Spheres;
    std::vector<Material> Materials;
};

#endif // SCENE_H
