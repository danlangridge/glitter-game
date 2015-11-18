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
        faces[j] = vertices[i].x *.5f;
        faces[j + 1] = vertices[i].y *.5f;
        faces[j + 2] = vertices[i].z *.5f;
         printf("x: %f, y: %f, z: %f\n", vertices[i].x, vertices[i].y, vertices[i].z);
    }

    unsigned int numFaces = mesh->mNumFaces;

    aiFace * meshFaces = mesh->mFaces;
    

    /*
   for (unsigned i = 0; i < numFaces*3; i = i + 3) {
       faces[i] = vertices[meshFaces[i].mIndices[0]].x;
       faces[i + 1] = vertices[meshFaces[i].mIndices[0]].y;
       faces[i + 2] = vertices[meshFaces[i].mIndices[0]].z;
        printf("x: %f, y: %f, z: %f\n", faces[i], faces[i + 1], faces[i + 2]);
   
   }*/ 
    return faces; 
}



}
