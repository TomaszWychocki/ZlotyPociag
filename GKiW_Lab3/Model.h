#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <map>
#include <fstream>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <IL/il.h> 
#include <IL/ilu.h> 
#include <IL/ilut.h>

class Model {
public:
	Model();
	~Model();
	void Render();
	bool Import3DFromFile(const std::string & pFile);
	std::string getBasePath(const std::string & path);
	int LoadGLTextures(const aiScene * scene);
	void Color4f(const aiColor4D * color);
	void set_float4(float f[4], float a, float b, float c, float d);
	void color4_to_float4(const aiColor4D * c, float f[4]);
	void apply_material(const aiMaterial * mtl);
	void recursive_render(const aiScene * sc, const aiNode * nd, float scale);

private:
	std::string modelpath = "models/terrain.obj";
	const aiScene* scene = NULL;
	GLuint scene_list = 0;
	std::map<std::string, GLuint*> textureIdMap;
	GLuint*	textureIds;
	Assimp::Importer importer;
};
