#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>

namespace Gravel
{

class Mesh {

    public:
        Mesh(std::string filename);
        float* getVertices();
        unsigned int getSize();
    private:
        Assimp::Importer mAssetImporter;
        unsigned int mSize;
};

}
