#include <fstream>
#include <cstdio> 

#include "mesh.hpp"

namespace Gravel
{

Mesh::Mesh(std::string filename) 
{
   const aiScene* scene = mAssetImporter.ReadFile(filename, 0);

   if (scene == NULL) {
       printf("%s\n", mAssetImporter.GetErrorString());
   } else {
       printf("Retrieved %u meshes from %s\n", scene->mNumMeshes, filename.c_str());
   }
}

float* Mesh::getVertices() {
    const aiScene* scene = mAssetImporter.GetScene();
    aiMesh* mesh = scene->mMeshes[0];

    unsigned int numVertices = mesh->mNumVertices;

    aiVector3D* vertices = mesh->mVertices; 
    printf("Retrieved %u vertices\n", numVertices);

    float* faces = new float[numVertices*3];
    for (unsigned i = 0; i < numVertices; i++) {
        unsigned j = i*3;
        faces[j] = vertices[i].x;
        faces[j + 1] = vertices[i].y;
        faces[j + 2] = vertices[i].z;
         printf("x: %f, y: %f, z: %f\n", vertices[i].x, vertices[i].y, vertices[i].z);
    }
    
    return faces; 
}

}
