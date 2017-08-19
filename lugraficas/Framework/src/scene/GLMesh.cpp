#include <scene\GLMesh.h>
#define BUFFER_OFFSET(i) ((char *)NULL + (i))
#include <string>
#include <map>
#include <video\BaseDriver.h>


void GLMesh::Create(char * path) {
	/*
	long sizeFile;
	char *archivo = file2string(path, sizeFile);
	int counter = 0;
	int tempSizeBufferIndex = 0;
	int counterBufferIndex = 0;
	int offsetVertex = 0;
	int counterBufferVertex = 0;
	int tempSizeBufferVertex = 0;
	int dif;
	int positionBuffer;
	bool flag = true;
	char buffer1[20];

	mesh tempMesh;
	while (counter < sizeFile)
	{
		if (
			archivo[counter] == 'F' &&
			archivo[counter + 1] == 'r' &&
			archivo[counter + 2] == 'a' &&
			archivo[counter + 3] == 'm' &&
			archivo[counter + 4] == 'e' &&
			archivo[counter + 5] == ' ' &&
			archivo[counter + 6] != '{'
			)
		{
			counter += 6;
			counter = AddBone(archivo, counter, -1);
			if (archivo[counter] == 'M')
			{
				AddChildsAndBrothers();
			}
		}
		if (
			archivo[counter] == 'M' &&
			archivo[counter + 1] == 'e' &&
			archivo[counter + 2] == 's' &&
			archivo[counter + 3] == 'h' &&
			archivo[counter + 4] == ' ' &&
			archivo[counter + 5] == 'm'
			)
		{

			counter += 9;
			bones;
			flag = true;
			while (flag)
			{
				if (archivo[counter] == '{')
				{
					counter += 1;
					positionBuffer = 0;
					while (archivo[counter] != ';')
					{
						buffer1[positionBuffer] = archivo[counter];
						positionBuffer++;
						counter++;
					}
					buffer1[positionBuffer] = '\0';
					tempMesh.bufferVertex.resize(std::atof(buffer1));
					tempMesh.bonsInlfluenceForVertex.resize(std::atof(buffer1));

					for (int i = 0; i < tempMesh.bufferVertex.size(); i++)
					{
						counter++;
						positionBuffer = 0;
						while (archivo[counter] != ';')
						{
							buffer1[positionBuffer] = archivo[counter];
							counter++;
							positionBuffer++;
						}
						buffer1[positionBuffer] = '\0';
						tempMesh.bufferVertex[i].x = std::atof(buffer1);
						counter++;

						positionBuffer = 0;
						while (archivo[counter] != ';')
						{
							buffer1[positionBuffer] = archivo[counter];
							positionBuffer++;
							counter++;
						}
						buffer1[positionBuffer] = '\0';
						tempMesh.bufferVertex[i].y = std::atof(buffer1);

						counter++;

						positionBuffer = 0;
						while (archivo[counter] != ';')
						{
							buffer1[positionBuffer] = archivo[counter];
							positionBuffer++;
							counter++;
						}
						buffer1[positionBuffer] = '\0';
						tempMesh.bufferVertex[i].z = std::atof(buffer1);
						tempMesh.bufferVertex[i].w = 1;


						counterBufferVertex++;
						counter++;
					}
					//end vertex

					//startIndex
					counter += 2;
					dif = counter;
					positionBuffer = 0;

					while (archivo[counter] != ';')
					{
						buffer1[positionBuffer] = archivo[counter];
						positionBuffer++;
						counter++;
					}
					buffer1[positionBuffer] = '\0';
					dif -= std::atof(buffer1);
					tempMesh.bufferIndex.resize(std::atof(buffer1) * 3);
					tempMesh.meshbufferIndex.resize(std::atof(buffer1) * 3 * 2);

					counterBufferIndex = 0;
					for (int i = 0; i < tempMesh.bufferIndex.size(); i += 3)
					{

						counter++;
						while (archivo[counter] != ';')
						{
							counter++;
						}
						counter++;
						positionBuffer = 0;
						while (archivo[counter] != ',')
						{
							buffer1[positionBuffer] = archivo[counter];
							counter++;
							positionBuffer++;
						}
						buffer1[positionBuffer] = '\0';

						tempMesh.bufferIndex[i + 2] = std::atof(buffer1);
						counter++;

						positionBuffer = 0;
						while (archivo[counter] != ',')
						{
							buffer1[positionBuffer] = archivo[counter];
							counter++;
							positionBuffer++;
						}
						buffer1[positionBuffer] = '\0';
						tempMesh.bufferIndex[i + 1] = std::atof(buffer1);


						counter++;

						positionBuffer = 0;
						while (archivo[counter] != ';')
						{
							buffer1[positionBuffer] = archivo[counter];
							counter++;
							positionBuffer++;
						}
						buffer1[positionBuffer] = '\0';
						tempMesh.bufferIndex[i] = std::atof(buffer1);

						counter++;
						tempMesh.meshbufferIndex[counterBufferIndex] = tempMesh.bufferIndex[i];
						counterBufferIndex++;
						tempMesh.meshbufferIndex[counterBufferIndex] = tempMesh.bufferIndex[i + 1];
						counterBufferIndex++;

						tempMesh.meshbufferIndex[counterBufferIndex] = tempMesh.bufferIndex[i];
						counterBufferIndex++;
						tempMesh.meshbufferIndex[counterBufferIndex] = tempMesh.bufferIndex[i + 2];
						counterBufferIndex++;

						tempMesh.meshbufferIndex[counterBufferIndex] = tempMesh.bufferIndex[i + 1];
						counterBufferIndex++;
						tempMesh.meshbufferIndex[counterBufferIndex] = tempMesh.bufferIndex[i + 2];
						counterBufferIndex++;
					}
					//endIndex

					//normals
					counter += 2;
					dif = counter - dif;
					while (archivo[counter] != ';')
					{
						counter++;
					}
					counterBufferVertex -= tempSizeBufferVertex;
					for (int i = 0; i < tempMesh.bufferVertex.size(); i++)
					{
						counter++;
						positionBuffer = 0;
						while (archivo[counter] != ';')
						{
							buffer1[positionBuffer] = archivo[counter];
							counter++;
							positionBuffer++;
						}
						buffer1[positionBuffer] = '\0';
						tempMesh.bufferVertex[i].nx = std::atof(buffer1);
						counter++;

						positionBuffer = 0;
						while (archivo[counter] != ';')
						{
							buffer1[positionBuffer] = archivo[counter];
							positionBuffer++;
							counter++;
						}
						buffer1[positionBuffer] = '\0';
						tempMesh.bufferVertex[i].ny = std::atof(buffer1);


						counter++;

						positionBuffer = 0;
						while (archivo[counter] != ';')
						{
							buffer1[positionBuffer] = archivo[counter];
							positionBuffer++;
							counter++;
						}
						buffer1[positionBuffer] = '\0';
						tempMesh.bufferVertex[i].nz = std::atof(buffer1);
						tempMesh.bufferVertex[i].nw = 1;


						counter++;
						counterBufferVertex++;
					}
					//endnormals

					//uvs
					counter += dif + 30;
					while (archivo[counter] != ';')
					{
						counter++;
					}
					counter++;
					counterBufferVertex -= tempSizeBufferVertex;
					for (int i = 0; i < tempMesh.bufferVertex.size(); i++)
					{
						counter++;
						positionBuffer = 0;
						while (archivo[counter] != ';')
						{
							buffer1[positionBuffer] = archivo[counter];
							counter++;
							positionBuffer++;
						}
						buffer1[positionBuffer] = '\0';
						tempMesh.bufferVertex[i].s = std::atof(buffer1);
						counter++;

						positionBuffer = 0;
						while (archivo[counter] != ';')
						{
							buffer1[positionBuffer] = archivo[counter];
							positionBuffer++;
							counter++;
						}
						buffer1[positionBuffer] = '\0';
						tempMesh.bufferVertex[i].t = std::atof(buffer1);

						counterBufferVertex++;
						counter++;
					}
					//enduvs

					//DEclData
					while (archivo[counter] != '{')
					{
						counter++;
					}
					counter++;
					positionBuffer = 0;
					while (archivo[counter] != ';')
					{
						buffer1[positionBuffer] = archivo[counter];
						positionBuffer++;
						counter++;
					}
					buffer1[positionBuffer] = '\0';
					//numero de valores del decl data
					while (!(archivo[counter] == ';' && archivo[counter + 1] == ';'))
					{
						counter++;
					}
					counter += 2;

					positionBuffer = 0;
					while (archivo[counter] != ';')
					{
						buffer1[positionBuffer] = archivo[counter];
						positionBuffer++;
						counter++;
					}
					buffer1[positionBuffer] = '\0';
					unsigned int sizeDeclData = std::atoi(buffer1);
					counter++;
					///
					unsigned long tempNumber;
					float *castFloat;
					for (int i = 0; i < tempMesh.bufferVertex.size(); i++)
					{
						positionBuffer = 0;
						while (archivo[counter] != ',')
						{
							buffer1[positionBuffer] = archivo[counter];
							positionBuffer++;
							counter++;
						}
						counter++;
						buffer1[positionBuffer] = '\0';
						tempNumber = std::strtoul(buffer1, NULL, 0);
						castFloat = (float*)&tempNumber;
						tempMesh.bufferVertex[i].bx = (*castFloat);

						positionBuffer = 0;
						while (archivo[counter] != ',')
						{
							buffer1[positionBuffer] = archivo[counter];
							positionBuffer++;
							counter++;
						}
						counter++;
						buffer1[positionBuffer] = '\0';
						tempNumber = std::strtoul(buffer1, NULL, 0);
						castFloat = (float*)&tempNumber;
						tempMesh.bufferVertex[i].by = (*castFloat);

						positionBuffer = 0;
						while (archivo[counter] != ',')
						{
							buffer1[positionBuffer] = archivo[counter];
							positionBuffer++;
							counter++;
						}
						counter++;
						buffer1[positionBuffer] = '\0';
						tempNumber = std::strtoul(buffer1, NULL, 0);
						castFloat = (float*)&tempNumber;
						tempMesh.bufferVertex[i].bz = (*castFloat);
						tempMesh.bufferVertex[i].bw = 1;


						positionBuffer = 0;
						while (archivo[counter] != ',')
						{
							buffer1[positionBuffer] = archivo[counter];
							positionBuffer++;
							counter++;
						}
						counter++;
						buffer1[positionBuffer] = '\0';
						tempNumber = std::strtoul(buffer1, NULL, 0);
						castFloat = (float*)&tempNumber;
						tempMesh.bufferVertex[i].tx = (*castFloat);

						positionBuffer = 0;
						while (archivo[counter] != ',')
						{
							buffer1[positionBuffer] = archivo[counter];
							positionBuffer++;
							counter++;
						}
						counter++;
						buffer1[positionBuffer] = '\0';
						tempNumber = std::strtoul(buffer1, NULL, 0);
						castFloat = (float*)&tempNumber;
						tempMesh.bufferVertex[i].ty = (*castFloat);

						positionBuffer = 0;
						while (archivo[counter] != ',' && archivo[counter] != ';')
						{
							buffer1[positionBuffer] = archivo[counter];
							positionBuffer++;
							counter++;
						}
						counter++;
						buffer1[positionBuffer] = '\0';
						tempNumber = std::strtoul(buffer1, NULL, 0);
						castFloat = (float*)&tempNumber;
						tempMesh.bufferVertex[i].tz = (*castFloat);
						tempMesh.bufferVertex[i].tw = 1;

					}

					//
					while (archivo[counter] != '}')
					{
						counter++;
					}
					counter++;
					int counterOpenBrackets = 1;
					while (!(counterOpenBrackets == 0))
					{
						if (archivo[counter + 4] == 'M' &&
							archivo[counter + 5] == 'e' &&
							archivo[counter + 6] == 's' &&
							archivo[counter + 7] == 'h' &&
							archivo[counter + 8] == 'M' &&
							archivo[counter + 9] == 'a' &&
							archivo[counter + 10] == 't')
						{
							counterOpenBrackets--;
						}
						if (archivo[counter] == '{')
						{
							counterOpenBrackets++;
						}
						if (archivo[counter] == '}')
						{
							counterOpenBrackets--;
						}
						if (archivo[counter] == 'S' &&
							archivo[counter + 1] == 'k' &&
							archivo[counter + 2] == 'i' &&
							archivo[counter + 3] == 'n' &&
							archivo[counter + 4] == 'W' &&
							archivo[counter + 5] == 'e' &&
							archivo[counter + 6] == 'i' &&
							archivo[counter + 7] == 'g' &&
							archivo[counter + 8] == 'h' &&
							archivo[counter + 9] == 't' &&
							archivo[counter + 10] == 's')
						{
							counterOpenBrackets++;
							while (archivo[counter] != '"')
							{
								counter++;
							}
							counter++;
							positionBuffer = 0;
							while (archivo[counter] != '"')
							{
								buffer1[positionBuffer] = archivo[counter];
								positionBuffer++;
								counter++;
							}
							counter += 3;
							buffer1[positionBuffer] = '\0';

							int selectedBone;
							for (int i = 0; i < bones.size(); i++)
							{
								if (strcmp(buffer1, bones[i].name) == 0)
								{
									selectedBone = i;
									break;
								}
							}

							int numberOfVertexAfectedForBone;
							positionBuffer = 0;
							std::vector<int> vertexAfected;
							std::vector<float> influencVertexAfected;

							while (archivo[counter] != ';')
							{
								buffer1[positionBuffer] = archivo[counter];
								positionBuffer++;
								counter++;
							}
							buffer1[positionBuffer] = '\0';
							numberOfVertexAfectedForBone = std::atoi(buffer1);
							counter++;
							for (int i = 0; i < numberOfVertexAfectedForBone; i++)
							{
								positionBuffer = 0;
								while (archivo[counter] != ';' && archivo[counter] != ',')
								{
									buffer1[positionBuffer] = archivo[counter];
									positionBuffer++;
									counter++;
								}
								counter++;
								buffer1[positionBuffer] = '\0';
								vertexAfected.push_back(std::atoi(buffer1));
							}
							tempMesh.bonsInlfluenceForVertex[std::atoi(buffer1)];
							counter++;
							for (int i = 0; i < numberOfVertexAfectedForBone; i++)
							{
								positionBuffer = 0;
								while (archivo[counter] != ';' && archivo[counter] != ',')
								{
									buffer1[positionBuffer] = archivo[counter];
									positionBuffer++;
									counter++;
								}
								counter++;
								buffer1[positionBuffer] = '\0';
								influencVertexAfected.push_back(std::atof(buffer1));
							}
							counter++;
							//MATRIX OFFSET
							for (int i = 0; i < 16; i++)
							{
								positionBuffer = 0;
								while (!(archivo[counter] == ',' || archivo[counter] == ';'))
								{
									buffer1[positionBuffer] = archivo[counter];
									counter++;
									positionBuffer++;
								}
								buffer1[positionBuffer] = '\0';
								bones[selectedBone].tranformMatrix.v[i] = std::atof(buffer1);
								counter++;
							}
							for (int i = 0; i < vertexAfected.size(); i++)
							{
								tempMesh.bonsInlfluenceForVertex[vertexAfected[i]].bones.push_back(selectedBone);
								tempMesh.bonsInlfluenceForVertex[vertexAfected[i]].influence.push_back(influencVertexAfected[i]);
							}


						}
						counter++;
					}
					counter++;
					flag = false;
				}
				counter++;
			}
		}
		if (
			archivo[counter] == 'L' &&
			archivo[counter + 1] == 'i' &&
			archivo[counter + 2] == 's' &&
			archivo[counter + 3] == 't' &&
			archivo[counter + 4] == ' ' &&
			archivo[counter + 5] == 'm' &&
			archivo[counter + 6] == 't' &&
			archivo[counter + 7] == 'l' &&
			archivo[counter + 8] == 's'
			)
		{
			infotex tempContentInfotext;
			counter = counter + 12;
			positionBuffer = 0;
			while (archivo[counter] != ';')
			{
				buffer1[positionBuffer] = archivo[counter];
				positionBuffer++;
				counter++;
			}
			buffer1[positionBuffer] = '\0';
			tempContentInfotext.numberOfTextures = std::atoi(buffer1);
			counter++;
			positionBuffer = 0;
			while (archivo[counter] != ';')
			{
				buffer1[positionBuffer] = archivo[counter];
				positionBuffer++;
				counter++;
			}
			buffer1[positionBuffer] = '\0';
			tempContentInfotext.indicesTextures.resize(std::atoi(buffer1));
			counter++;
			for (int i = 0; i < tempContentInfotext.indicesTextures.size(); i++)
			{
				positionBuffer = 0;
				while (archivo[counter] != ';' && archivo[counter] != ',')
				{
					buffer1[positionBuffer] = archivo[counter];
					positionBuffer++;
					counter++;
				}
				counter++;
				buffer1[positionBuffer] = '\0';
				tempContentInfotext.indicesTextures[i] = std::atof(buffer1);
			}

			textureByMesh tempTextureMesh;
			while (tempContentInfotext.textures.size() < tempContentInfotext.numberOfTextures)
			{
				if (
					archivo[counter - 1] == ' ' &&
					archivo[counter] == 'M' &&
					archivo[counter + 1] == 'a' &&
					archivo[counter + 2] == 't' &&
					archivo[counter + 3] == 'e' &&
					archivo[counter + 4] == 'r' &&
					archivo[counter + 5] == 'i' &&
					archivo[counter + 6] == 'a' &&
					archivo[counter + 7] == 'l' &&
					archivo[counter + 8] == ' '
					) {
					counter += 8;
					tempTextureMesh.gloss = false;
					tempTextureMesh.normal = false;
					tempTextureMesh.specular = false;
				}
				if (
					archivo[counter] == 'T' &&
					archivo[counter + 1] == 'e' &&
					archivo[counter + 2] == 'x' &&
					archivo[counter + 3] == 't' &&
					archivo[counter + 4] == 'u' &&
					archivo[counter + 5] == 'r' &&
					archivo[counter + 6] == 'e' &&
					archivo[counter + 7] == 'F' &&
					archivo[counter + 8] == 'i' &&
					archivo[counter + 9] == 'l' &&
					archivo[counter + 10] == 'e' &&
					archivo[counter + 11] == 'n' &&
					archivo[counter + 12] == 'a' &&
					archivo[counter + 13] == 'm' &&
					archivo[counter + 14] == 'e'
					) {
					counter += 15;
					tempContentInfotext.textures.push_back(tempTextureMesh);
				}
				if (
					archivo[counter] == '"' &&
					archivo[counter + 1] == 'd' &&
					archivo[counter + 2] == 'i' &&
					archivo[counter + 3] == 'f' &&
					archivo[counter + 4] == 'f' &&
					archivo[counter + 5] == 'u' &&
					archivo[counter + 6] == 's' &&
					archivo[counter + 7] == 'e' &&
					archivo[counter + 8] == 'M' &&
					archivo[counter + 9] == 'a' &&
					archivo[counter + 10] == 'p' &&
					archivo[counter + 11] == '"'
					)
				{
					counter = counter + 12;

					while (archivo[counter] != '"')
					{
						counter++;
					}
					counter++;
					char* temp = new char[30];
					positionBuffer = 0;
					while (archivo[counter] != '"')
					{
						if (archivo[counter] == 92) {
							positionBuffer = 0;
							counter++;
						}
						else {
							temp[positionBuffer] = archivo[counter];
							positionBuffer++;
							counter++;
						}
					}
					temp[positionBuffer] = '\0';
					tempTextureMesh.diffuseName = temp;
				}
				//SPECULAR
				if (
					archivo[counter] == '"' &&
					archivo[counter + 1] == 's' &&
					archivo[counter + 2] == 'p' &&
					archivo[counter + 3] == 'e' &&
					archivo[counter + 4] == 'c' &&
					archivo[counter + 5] == 'u' &&
					archivo[counter + 6] == 'l' &&
					archivo[counter + 7] == 'a' &&
					archivo[counter + 8] == 'r' &&
					archivo[counter + 9] == 'M' &&
					archivo[counter + 10] == 'a' &&
					archivo[counter + 11] == 'p' &&
					archivo[counter + 12] == '"'
					)
				{
					counter = counter + 13;

					while (archivo[counter] != '"')
					{
						counter++;
					}
					counter++;
					char* temp = new char[30];
					positionBuffer = 0;
					while (archivo[counter] != '"')
					{
						if (archivo[counter] == 92) {
							positionBuffer = 0;
							counter++;
						}
						else {
							temp[positionBuffer] = archivo[counter];
							positionBuffer++;
							counter++;
						}
					}
					temp[positionBuffer] = '\0';
					tempTextureMesh.specularName = temp;
					tempTextureMesh.specular = true;
				}
				//GLOSSS
				if (
					archivo[counter] == '"' &&
					archivo[counter + 1] == 'g' &&
					archivo[counter + 2] == 'l' &&
					archivo[counter + 3] == 'o' &&
					archivo[counter + 4] == 's' &&
					archivo[counter + 5] == 's' &&
					archivo[counter + 6] == 'M' &&
					archivo[counter + 7] == 'a' &&
					archivo[counter + 8] == 'p' &&
					archivo[counter + 9] == '"'
					)
				{
					counter = counter + 10;

					while (archivo[counter] != '"')
					{
						counter++;
					}
					counter++;
					char* temp = new char[30];
					positionBuffer = 0;
					while (archivo[counter] != '"')
					{
						if (archivo[counter] == 92) {
							positionBuffer = 0;
							counter++;
						}
						else {
							temp[positionBuffer] = archivo[counter];
							positionBuffer++;
							counter++;
						}
					}
					temp[positionBuffer] = '\0';
					tempTextureMesh.glossName = temp;
					tempTextureMesh.gloss = true;
				}
				//NORMAL
				if (
					archivo[counter] == '"' &&
					archivo[counter + 1] == 'n' &&
					archivo[counter + 2] == 'o' &&
					archivo[counter + 3] == 'r' &&
					archivo[counter + 4] == 'm' &&
					archivo[counter + 5] == 'a' &&
					archivo[counter + 6] == 'l' &&
					archivo[counter + 7] == 'M' &&
					archivo[counter + 8] == 'a' &&
					archivo[counter + 9] == 'p' &&
					archivo[counter + 10] == '"'
					)
				{
					counter = counter + 11;

					while (archivo[counter] != '"')
					{
						counter++;
					}
					counter++;
					char* temp = new char[30];
					positionBuffer = 0;
					while (archivo[counter] != '"')
					{
						if (archivo[counter] == 92) {
							positionBuffer = 0;
							counter++;
						}
						else {
							temp[positionBuffer] = archivo[counter];
							positionBuffer++;
							counter++;
						}
					}
					temp[positionBuffer] = '\0';
					tempTextureMesh.normalName = temp;
					tempTextureMesh.normal = true;

				}
				counter++;
			}
			tempMesh.infoTexture = tempContentInfotext;
			meshes.push_back(tempMesh);
			//infoMeshTextures.push_back(tempContentInfotext);
		}
		counter++;

	}
	for (auto i = meshes.begin(); i != meshes.end(); i++) {

		for (int j = 0; j < i->infoTexture.numberOfTextures; j++)
		{
			std::vector<unsigned short> *temp;
			temp = new std::vector<unsigned short>;
			i->bufferIndexForTextures.push_back(temp);
		}

		int countIndex = 0;
		for (auto textureCount = i->infoTexture.indicesTextures.begin(); textureCount != i->infoTexture.indicesTextures.end(); textureCount++)
		{
			i->bufferIndexForTextures[(*textureCount)]->push_back(i->bufferIndex[countIndex]);
			countIndex++;
			i->bufferIndexForTextures[(*textureCount)]->push_back(i->bufferIndex[countIndex]);
			countIndex++;
			i->bufferIndexForTextures[(*textureCount)]->push_back(i->bufferIndex[countIndex]);
			countIndex++;
		}
	}

	char *vsSourceP = file2string("Shaders/VS.glsl");
	char *fsSourceP = file2string("Shaders/FS.glsl");




	std::string vstr = std::string(vsSourceP);
	std::string fstr = std::string(fsSourceP);

	std::string wireframeShader = "attribute highp vec4 Vertex;\n\n";
	wireframeShader += "uniform highp mat4 WVP;\n\n";

	wireframeShader += "void main(){\n\n";
	wireframeShader += "gl_Position = WVP*Vertex;\n\n";
	wireframeShader += "}\n\n";

	std::string vertex = wireframeShader;

	wireframeShader = "";
	wireframeShader = "void main() { gl_FragColor = vec4(1.0, 0.8, 0.2, 1.0);}";
	std::string fragment = wireframeShader;

	shaderWireFrame = glCreateProgram();
	GLuint vshader_id0 = createShader(GL_VERTEX_SHADER, (char*)vertex.c_str());
	GLuint fshader_id0 = createShader(GL_FRAGMENT_SHADER, (char*)fragment.c_str());


	glAttachShader(shaderWireFrame, vshader_id0);
	glAttachShader(shaderWireFrame, fshader_id0);

	glLinkProgram(shaderWireFrame);
	glUseProgram(shaderWireFrame);

	vertexAttribLocSimple = glGetAttribLocation(shaderWireFrame, "Vertex");
	matWorldViewProjUniformLocSimple = glGetUniformLocation(shaderWireFrame, "WVP");

	glUseProgram(0);

	shaderID = glCreateProgram();
	GLuint vshader_id = createShader(GL_VERTEX_SHADER, (char*)vstr.c_str());
	GLuint fshader_id = createShader(GL_FRAGMENT_SHADER, (char*)fstr.c_str());

	if (vshader_id && fshader_id)
	{
		glAttachShader(shaderID, vshader_id);
		glAttachShader(shaderID, fshader_id);

		glLinkProgram(shaderID);
		glUseProgram(shaderID);

		vertexAttribLoc = glGetAttribLocation(shaderID, "Vertex");
		normalAttribLoc = glGetAttribLocation(shaderID, "Normal");
		binormalAttribLoc = glGetAttribLocation(shaderID, "Binormal");
		tangenteAttribLoc = glGetAttribLocation(shaderID, "Tangente");
		uvAttribLoc = glGetAttribLocation(shaderID, "UV");

		matWorldViewProjUniformLoc = glGetUniformLocation(shaderID, "WVP");
		matWorldUniformLoc = glGetUniformLocation(shaderID, "World");
		diffuseLoc = glGetUniformLocation(shaderID, "diffuse");
		specularLoc = glGetUniformLocation(shaderID, "specularLoc");
		glossLoc = glGetUniformLocation(shaderID, "glossLoc");

		normalLoc = glGetUniformLocation(shaderID, "normalLoc");

#ifdef USE_GLOBALLIGHT
		DirectionGlobalLight = glGetUniformLocation(shaderID, "DirectionGlobalLight");
		ColorGlobalLight = glGetUniformLocation(shaderID, "ColorGlobalLight");
#endif
#ifdef	USE_POINTLIGHT
		PositionPointLight = glGetUniformLocation(shaderID, "PositionPointLight");
		ColorPointLight = glGetUniformLocation(shaderID, "ColorPointLight");
#endif
#ifdef	USE_DIFFUSE
		PosCamera = glGetUniformLocation(shaderID, "PositionCamera");
#endif
		glUseProgram(0);
	}
	else
	{
		shaderID = shaderWireFrame;
	}

	for (auto i = meshes.begin(); i != meshes.end(); i++)
	{
		glGenBuffers(1, &((*i).VB));
		glBindBuffer(GL_ARRAY_BUFFER, ((*i).VB));
		glBufferData(GL_ARRAY_BUFFER, (*i).bufferVertex.size() * sizeof(CVertex), (*i).bufferVertex.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		for (int index = 0; index < (*i).bufferIndexForTextures.size(); index++)
		{
			glGenBuffers(1, &((*i).IB[index]));
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ((*i).IB[index]));
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, (*i).bufferIndexForTextures[index]->size() * sizeof(unsigned short), (*i).bufferIndexForTextures[index]->data(), GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		glGenBuffers(1, &((*i).IBMesh));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ((*i).IBMesh));
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, (*i).meshbufferIndex.size() * sizeof(unsigned short), (*i).meshbufferIndex.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	std::map<std::string, int> list;
	for (auto mesh = meshes.begin(); mesh != meshes.end(); mesh++)
	{
		for (auto textures = (*mesh).infoTexture.textures.begin(); textures != (*mesh).infoTexture.textures.end(); textures++) {
			std::string tempString((*textures).diffuseName);
			auto iteradorFind = list.find(tempString);
			if (iteradorFind == list.end())
			{
				Texture	*tex = new GLTexture;
				list[tempString] = tex->LoadTexture((*textures).diffuseName);
				if (list[tempString] == -1) {
					list[tempString] = tex->LoadTexture("cheker.tga");
				}

				(*textures).idDiffuse = list[tempString];

			}
			else
			{
				(*textures).idDiffuse = list[tempString];
			}
			if ((*textures).specular)
			{
				std::string tempString((*textures).specularName);
				auto iteradorFind = list.find(tempString);
				if (iteradorFind == list.end())
				{
					Texture	*tex = new GLTexture;
					list[tempString] = tex->LoadTexture((*textures).specularName);
					if (list[tempString] == -1) {
						delete tex;
						textures->specular = false;
					}
					else
					{
						(*textures).idSpecular = list[tempString];
					}
				}
				else
				{
					(*textures).idSpecular = list[tempString];
				}
			}
			if ((*textures).gloss)
			{
				std::string tempString((*textures).glossName);
				auto iteradorFind = list.find(tempString);
				if (iteradorFind == list.end())
				{
					Texture	*tex = new GLTexture;
					list[tempString] = tex->LoadTexture((*textures).glossName);
					if (list[tempString] == -1) {
						delete tex;
						textures->gloss = false;
					}
					else
					{
						(*textures).idGloss = list[tempString];
					}
				}
				else
				{
					(*textures).idGloss = list[tempString];
				}
			}
			if ((*textures).normal)
			{
				std::string tempString((*textures).normalName);
				auto iteradorFind = list.find(tempString);
				if (iteradorFind == list.end())
				{
					Texture	*tex = new GLTexture;
					list[tempString] = tex->LoadTexture((*textures).normalName);
					if (list[tempString] == -1) {
						delete tex;
						textures->normal = false;
					}
					else
					{
						(*textures).idNormal = list[tempString];
					}
				}
				else
				{
					(*textures).idNormal = list[tempString];
				}
			}
		}
	}

	transform = transform.Identity();
	free(vsSourceP);
	free(fsSourceP);
	free(archivo);
	bones;
	meshes;
	*/
}

void GLMesh::Transform(CMatrix4D *t) {
	transform = *t;
}

void GLMesh::Draw(CMatrix4D *t, CMatrix4D *vp) {

	if (t)
		transform = *t;

	Camera *pActualCamera = pScProp->pCameras[0];

	CMatrix4D VP = pActualCamera->VP;
	CMatrix4D WVP = transform*VP;
	CMatrix4D WorldView = transform*pActualCamera->View;
	//CVector4D infoCam = CVector4D(0.1f, 10000.0f, 90 * Deg2Rad, 1.0f);
	CVector4D infoCam = CVector4D(pActualCamera->NPlane, pActualCamera->FPlane, pActualCamera->Fov, 1.0f);


	
	glUseProgram(shaderID);

#ifdef	USE_DIFFUSE
	glUniform3f(PosCamera, lights->posCamera->x, lights->posCamera->y, lights->posCamera->z);
#endif
#ifdef USE_GLOBALLIGHT
	glUniform3f(DirectionGlobalLight, lights->dirGlobal.x, lights->dirGlobal.y, lights->dirGlobal.z);
	glUniform3f(ColorGlobalLight, lights->colorGlobal.x, lights->colorGlobal.y, lights->colorGlobal.z);
#endif
#ifdef	USE_POINTLIGHT
	glUniform3f(PositionPointLight, lights->posPoint.x, lights->posPoint.y, lights->posPoint.z);
	glUniform3f(ColorPointLight, lights->colorPoint.x, lights->colorPoint.y, lights->colorPoint.z);
#endif

	glUniformMatrix4fv(matWorldUniformLoc, 1, GL_FALSE, &transform.m[0][0]);
	glUniformMatrix4fv(matWorldViewProjUniformLoc, 1, GL_FALSE, &WVP.m[0][0]);




	for (auto i = meshes.begin(); i != meshes.end(); i++)
	{
		glBindBuffer(GL_ARRAY_BUFFER, (*i).VB);
		glEnableVertexAttribArray(vertexAttribLoc);
		glEnableVertexAttribArray(normalAttribLoc);

		if (uvAttribLoc != -1)
			glEnableVertexAttribArray(uvAttribLoc);
		if (binormalAttribLoc != -1)
			glEnableVertexAttribArray(binormalAttribLoc);
		if (tangenteAttribLoc != -1)
			glEnableVertexAttribArray(tangenteAttribLoc);

		glVertexAttribPointer(vertexAttribLoc, 4, GL_FLOAT, GL_FALSE, sizeof(CVertex), BUFFER_OFFSET(0));
		glVertexAttribPointer(normalAttribLoc, 4, GL_FLOAT, GL_FALSE, sizeof(CVertex), BUFFER_OFFSET(16));

		if (uvAttribLoc != -1)
			glVertexAttribPointer(uvAttribLoc, 2, GL_FLOAT, GL_FALSE, sizeof(CVertex), BUFFER_OFFSET(32));
		if (binormalAttribLoc != -1)
			glVertexAttribPointer(binormalAttribLoc, 4, GL_FLOAT, GL_FALSE, sizeof(CVertex), BUFFER_OFFSET(40));
		if (tangenteAttribLoc != -1)
			glVertexAttribPointer(tangenteAttribLoc, 4, GL_FLOAT, GL_FALSE, sizeof(CVertex), BUFFER_OFFSET(56));



		for (int index = 0; index < (*i).bufferIndexForTextures.size(); index++)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, (*i).infoTexture.textures[index].idDiffuse);
			glUniform1i(diffuseLoc, 0);
			if ((*i).infoTexture.textures[index].normal)
			{
				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, (*i).infoTexture.textures[index].idNormal);
				glUniform1i(normalLoc, 1);
			}
			if ((*i).infoTexture.textures[index].specular)
			{
				glActiveTexture(GL_TEXTURE2);
				glBindTexture(GL_TEXTURE_2D, (*i).infoTexture.textures[index].idSpecular);
				glUniform1i(specularLoc, 2);
			}
			if ((*i).infoTexture.textures[index].gloss)
			{
				glActiveTexture(GL_TEXTURE3);
				glBindTexture(GL_TEXTURE_2D, (*i).infoTexture.textures[index].idGloss);
				glUniform1i(glossLoc, 3);
			}
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, (*i).IB[index]);
			glDrawElements(GL_TRIANGLES, (*i).bufferIndexForTextures[index]->size(), GL_UNSIGNED_SHORT, 0);
		}

	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glDisableVertexAttribArray(vertexAttribLoc);
	glDisableVertexAttribArray(normalAttribLoc);

	if (uvAttribLoc != -1) {
		glDisableVertexAttribArray(uvAttribLoc);
	}

	glUseProgram(0);
	glUseProgram(0);

}

void GLMesh::Destroy() {
#ifdef USING_GL_COMMON
	glDeleteProgram(shaderID);
#endif
}