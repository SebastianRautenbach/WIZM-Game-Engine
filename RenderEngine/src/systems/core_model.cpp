#include "system/core_model.h"

lowlevelsys::core_model::core_model(const char* file_path)
{
    loadModel(file_path);
}

void lowlevelsys::core_model::render_model(core_gl_shader* shader)
{
	for (unsigned int i = 0; i < meshes.size(); i++)
		meshes[i].draw_mesh(shader);
}

void lowlevelsys::core_model::loadModel(std::string path)
{
    Assimp::Importer import;
    const aiScene * scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        return;
    }
    directory = path.substr(0, path.find_last_of('/'));

    processNode(scene->mRootNode, scene);
}

void lowlevelsys::core_model::processNode(aiNode* node, const aiScene* scene)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }
    // then do the same for each of its children
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

lowlevelsys::core_mesh lowlevelsys::core_model::processMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<vertex_data> vertices;
    std::vector<unsigned int> indices;
    std::vector<core_gl_texture> textures;

   
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        vertex_data vertex;
        glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
        // positions
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;
        // normals
        if (mesh->HasNormals())
        {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.Normal = vector;
        }
        // texture coordinates
        if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            glm::vec2 vec;
            // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
            // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
     

            if(mesh->HasTangentsAndBitangents())
            {
                vector.x = mesh->mTangents[i].x;
                vector.y = mesh->mTangents[i].y;
                vector.z = mesh->mTangents[i].z;
                vertex.Tangent = vector;
             
                vector.x = mesh->mBitangents[i].x;
                vector.y = mesh->mBitangents[i].y;
                vector.z = mesh->mBitangents[i].z;
                vertex.Bitangent = vector;
            }
        }
        else
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);

        vertices.push_back(vertex);
    }
    // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        // retrieve all indices of the face and store them in the indices vector
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    // process materials
    //aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

    //std::vector<core_gl_texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    //textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    //
    //std::vector<core_gl_texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    //textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    //
    //std::vector<core_gl_texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
    //textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
    //
    //std::vector<core_gl_texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
    //textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

    return core_mesh(vertices, indices, textures);
}



std::vector<core_gl_texture> lowlevelsys::core_model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
    std::vector<core_gl_texture> textures;
    //for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    //{
    //    aiString str;
    //    mat->GetTexture(type, i, &str);
    //    // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
    //    bool skip = false;
    //    for (unsigned int j = 0; j < textures_loaded.size(); j++)
    //    {
    //        if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
    //        {
    //            textures.push_back(textures_loaded[j]);
    //            skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
    //            break;
    //        }
    //    }
    //    if (!skip)
    //    {   // if texture hasn't been loaded already, load it
    //        core_gl_texture texture(str.C_Str(), this->directory);
    //        texture.type = typeName;
    //        texture.path = str.C_Str();
    //        textures.push_back(texture);
    //        textures_loaded.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecessary load duplicate textures.
    //    }
    //}
    return textures;
}