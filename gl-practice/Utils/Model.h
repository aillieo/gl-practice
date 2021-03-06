#ifndef MODEL_H
#define MODEL_H

#include "GL/glew.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "../Utils/GLMethod.h"
#include "../Utils/Mesh.h"
#include "../Utils/Shader.h"

using std::vector;
using std::string;

class Model
{
public:
    /*  Model Data */
    // stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    vector<Texture> textures_loaded;
    
    vector<Mesh> meshes;
    string directory;
    bool gammaCorrection;
    
    // constructor, expects a filepath to a 3D model.
    Model(string const &path, bool gamma = false);
    
    // draws the model, and thus all its meshes
    void Draw(Shader shader);

	void drawAsinstanced(Shader* shader, int amount);

	void setupInstanceattribute(GLuint index, GLuint instanceAmount, GLsizeiptr size, const void* data, GLuint divisor);
    
private:

    // loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
    void loadModel(string const &path);

    
    // processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
    void processNode(aiNode *node, const aiScene *scene);
    
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    
    
    // checks all material textures of a given type and loads the textures if they're not loaded yet.
    // the required info is returned as a Texture struct.
    vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
    
};

#endif
