#include <scene/D3DXMesh.h>

#include <video/BaseDriver.h>
#include <iostream>

#include <video/D3DXShader.h>

#define CHANGE_TO_RH 0
#define DEBUG_MODEL 0

extern ComPtr<ID3D11Device>            D3D11Device;
extern ComPtr<ID3D11DeviceContext>     D3D11DeviceContext;

static int LinePosNumber = 0;

bool LoadLine(const char * cFile, const long fileSz, long & OriginalStartPosition, long & OriginalEndPosition)
{
	const char CEnter = static_cast<char>(10);
	const char CRetur = static_cast<char>(13);

	bool enterFound = false;
	bool spaceFound = false;

	long StartPosition = OriginalEndPosition;
	long EndPosition = OriginalEndPosition;

	if (EndPosition < fileSz)
	{
		LinePosNumber++;
		while (!enterFound && EndPosition < fileSz)
		{
			if (cFile[EndPosition] == CEnter)
				enterFound = true;
			EndPosition++;
		}

		OriginalEndPosition = EndPosition;
		OriginalStartPosition = StartPosition;

		return true;
	}

	return false;
}

bool HasCRLF(const char * cFile, const long fileSz)
{
	const char CRetur = static_cast<char>(13);
	int fileCharPointer = 0;

	while (fileCharPointer < fileSz)
	{
		if (cFile[fileCharPointer] == CRetur)
			return true;
		fileCharPointer++;
	}
	return false;
}

void D3DXMesh::Create(char *filename)
{
	file_name = std::string(filename);

	needToLoadAnimation = false;

	hasNormals = false;
	hasBiNormals = false;
	hasTangets = false;
	hasUVs = false;
	hasDifusse = false;
	hasSpecular = false;
	hasGlossMap = false;
	hasNormalMap = false;

	char *fileInChars;
	long fileSz;
	long fileStartPointer = 0;
	long fileEndPointer = 0;

	fileInChars = file2string(filename, fileSz);

	Sig = 0;

	printf("Trabajando en: %s\n", filename);

	//Logre abrir el archivo
	if (fileInChars != NULL)
	{
		int NumberOfNULLS = 0;

		verticesSz = 0;

		int pos;
		int lastPos;
		int IndexOffset = 0;

		std::vector<CVertex*> vertexTmp;
		std::vector<int> vertexSzTmp;
		std::vector<unsigned short*> indicesTmp;
		std::vector<int> indicesSzTmp;

		std::vector<int> numberOfmaterials;
		std::vector<std::vector<int>> materials;

		int totalDeLineas = 0;
		unsigned long tempoInto = 0;
		int saltarse;

		char * g_pText;
		float g_fNumero;

		char g_Line[256];

		//Cargar cosas
		while (LoadLine(fileInChars, fileSz, fileStartPointer, fileEndPointer))
		{
			memset(g_Line, 0, 256);
			memcpy(&g_Line[0], fileInChars + fileStartPointer, fileEndPointer - fileStartPointer);

			if (strstr(g_Line, "template XSkinMeshHeader"))
			{
				needToLoadAnimation = true;
			}
			else if (needToLoadAnimation)
			{
				if (LoadMeshBone(-1, g_Line, fileInChars, fileSz, fileStartPointer, fileEndPointer))
					needToLoadAnimation = false;
			}
			else if (strstr(g_Line, "Mesh "))
			{
				if (!strstr(g_Line, "template ")) //La linea no contiene la palabra template
				{
					LoadLine(fileInChars, fileSz, fileStartPointer, fileEndPointer);
					g_pText = fileInChars + fileStartPointer;
					int tmpvBack = atoi(g_pText);

					vertexSzTmp.push_back(tmpvBack); //Lee cuantos vertices hay
					verticesSz += tmpvBack; //Almacenar cuantos vertices habra en total
					vertexTmp.push_back(new CVertex[tmpvBack]); //Crear el espacio para los vertices
					CVertex * vertexBack = vertexTmp.back();
					//Load vertex positions

					for (int i = 0; i < tmpvBack; i++)
					{
						//Read the X,Y,Z coordinates of the actual vertex
						LoadLine(fileInChars, fileSz, fileStartPointer, fileEndPointer);
						g_pText = fileInChars + fileStartPointer;

						vertexBack[i].x = atof(g_pText);

						g_pText = strchr(g_pText + 1, ';');
						vertexBack[i].y = atof(g_pText + 1);

						g_pText = strchr(g_pText + 1, ';');
						vertexBack[i].z = atof(g_pText + 1);

						vertexBack[i].w = 1.0f;
					}

					do
					{
						LoadLine(fileInChars, fileSz, fileStartPointer, fileEndPointer);
					} while (fileEndPointer - fileStartPointer <= 0);

					g_pText = fileInChars + fileStartPointer;
					int indexSzBack = 3 * atoi(g_pText);
					indicesSzTmp.push_back(indexSzBack);
					indicesTmp.push_back(new unsigned short[indexSzBack]); //Reservar espacio guardar el orden de los indices
					unsigned short * indexBack = indicesTmp.back();
					//Load index order
					for (int i = 0; i < indexSzBack; i += 3)
					{
						//Read the X,Y,Z coordinates of the actual vertex
						LoadLine(fileInChars, fileSz, fileStartPointer, fileEndPointer);
						g_pText = fileInChars + fileStartPointer;

						g_pText = strchr(g_pText + 1, ';');
						indexBack[i + 0] = atoi(g_pText + 1) + IndexOffset;

						g_pText = strchr(g_pText + 1, ',');
						indexBack[i + 1] = atoi(g_pText + 1) + IndexOffset;

						g_pText = strchr(g_pText + 1, ',');
						indexBack[i + 2] = atoi(g_pText + 1) + IndexOffset;
					}
					IndexOffset += vertexSzTmp.back();
				}
			}
			else if (strstr(g_Line, "MeshNormals ")) //Se encontro una linea con la palabra MeshNormals
			{
				if (!strstr(g_Line, "template ")) //La linea no contiene la palabra template
				{
					hasNormals = true;

					LoadLine(fileInChars, fileSz, fileStartPointer, fileEndPointer); //Cantidad de normales a cargar, no se guarda por que es el mismo numero de vertices
																					 //Read the X,Y,Z coordinates of the actual vertex
					int tmpvSz = vertexSzTmp.back();
					CVertex * vertexBack = vertexTmp.back();

					for (int i = 0; i < tmpvSz; i++)
					{
						LoadLine(fileInChars, fileSz, fileStartPointer, fileEndPointer);

						g_pText = fileInChars + fileStartPointer;
						vertexBack[i].nx = atof(g_pText);

						g_pText = strchr(g_pText + 1, ';');
						vertexBack[i].ny = atof(g_pText + 1);

						g_pText = strchr(g_pText + 1, ';');
						vertexBack[i].nz = atof(g_pText + 1);

						vertexBack[i].nw = 1.0f;
					}
					//Ignorar lineas
					LoadLine(fileInChars, fileSz, fileStartPointer, fileEndPointer);
					g_pText = fileInChars + fileStartPointer;
					int ignoreTmpi = atoi(g_pText);


					for (int i = 0; i < ignoreTmpi; i++)
						LoadLine(fileInChars, fileSz, fileStartPointer, fileEndPointer);

				}
			}
			else if (strstr(g_Line, "MeshTextureCoords "))
			{
				if (!strstr(g_Line, "template ")) //La linea no contiene la palabra template
				{
					hasUVs = true;
					LoadLine(fileInChars, fileSz, fileStartPointer, fileEndPointer); //Cantidad de normales a cargar, no se guarda por que es el mismo numero de vertices

					int vertexSzBack = vertexSzTmp.back();
					CVertex * vertexBack = vertexTmp.back();

					for (int i = 0; i < vertexSzBack; i++)
					{
						LoadLine(fileInChars, fileSz, fileStartPointer, fileEndPointer);
						g_pText = fileInChars + fileStartPointer;

						vertexBack[i].s = atof(g_pText);

						g_pText = strchr(g_pText + 1, ';');
						vertexBack[i].t = atof(g_pText + 1);
					}

				}
			}
			else if (strstr(g_Line, "DeclData"))
			{
				if (!strstr(g_Line, "template ")) //La linea no contiene la palabra template
				{
					hasBiNormals = true;
					hasTangets = true;

					//Sabes cuantas cosas hay
					LoadLine(fileInChars, fileSz, fileStartPointer, fileEndPointer);
					g_pText = fileInChars + fileStartPointer;
					saltarse = atoi(g_pText);

					//Saltarse lineas caca
					for (int i = 0; i < saltarse; i++)
						LoadLine(fileInChars, fileSz, fileStartPointer, fileEndPointer);

					//Leer cuantas lineas hay que leer
					LoadLine(fileInChars, fileSz, fileStartPointer, fileEndPointer);
					g_pText = fileInChars + fileStartPointer;
					totalDeLineas = atoi(g_pText);
					tempoInto = 0;
					int tmpnewLineas = totalDeLineas / (saltarse * 3);

					CVertex * vertexBack = vertexTmp.back();

					for (int i = 0; i < tmpnewLineas; i++)
					{
						//tangentes
						if (saltarse >= 2)
						{
							LoadLine(fileInChars, fileSz, fileStartPointer, fileEndPointer);
							g_pText = fileInChars + fileStartPointer;
							tempoInto = atof(g_pText);
							vertexBack[i].tx = *(float*)&tempoInto;

							LoadLine(fileInChars, fileSz, fileStartPointer, fileEndPointer);
							g_pText = fileInChars + fileStartPointer;
							tempoInto = atof(g_pText);
							vertexBack[i].ty = *(float*)&tempoInto;

							LoadLine(fileInChars, fileSz, fileStartPointer, fileEndPointer);
							g_pText = fileInChars + fileStartPointer;
							tempoInto = atof(g_pText);
							vertexBack[i].tz = *(float*)&tempoInto;
						}
						//Binormales
						if (saltarse >= 1)
						{
							LoadLine(fileInChars, fileSz, fileStartPointer, fileEndPointer);
							g_pText = fileInChars + fileStartPointer;
							tempoInto = atof(g_pText);
							vertexBack[i].bx = *(float*)&tempoInto;

							LoadLine(fileInChars, fileSz, fileStartPointer, fileEndPointer);
							g_pText = fileInChars + fileStartPointer;
							tempoInto = atof(g_pText);
							vertexBack[i].by = *(float*)&tempoInto;

							LoadLine(fileInChars, fileSz, fileStartPointer, fileEndPointer);
							g_pText = fileInChars + fileStartPointer;
							tempoInto = atof(g_pText);
							vertexBack[i].bz = *(float*)&tempoInto;
						}
					}

				}
			}
			else if (strstr(g_Line, "MeshMaterialList mtls {"))
			{
				//Saber cuantos tipos de materiales va a haber
				LoadLine(fileInChars, fileSz, fileStartPointer, fileEndPointer);
				g_pText = fileInChars + fileStartPointer;
				numberOfmaterials.push_back(atoi(g_pText));

				//Leer cuantas lineas vamos a leer
				LoadLine(fileInChars, fileSz, fileStartPointer, fileEndPointer);
				g_pText = fileInChars + fileStartPointer;
				int totalMaterialsLines = atoi(g_pText);

				materials.resize(materials.size() + 1);

				std::vector<int> * lastMaterial = &materials.back();

				for (int i = 0; i < totalMaterialsLines; i++)
				{
					LoadLine(fileInChars, fileSz, fileStartPointer, fileEndPointer);
					g_pText = fileInChars + fileStartPointer;
					lastMaterial->push_back(atoi(g_pText));
				}

			}
			else if (strstr(g_Line, "bUseDiffuseMap"))
			{
				LoadLine(fileInChars, fileSz, fileStartPointer, fileEndPointer);
				g_pText = fileInChars + fileStartPointer;
				useTexture.push_back(atoi(g_pText));
			}
			else if (strstr(g_Line, "bUseNormalMap"))
			{
				LoadLine(fileInChars, fileSz, fileStartPointer, fileEndPointer);
				g_pText = fileInChars + fileStartPointer;
				useNormalMap.push_back(atoi(g_pText));
			}
			else if (strstr(g_Line, "bUseSpecMap"))
			{
				LoadLine(fileInChars, fileSz, fileStartPointer, fileEndPointer);
				g_pText = fileInChars + fileStartPointer;
				useSpecularMap.push_back(atoi(g_pText));
			}
			else if (strstr(g_Line, "bUseGlossMap"))
			{
				LoadLine(fileInChars, fileSz, fileStartPointer, fileEndPointer);
				g_pText = fileInChars + fileStartPointer;
				useGlossMap.push_back(atoi(g_pText));
			}
			else if (strstr(g_Line, "EffectParamString "))
			{
				if (!strstr(g_Line, "template"))
				{
					std::string line;

					LoadLine(fileInChars, fileSz, fileStartPointer, fileEndPointer);

					memset(g_Line, 0, 256);
					memcpy(&g_Line[0], fileInChars + fileStartPointer, fileEndPointer - fileStartPointer);

					int lastComillas;

					if (strstr(g_Line, "diffuseMap"))
					{
						LoadLine(fileInChars, fileSz, fileStartPointer, fileEndPointer);
						line.clear();
						line.assign(fileInChars + fileStartPointer, fileEndPointer - fileStartPointer - 1);

						Texture *tex = new D3DXTexture;

						pos = line.find("\\\\");
						if (pos <= 1)
							pos = line.find("\"");
						pos++;

						lastComillas = line.find("\"", pos);

						line = line.substr(pos, lastComillas - pos);
						TextureID.push_back(tex->LoadTexture((char*)line.c_str()));
						if (TextureID.back() != -1)
						{
							Textures.push_back(tex);
							hasDifusse = true;
						}
					}
					if (strstr(g_Line, "normalMap"))
					{
						LoadLine(fileInChars, fileSz, fileStartPointer, fileEndPointer);
						line.clear();
						line.assign(fileInChars + fileStartPointer, fileEndPointer - fileStartPointer - 1);

						Texture *tex = new D3DXTexture;

						pos = line.find("\\\\");
						if (pos <= 1)
							pos = line.find("\"");
						pos++;

						lastComillas = line.find("\"", pos);

						line = line.substr(pos, lastComillas - pos);
						NormalMapID.push_back(tex->LoadTexture((char*)line.c_str()));
						if (NormalMapID.back() != -1)
						{
							Textures.push_back(tex);
							hasNormalMap = true;
						}
					}
					if (strstr(g_Line, "specularMap"))
					{
						LoadLine(fileInChars, fileSz, fileStartPointer, fileEndPointer);
						line.clear();
						line.assign(fileInChars + fileStartPointer, fileEndPointer - fileStartPointer - 1);

						Texture *tex = new D3DXTexture;

						pos = line.find("\\\\");
						if (pos <= 1)
							pos = line.find("\"");
						pos++;

						lastComillas = line.find("\"", pos);

						line = line.substr(pos, lastComillas - pos);
						SpecularMapID.push_back(tex->LoadTexture((char*)line.c_str()));

						if (SpecularMapID.back() != -1)
						{
							Textures.push_back(tex);
							hasSpecular = true;
						}
					}
					if (strstr(g_Line, "glossMap"))
					{
						LoadLine(fileInChars, fileSz, fileStartPointer, fileEndPointer);
						line.clear();
						line.assign(fileInChars + fileStartPointer, fileEndPointer - fileStartPointer - 1);

						Texture *tex = new D3DXTexture;

						pos = line.find("\\\\");
						if (pos <= 1)
							pos = line.find("\"");
						pos++;

						lastComillas = line.find("\"", pos);

						line = line.substr(pos, lastComillas - pos);
						GlossMapID.push_back(tex->LoadTexture((char*)line.c_str()));

						if (GlossMapID.back() != -1)
						{
							Textures.push_back(tex);
							hasGlossMap = true;
						}
					}
					if (strstr(g_Line, "siMap"))
					{

					}
				}
			}
			else if (strstr(g_Line, "SkinWeights "))
			{
				if (!strstr(g_Line, "template"))
				{
					std::string MatrixName;
					MatrixName.clear();

					LoadLine(fileInChars, fileSz, fileStartPointer, fileEndPointer);
					memset(g_Line, 0, 256);
					memcpy(&g_Line[0], fileInChars + fileStartPointer, fileEndPointer - fileStartPointer);

					//Cargar nombre
					char * CharPointer;
					CharPointer = strchr(g_Line, '\"');
					int nameStartPos = CharPointer - g_Line + 1;
					CharPointer = strrchr(g_Line, '\"');
					int nameLength = (CharPointer - g_Line + 1) - nameStartPos;

					MatrixName = std::string(g_Line).substr(nameStartPos, nameLength - 1);

					LoadLine(fileInChars, fileSz, fileStartPointer, fileEndPointer);
					memset(g_Line, 0, 256);
					memcpy(&g_Line[0], fileInChars + fileStartPointer, fileEndPointer - fileStartPointer);

					//Leer cuantos vertices vamos a modificar
					int totalAfectedVertex = atoi(g_Line);

					std::vector<CVertex*> VertexToModify;
					VertexToModify.resize(totalAfectedVertex);

					int intloaded;
					float floatLoaded;

					for (int vertexIndex = 0; vertexIndex < totalAfectedVertex; vertexIndex++)
					{
						LoadLine(fileInChars, fileSz, fileStartPointer, fileEndPointer);
						memset(g_Line, 0, 256);
						memcpy(&g_Line[0], fileInChars + fileStartPointer, fileEndPointer - fileStartPointer);

						intloaded = atoi(g_Line);

						VertexToModify[vertexIndex] = &vertexTmp.back()[intloaded];
					}

					for (auto it : VertexToModify)
					{
						LoadLine(fileInChars, fileSz, fileStartPointer, fileEndPointer);
						memset(g_Line, 0, 256);
						memcpy(&g_Line[0], fileInChars + fileStartPointer, fileEndPointer - fileStartPointer);

						floatLoaded = atof(g_Line);

						it->weight = floatLoaded;
					}

					VertexToModify.clear();

				}
			}
			else if (strstr(g_Line, "AnimationSet "))
			{
				if (!strstr(g_Line, "template"))
				{
					Animations.resize(Animations.size() + 1);
					SAnimationSet & NewAnimation = Animations.back();

					int NumeroDeMatrices;
					int indiceMatriz;
					float xi, yj, zk, w;

					std::string AnimationName = std::string(g_Line);
					int NameEnd = AnimationName.find("{") - 1;
					NewAnimation.Name = AnimationName.substr(13, NameEnd - 13);
					do
					{
						do
						{
							LoadLine(fileInChars, fileSz, fileStartPointer, fileEndPointer);
							memset(g_Line, 0, 256);
							memcpy(&g_Line[0], fileInChars + fileStartPointer, fileEndPointer - fileStartPointer);
						} while (!strstr(g_Line, "Animation "));

						NewAnimation.Keys.resize(NewAnimation.Keys.size() + 1);
						AnimationName = std::string(g_Line);
						NameEnd = AnimationName.find("{") - 1;
						NewAnimation.Keys.back().Name = AnimationName.substr(13, NameEnd - 13);

						//Rotaciones
						do
						{
							LoadLine(fileInChars, fileSz, fileStartPointer, fileEndPointer);
							memset(g_Line, 0, 256);
							memcpy(&g_Line[0], fileInChars + fileStartPointer, fileEndPointer - fileStartPointer);
						} while (!strstr(g_Line, "AnimationKey rot {"));

						LoadLine(fileInChars, fileSz, fileStartPointer, fileEndPointer);
						memset(g_Line, 0, 256);
						memcpy(&g_Line[0], fileInChars + fileStartPointer, fileEndPointer - fileStartPointer);
						//Valor extraño

						LoadLine(fileInChars, fileSz, fileStartPointer, fileEndPointer);
						memset(g_Line, 0, 256);
						memcpy(&g_Line[0], fileInChars + fileStartPointer, fileEndPointer - fileStartPointer);
						NumeroDeMatrices = atoi(g_Line);

						for (int i = 0; i < NumeroDeMatrices; i++)
						{
							//Indice;NumeroDeValores;xi,jk,zk,w;;,
							LoadLine(fileInChars, fileSz, fileStartPointer, fileEndPointer);
							g_pText = fileInChars + fileStartPointer;

							NewAnimation.Keys.back().RotationTimes.push_back(atoi(g_pText));

							g_pText = strchr(g_pText + 1, ';');
							//4

							g_pText = strchr(g_pText + 1, ';');
							xi = atof(g_pText + 1);
							g_pText = strchr(g_pText + 1, ',');
							yj = atof(g_pText + 1);
							g_pText = strchr(g_pText + 1, ',');
							zk = atof(g_pText + 1);
							g_pText = strchr(g_pText + 1, ',');
							w = atof(g_pText + 1);

							NewAnimation.Keys.back().Rotation.push_back(CQuaternion(xi, yj, zk, w));
						}
						//Escalaciones
						do
						{
							LoadLine(fileInChars, fileSz, fileStartPointer, fileEndPointer);
							memset(g_Line, 0, 256);
							memcpy(&g_Line[0], fileInChars + fileStartPointer, fileEndPointer - fileStartPointer);
						} while (!strstr(g_Line, "AnimationKey scale {"));

						LoadLine(fileInChars, fileSz, fileStartPointer, fileEndPointer);
						memset(g_Line, 0, 256);
						memcpy(&g_Line[0], fileInChars + fileStartPointer, fileEndPointer - fileStartPointer);
						//Valor extraño

						LoadLine(fileInChars, fileSz, fileStartPointer, fileEndPointer);
						memset(g_Line, 0, 256);
						memcpy(&g_Line[0], fileInChars + fileStartPointer, fileEndPointer - fileStartPointer);
						NumeroDeMatrices = atoi(g_Line);

						for (int i = 0; i < NumeroDeMatrices; i++)
						{
							//Indice;NumeroDeValores;xi,jk,zk,w;;,
							LoadLine(fileInChars, fileSz, fileStartPointer, fileEndPointer);
							g_pText = fileInChars + fileStartPointer;

							NewAnimation.Keys.back().ScalationTimes.push_back(atoi(g_pText));

							g_pText = strchr(g_pText + 1, ';');
							//3

							g_pText = strchr(g_pText + 1, ';');
							xi = atof(g_pText + 1);
							g_pText = strchr(g_pText + 1, ',');
							yj = atof(g_pText + 1);
							g_pText = strchr(g_pText + 1, ',');
							zk = atof(g_pText + 1);
							w = 1.0f;

							NewAnimation.Keys.back().Scalation.push_back(CQuaternion(xi, yj, zk, w));
						}
						//Posicion
						do
						{
							LoadLine(fileInChars, fileSz, fileStartPointer, fileEndPointer);
							memset(g_Line, 0, 256);
							memcpy(&g_Line[0], fileInChars + fileStartPointer, fileEndPointer - fileStartPointer);
						} while (!strstr(g_Line, "AnimationKey pos {"));

						LoadLine(fileInChars, fileSz, fileStartPointer, fileEndPointer);
						memset(g_Line, 0, 256);
						memcpy(&g_Line[0], fileInChars + fileStartPointer, fileEndPointer - fileStartPointer);
						//Valor extraño

						LoadLine(fileInChars, fileSz, fileStartPointer, fileEndPointer);
						memset(g_Line, 0, 256);
						memcpy(&g_Line[0], fileInChars + fileStartPointer, fileEndPointer - fileStartPointer);
						NumeroDeMatrices = atoi(g_Line);

						for (int i = 0; i < NumeroDeMatrices; i++)
						{
							//Tiempo;NumeroDeValores;xi,jk,zk,w;;,
							LoadLine(fileInChars, fileSz, fileStartPointer, fileEndPointer);
							g_pText = fileInChars + fileStartPointer;

							NewAnimation.Keys.back().TraslationTimes.push_back(atoi(g_pText));

							g_pText = strchr(g_pText + 1, ';');
							//3

							g_pText = strchr(g_pText + 1, ';');
							xi = atof(g_pText + 1);
							g_pText = strchr(g_pText + 1, ',');
							yj = atof(g_pText + 1);
							g_pText = strchr(g_pText + 1, ',');
							zk = atof(g_pText + 1);
							w = 1.0f;

							NewAnimation.Keys.back().Traslation.push_back(CQuaternion(xi, yj, zk, w));
						}
						LoadLine(fileInChars, fileSz, fileStartPointer, fileEndPointer); //End bracket of positions
						LoadLine(fileInChars, fileSz, fileStartPointer, fileEndPointer); //End bracket of Animation

						LoadLine(fileInChars, fileSz, fileStartPointer, fileEndPointer);
						memset(g_Line, 0, 256);
						memcpy(&g_Line[0], fileInChars + fileStartPointer, fileEndPointer - fileStartPointer);
					} while (!strstr(g_Line, "}"));
				}
			}
		}
		printf("Archivo listo\n");
		free(fileInChars);

		vertices = new CVertex[verticesSz];
		//indices = new unsigned short[indicesSz];

		int countah = 0;
		//Pasar la informacion a un buffer unico
		for (int i = 0; i < vertexSzTmp.size(); i++)
		{
			for (int k = 0; k < vertexSzTmp[i]; k++)
			{
				vertices[countah] = vertexTmp[i][k];
				countah++;
			}
		}

		countah = 0;
		int tmpCicle = materials.size();

		for (int i = 0; i < tmpCicle; i++)
		{
			indices.resize(indices.size() + numberOfmaterials[i]);

			for (int k = 0; k < materials[i].size(); k++)
			{
#if CHANGE_TO_RH
				indices[countah + materials[i][k]].push_back(indicesTmp[i][(k * 3) + 2]);
				indices[countah + materials[i][k]].push_back(indicesTmp[i][(k * 3) + 1]);
				indices[countah + materials[i][k]].push_back(indicesTmp[i][(k * 3) + 0]);
#else
				indices[countah + materials[i][k]].push_back(indicesTmp[i][(k * 3) + 0]);
				indices[countah + materials[i][k]].push_back(indicesTmp[i][(k * 3) + 1]);
				indices[countah + materials[i][k]].push_back(indicesTmp[i][(k * 3) + 2]);
#endif
			}
			countah += numberOfmaterials[i];
		}
		for (int subset = 0; subset < indices.size(); subset++)
		{
			wireframeIndex.resize(wireframeIndex.size() + 1);

			for (int i = 0; i < indices[subset].size(); i += 3)
			{
				wireframeIndex[subset].push_back(indices[subset][i + 0]);
				wireframeIndex[subset].push_back(indices[subset][i + 1]);
				wireframeIndex[subset].push_back(indices[subset][i + 1]);
				wireframeIndex[subset].push_back(indices[subset][i + 2]);
				wireframeIndex[subset].push_back(indices[subset][i + 2]);
				wireframeIndex[subset].push_back(indices[subset][i + 0]);
			}
		}

		wireframeMode = false;

		//Limpiar vectores temporales
		for (auto it = vertexTmp.rbegin(); it != vertexTmp.rend(); it++)
			delete[](*it);
		vertexTmp.clear();
		vertexSzTmp.clear();
		for (auto it = indicesTmp.rbegin(); it != indicesTmp.rend(); it++)
			delete[](*it);
		indicesTmp.clear();
		indicesSzTmp.clear();
	}

	char *vsSourceP = file2string("Shaders/VS_Mesh.hlsl");
	char *fsSourceP = file2string("Shaders/FS_Mesh.hlsl");

	std::string vstr;
	std::string fstr;

	if (vsSourceP == NULL || fsSourceP == NULL)
	{
		vstr = dummyShaderVS;
		fstr = dummyShaderFS;
	}
	else
	{
		vstr = std::string(vsSourceP);
		fstr = std::string(fsSourceP);
	}

	free(vsSourceP);
	free(fsSourceP);

	if (hasNormals)
		Sig |= Signature::HAS_NORMALS;
	if (hasBiNormals)
		Sig |= Signature::HAS_BINORMALS;
	if (hasTangets)
		Sig |= Signature::HAS_TANGENTS;
	if (hasUVs)
		Sig |= Signature::HAS_TEXCOORDS0;
	if (hasDifusse)
		Sig |= Signature::DIFFUSE_MAP;
	if (hasNormalMap)
		Sig |= Signature::NORMAL_MAP;
	if (hasSpecular)
		Sig |= Signature::SPECULAR_MAP;
	if (hasGlossMap)
		Sig |= Signature::GLOSS_MAP;

	g_pBaseDriver->CreateShader(vstr, fstr, Sig);

	int gBuffSig = Sig;
	gBuffSig |= Signature::GBUFF_PASS;
	g_pBaseDriver->CreateShader(vstr, fstr, gBuffSig);

	int shadowSig = Sig;
	shadowSig |= Signature::SHADOW_MAP_PASS;
	g_pBaseDriver->CreateShader(vstr, fstr, shadowSig);

	HRESULT hr;

	D3DXShader *s = dynamic_cast<D3DXShader*>(g_pBaseDriver->GetShaderSig(Sig));

	D3D11DeviceContext->IASetInputLayout(s->Layout.Get());

	D3D11_BUFFER_DESC bdesc = { 0 };
	bdesc.Usage = D3D11_USAGE_DEFAULT;
	bdesc.ByteWidth = sizeof(D3DXMesh::CBuffer);
	bdesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	hr = D3D11Device->CreateBuffer(&bdesc, 0, pd3dConstantBuffer.GetAddressOf());
	if (hr != S_OK)
	{
		printf("Error Creating Buffer Layout\n");
		return;
	}

	// Set the constant buffer to the shader programs: Note that we use the Device Context to manage the resources
	D3D11DeviceContext->VSSetConstantBuffers(0, 1, pd3dConstantBuffer.GetAddressOf());
	D3D11DeviceContext->PSSetConstantBuffers(0, 1, pd3dConstantBuffer.GetAddressOf());

	// We fill the descriptor, this time we set that will be used for vertex data, that is, vertex buffer
	bdesc = { 0 };
	bdesc.ByteWidth = verticesSz * sizeof(CVertex);
	bdesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	// Resource sub data is just a structure friendly to set our pointer to the vertex data
	D3D11_SUBRESOURCE_DATA subData = { vertices, 0, 0 };

	// As we did with the constant buffer, we create the actual vertex buffer
	hr = D3D11Device->CreateBuffer(&bdesc, &subData, &VB);
	if (hr != S_OK)
	{
		printf("Error Creating Vertex Buffer\n");
		return;
	}

	// Same for the index buffer

	for (int i = 0; i < indices.size(); i++)
	{
		bdesc = { 0 };
		bdesc.ByteWidth = indices[i].size() * sizeof(USHORT);
		bdesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

		subData = { &indices[i][0], 0, 0 };
		IB.resize(IB.size() + 1);
		hr = D3D11Device->CreateBuffer(&bdesc, &subData, &IB[i]);
		if (hr != S_OK)
		{
			printf("Error Creating Index Buffer\n");
			return;
		}

		bdesc = { 0 };
		bdesc.ByteWidth = wireframeIndex[i].size() * sizeof(USHORT);
		bdesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

		subData = { &wireframeIndex[i][0], 0, 0 };
		WIB.resize(WIB.size() + 1);
		hr = D3D11Device->CreateBuffer(&bdesc, &subData, &WIB[i]);
		if (hr != S_OK)
		{
			printf("Error Creating Index Buffer\n");
			return;
		}
	}



	transform = transform.Identity();
	printf("Terminado\n\n");
}

void D3DXMesh::Transform(CMatrix4D * t)
{
	transform = *t;
}

void D3DXMesh::Draw(CMatrix4D *t, CMatrix4D *vp)
{
	if (t)
		transform = *t;

	Camera *pActualCamera = pScProp->pCameras[0];

	CMatrix4D VP = pActualCamera->VP;
	CMatrix4D WVP = transform*VP;
	CMatrix4D WorldView = transform*pActualCamera->View;
	//CVector4D infoCam = CVector4D(0.1f, 10000.0f, 90 * Deg2Rad, 1.0f);
	CVector4D infoCam = CVector4D(pActualCamera->NPlane, pActualCamera->FPlane, pActualCamera->Fov, 1.0f);

	int countText = 0;
	int countNorm = 0;
	int countSpec = 0;
	int countGlos = 0;

	memcpy(&CnstBuffer.WVP.v, WVP.v, 64);
	memcpy(&CnstBuffer.World.v, transform.v, 64);
	memcpy(&CnstBuffer.WorldView.v, WorldView.v, 64);

	memcpy(&CnstBuffer.Light0Pos.v, pScProp->Lights[0].Position.v, 16);
	memcpy(&CnstBuffer.Light0Col.v, pScProp->Lights[0].Color.v, 16);
	memcpy(&CnstBuffer.CameraPos.v, pActualCamera->Eye.v, 16);
	memcpy(&CnstBuffer.Ambient.v, pScProp->AmbientColor.v, 16);
	memcpy(&CnstBuffer.CameraInfo.v, infoCam.v, 16);

	UINT stride = sizeof(CVertex);
	UINT offset = 0;
	// We bound to use the vertex and pixel shader of this primitive
	D3D11DeviceContext->VSSetShader(pVS.Get(), 0, 0);
	D3D11DeviceContext->PSSetShader(pFS.Get(), 0, 0);
	// Set the input layout to let the shader program know what kind of vertex data we have
	D3D11DeviceContext->IASetInputLayout(Layout.Get());

	int tmpCount = 0;

	D3DXShader *s = 0;
	D3DXShader *last = (D3DXShader*)32;
	D3D11DeviceContext->IASetVertexBuffers(0, 1, VB.GetAddressOf(), &stride, &offset);

	unsigned int sig = Sig;
	sig |= gSig;
	s = dynamic_cast<D3DXShader*>(g_pBaseDriver->GetShaderSig(sig));

	D3D11DeviceContext->VSSetShader(s->pVS.Get(), 0, 0);
	D3D11DeviceContext->PSSetShader(s->pFS.Get(), 0, 0);
	D3D11DeviceContext->IASetInputLayout(s->Layout.Get());

	D3D11DeviceContext->UpdateSubresource(pd3dConstantBuffer.Get(), 0, 0, &CnstBuffer, 0, 0);
	D3D11DeviceContext->VSSetConstantBuffers(0, 1, pd3dConstantBuffer.GetAddressOf());
	D3D11DeviceContext->PSSetConstantBuffers(0, 1, pd3dConstantBuffer.GetAddressOf());

	// Same for the index buffer
	for (int i = 0; i < indices.size(); i++)
	{
		D3DXTexture *texd3d;

		// We let d3d that we are using our vertex and index buffers, they require the stride and offset
		D3D11DeviceContext->IASetVertexBuffers(0, 1, VB.GetAddressOf(), &stride, &offset);

		if (!useTexture.empty())
		{
			if (useTexture[i])
			{
				texd3d = dynamic_cast<D3DXTexture*>(Textures[tmpCount]);
				D3D11DeviceContext->PSSetShaderResources(0, 1, texd3d->pSRVTex.GetAddressOf());
				tmpCount++;
			}
		}
		if (!useSpecularMap.empty())
		{
			if (useSpecularMap[i])
			{
				texd3d = dynamic_cast<D3DXTexture*>(Textures[tmpCount]);
				D3D11DeviceContext->PSSetShaderResources(1, 1, texd3d->pSRVTex.GetAddressOf());
				tmpCount++;
			}
		}
		if (!useGlossMap.empty())
		{
			if (useGlossMap[i])
			{
				texd3d = dynamic_cast<D3DXTexture*>(Textures[tmpCount]);
				D3D11DeviceContext->PSSetShaderResources(2, 1, texd3d->pSRVTex.GetAddressOf());
				tmpCount++;
			}
		}
		if (!useNormalMap.empty())
		{
			if (useNormalMap[i])
			{
				texd3d = dynamic_cast<D3DXTexture*>(Textures[tmpCount]);
				D3D11DeviceContext->PSSetShaderResources(3, 1, texd3d->pSRVTex.GetAddressOf());
				tmpCount++;
			}
		}

		D3D11DeviceContext->PSSetSamplers(0, 1, texd3d->pSampler.GetAddressOf());

		if (wireframeMode)
		{
			D3D11DeviceContext->IASetIndexBuffer(WIB[i].Get(), DXGI_FORMAT_R16_UINT, 0);

			D3D11DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
			D3D11DeviceContext->DrawIndexed(wireframeIndex[i].size(), 0, 0);
		}
		else
		{
			D3D11DeviceContext->IASetIndexBuffer(IB[i].Get(), DXGI_FORMAT_R16_UINT, 0);

			D3D11DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			D3D11DeviceContext->DrawIndexed(indices[i].size(), 0, 0);
		}

	}
}


void D3DXMesh::Destroy()
{

}

bool D3DXMesh::LoadMeshBone(int myFather, char * g_Line, const char * cFile, const long fileSz, long & OriginalStartPosition, long & OriginalEndPosition)
{
	//Hay una nueva estructura de hueso
	if (strstr(g_Line, "Frame ") && !strstr(g_Line, "template"))
	{
		int bonesSz = Bones.size() + 1;
		Bones.resize(bonesSz);

		MeshBone & tmpBone = Bones.back();
		int me = bonesSz;
		int openKeys = 1;

		//Decirle quien es el padre
		tmpBone.m_iParent = myFather;

		//Decirle a mi papa que soy su hijo :'v
		if (myFather != -1)
			Bones[myFather].m_vecChildren.push_back(me);

		//Cargar nombre
		char * CharPointer;
		CharPointer = strchr(g_Line, ' ');
		int nameStartPos = CharPointer - g_Line + 1;
		CharPointer = strrchr(g_Line, ' ');
		int nameLength = (CharPointer - g_Line + 1) - nameStartPos;
		tmpBone.Name = std::string(g_Line).substr(nameStartPos, nameLength - 1);

		//Encontrar la linea que nos dice donde esta la transform matrix
		do
		{
			LoadLine(cFile, fileSz, OriginalStartPosition, OriginalEndPosition);
			memset(g_Line, 0, 256);
			memcpy(&g_Line[0], cFile + OriginalStartPosition, OriginalEndPosition - OriginalStartPosition);
		} while (!strstr(g_Line, "FrameTransformMatrix relative {"));
		LoadLine(cFile, fileSz, OriginalStartPosition, OriginalEndPosition);
		memset(g_Line, 0, 256);
		memcpy(&g_Line[0], cFile + OriginalStartPosition, OriginalEndPosition - OriginalStartPosition);

		//Cargar la matrix del hueso
		CharPointer = g_Line;
		tmpBone.m_CMat4Relative.v[0] = atof(CharPointer);
		CharPointer = strchr(g_Line, ',') + 1;
		for (int matrixIndex = 1; matrixIndex < 16; matrixIndex++)
		{
			tmpBone.m_CMat4Relative.v[matrixIndex] = atof(CharPointer);
			CharPointer = strchr(CharPointer, ',') + 1;
		}

		LoadLine(cFile, fileSz, OriginalStartPosition, OriginalEndPosition);
		LoadLine(cFile, fileSz, OriginalStartPosition, OriginalEndPosition);
		memset(g_Line, 0, 256);
		memcpy(&g_Line[0], cFile + OriginalStartPosition, OriginalEndPosition - OriginalStartPosition);

		//Revisar si hay mas MeshBones o salir
		do
		{
			LoadMeshBone(me, g_Line, cFile, fileSz, OriginalStartPosition, OriginalEndPosition);

			if (strstr(g_Line, "{"))
				openKeys++;
			if (strstr(g_Line, "}"))
				openKeys--;

			LoadLine(cFile, fileSz, OriginalStartPosition, OriginalEndPosition);
			memset(g_Line, 0, 256);
			memcpy(&g_Line[0], cFile + OriginalStartPosition, OriginalEndPosition - OriginalStartPosition);
		} while (openKeys > 0);
		return true;
	}
	return false;
}