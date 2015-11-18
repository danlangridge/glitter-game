#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>

namespace Gravel
{

class Mesh {

    public:
        Mesh(std::string filename);
        float* getVertices();
    private:
        Assimp::Importer mAssetImporter;
};

}
