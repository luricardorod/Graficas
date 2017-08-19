#include <video/GLShader.h>
#include <scene/GLQuad.h>
#include <utils/Utils.h>

void GLQuad::Create()
{
	SigBase = Signature::HAS_TEXCOORDS0;
	unsigned int Dest;
	char *vsSourceP = file2string("Shaders/VS_Quad.glsl");
	char *fsSourceP = file2string("Shaders/FS_Quad.glsl");

	std::string vstr = std::string(vsSourceP);
	std::string fstr = std::string(fsSourceP);

	free(vsSourceP);
	free(fsSourceP);

	g_pBaseDriver->CreateShader(vstr, fstr, SigBase);

	Dest = SigBase | Signature::DEFERRED_PASS;
	g_pBaseDriver->CreateShader(vstr, fstr, Dest);

	Dest = SigBase | Signature::FSQUAD_1_TEX;
	g_pBaseDriver->CreateShader(vstr, fstr, Dest);

	Dest = SigBase | Signature::FSQUAD_2_TEX;
	g_pBaseDriver->CreateShader(vstr, fstr, Dest);

	Dest = SigBase | Signature::FSQUAD_3_TEX;
	g_pBaseDriver->CreateShader(vstr, fstr, Dest);

	vertices[0] = { -1.0f,  1.0f, 0.0f, 1.0f,  0.0f, 0.0f };
	vertices[1] = { -1.0f, -1.0f, 0.0f, 1.0f,  0.0f, 1.0f };
	vertices[2] = {  1.0f, -1.0f, 0.0f, 1.0f,  1.0f, 1.0f };
	vertices[3] = {  1.0f,  1.0f, 0.0f, 1.0f,  1.0f, 0.0f };

	indices[0] = 2;
	indices[1] = 1;
	indices[2] = 0;
	indices[3] = 3;
	indices[4] = 2;
	indices[5] = 0;

	glGenBuffers(1, &VB);
	glBindBuffer(GL_ARRAY_BUFFER, VB);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vert), &vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &IB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned short), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	transform = transform.Identity();
}

void GLQuad::Transform(CMatrix4D * t)
{
	transform = *t;
}

void GLQuad::Draw(CMatrix4D * t, CMatrix4D * vp)
{
	if (t)
		transform = *t;

	unsigned int sig = SigBase;
	sig |= gSig;
	GLShader * s = dynamic_cast<GLShader*>(g_pBaseDriver->GetShaderSig(sig));

	Camera *pActualCamera = pScProp->pCameras[0];
	CMatrix4D VP = pActualCamera->VP;
	CMatrix4D WV = pActualCamera->View;
	CMatrix4D WVPInverse;
	//VP.Inverse(&WVPInverse);
	WVPInverse = VP.Inverse();
	CVector4D CameraPos = pActualCamera->Eye;

	unsigned int numLights = pScProp->ActiveLights;
	if (numLights >= pScProp->Lights.size())
		numLights = pScProp->Lights.size();

	CVector4D CameraInfo = CVector4D(pActualCamera->NPlane, pActualCamera->FPlane, pActualCamera->Fov, float(numLights));

	for (unsigned int i = 0; i < numLights; i++)
	{
		LightPositions[i] = pScProp->Lights[i].Position;
		LightColors[i] = pScProp->Lights[i].Color;
	}

	glUseProgram(s->ShaderProg);

	glUniformMatrix4fv(s->matWorldUniformLoc, 1, GL_FALSE, &transform.m[0][0]);
	glUniformMatrix4fv(s->matWorldViewProjUniformLoc, 1, GL_FALSE, &transform.m[0][0]);
	glUniformMatrix4fv(s->matWorldViewUniformLoc, 1, GL_FALSE, &WV.m[0][0]);
	glUniformMatrix4fv(s->matWVPInverseUniformLoc, 1, GL_FALSE, &WVPInverse.m[0][0]);

	glUniform4fv(s->CameraPos_Loc, 1, &CameraPos.v[0]);
	glUniform4fv(s->CameraInfo_Loc, 1, &CameraInfo.v[0]);

	glUniform4fv(s->LightPositions_Loc, numLights, &LightPositions[0].v[0]);
	glUniform4fv(s->LightColors_Loc, numLights, &LightColors[0].v[0]);

	glBindBuffer(GL_ARRAY_BUFFER, VB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);

	glEnableVertexAttribArray(s->vertexAttribLoc);
	glVertexAttribPointer(s->vertexAttribLoc, 4, GL_FLOAT, GL_FALSE, sizeof(Vert), BUFFER_OFFSET(0));
	glEnableVertexAttribArray(s->uvAttribLoc);
	glVertexAttribPointer(s->uvAttribLoc, 2, GL_FLOAT, GL_FALSE, sizeof(Vert), BUFFER_OFFSET(16));

	if (sig & Signature::DEFERRED_PASS)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Textures[0]->id);
		glUniform1i(s->tex0_loc, 0);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, Textures[1]->id);
		glUniform1i(s->tex1_loc, 1);

		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, Textures[2]->id);
		glUniform1i(s->tex2_loc, 2);

		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, Textures[3]->id);
		glUniform1i(s->tex3_loc, 3);

		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, Textures[4]->id);
		glUniform1i(s->tex4_loc, 4);
	}
	else if (sig & Signature::FSQUAD_1_TEX)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Textures[0]->id);
		glUniform1i(s->tex0_loc, 0);
	}
	else if (sig & Signature::FSQUAD_2_TEX)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Textures[0]->id);
		glUniform1i(s->tex0_loc, 0);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, Textures[1]->id);
		glUniform1i(s->tex1_loc, 1);
	}
	else if (sig & Signature::FSQUAD_3_TEX)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Textures[0]->id);
		glUniform1i(s->tex0_loc, 0);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, Textures[1]->id);
		glUniform1i(s->tex1_loc, 1);

		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, Textures[2]->id);
		glUniform1i(s->tex2_loc, 2);
	}
	else
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Textures[0]->id);
		glUniform1i(s->tex0_loc, 0);
	}

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
}

void GLQuad::Destroy()
{

}