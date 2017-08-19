#include "Application.h"
#include <video/BaseDriver.h>
#include <utils/InputManager.h>
#include <scene/Cube.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define AXIS_MAX_VALUE 32767.0f

#define DEGENERATED_FBO_TEST 0

#define NUM_LIGHTS 4
#define RADI 60.0f

#if defined(OS_LINUX)
#include <sys/time.h>
#endif

#include <iostream>
#include <string>
#include <vector>

extern std::vector<std::string> g_args;

void App::InitVars()
{
	DtTimer.Init();
	DtTimer.Update();
	srand((unsigned int)DtTimer.GetDTSecs());

	Cam.Init(CVector4D(10.0f, 10.0f, -50.0f, 1.0f), 80.0f*Deg2Rad, 1280.0f / 720.0f, 1.0f, 8000.0f);
	Cam.Update();

	LightCam.Init(CVector4D(0.0f, 30.0f, -45.0f, 1.0f), 80.0f*Deg2Rad, 1.0f, 0.1f, 8000.0f);
	LightCam.m_fYaw = PI;
	LightCam.m_fPitch = PI;
	LightCam.m_fRoll = 0.0f;
	LightCam.Update();

	ActiveCam = &Cam;

	SceneProp.AddCamera(ActiveCam);
	SceneProp.AddLightCamera(&LightCam);

	for (int i = 0; i < NUM_LIGHTS; i++)
	{
		float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		SceneProp.AddLight(CVector4D(0.0f, 0.0f, 0.0f, 1.0f), CVector4D(r, g, b, 1.0f), true);
	}

	SceneProp.ActiveLights = 127;
	SceneProp.AmbientColor = CVector4D(0.15f, 0.15f, 0.15f, 1.0f);

	RTIndex = -1;
	FirstFrame = true;

}

void App::CreateAssets()
{
	GBufferPass = pFramework->pVideoDriver->CreateRT(4, BaseRT::RGBA8, BaseRT::F32, 0, 0);
	DeferredPass = pFramework->pVideoDriver->CreateRT(1, BaseRT::RGBA8, BaseRT::F32, 0, 0);
	DepthPass = pFramework->pVideoDriver->CreateRT(0, BaseRT::NOTHING, BaseRT::F32, 1024, 1024);	
	ShadowAccumPass = pFramework->pVideoDriver->CreateRT(1, BaseRT::RGBA8, BaseRT::F32, 0, 0);
	HorizontalBlurPass = pFramework->pVideoDriver->CreateRT(1, BaseRT::RGBA8, BaseRT::F32, 0, 0);
	BloomAccumPass = pFramework->pVideoDriver->CreateRT(1, BaseRT::RGBA8, BaseRT::F32, 0, 0);
	VerticalBlurPass = pFramework->pVideoDriver->CreateRT(1, BaseRT::RGBA8, BaseRT::F32, 0, 0);

	PrimitiveMgr.SetVP(&VP);

	int index;

	index = PrimitiveMgr.CreateMesh("Models/Scene.X");
	Pigs[0].CreateInstance(PrimitiveMgr.GetPrimitive(index), &VP);
	Pigs[0].Update();

	index = PrimitiveMgr.CreateMesh("Models/NuCroc.X");
	Pigs[1].CreateInstance(PrimitiveMgr.GetPrimitive(index), &VP);
	Pigs[1].TranslateAbsolute(-20.0f, 0.0f, 15.0f);
	Pigs[1].RotateXAbsolute(0.0f);
	Pigs[1].RotateYAbsolute(0.0f);
	Pigs[1].RotateXAbsolute(0.0f);
	Pigs[1].ScaleAbsolute(0.15f);
	Pigs[1].Update();

    index = PrimitiveMgr.CreateMesh("Models/NuBatman.X");
	Pigs[2].CreateInstance(PrimitiveMgr.GetPrimitive(index), &VP);
	Pigs[2].TranslateAbsolute(0.0f, 0.0f, 0.0f);
	Pigs[2].RotateXAbsolute(0.0f);
	Pigs[2].RotateYAbsolute(0.0f);
	Pigs[2].RotateXAbsolute(0.0f);
	Pigs[2].ScaleAbsolute(0.15f);
	Pigs[2].Update();

	index = PrimitiveMgr.CreateMesh("Models/NuVenomJok.X");
	Pigs[3].CreateInstance(PrimitiveMgr.GetPrimitive(index), &VP);
	Pigs[3].TranslateAbsolute(20.0f, 0.0f, 35.0f);
	Pigs[3].RotateXAbsolute(0.0f);
	Pigs[3].RotateYAbsolute(0.0f);
	Pigs[3].RotateXAbsolute(0.0f);
	Pigs[3].ScaleAbsolute(0.15f);
	Pigs[3].Update();

	Pigs[4].CreateInstance(PrimitiveMgr.GetPrimitive(index), &VP);
	Pigs[4].TranslateAbsolute(0.0f, 0.0f, 35.0f);
	Pigs[4].ScaleAbsolute(0.2f);
	Pigs[4].Update();

	

	//Quads
	{
		QuadIndex = PrimitiveMgr.CreateQuad();
		Quads[0].CreateInstance(PrimitiveMgr.GetPrimitive(QuadIndex), &VP);
		PrimitiveMgr.GetPrimitive(QuadIndex)->SetTexture(pFramework->pVideoDriver->RTs[0]->vColorTextures[0], 0);
		PrimitiveMgr.GetPrimitive(QuadIndex)->SetTexture(pFramework->pVideoDriver->RTs[0]->vColorTextures[1], 1);
		PrimitiveMgr.GetPrimitive(QuadIndex)->SetTexture(pFramework->pVideoDriver->RTs[0]->vColorTextures[2], 2);
		PrimitiveMgr.GetPrimitive(QuadIndex)->SetTexture(pFramework->pVideoDriver->RTs[0]->vColorTextures[3], 3);
		PrimitiveMgr.GetPrimitive(QuadIndex)->SetTexture(pFramework->pVideoDriver->RTs[0]->pDepthTexture, 4);


		Quads[1].CreateInstance(PrimitiveMgr.GetPrimitive(QuadIndex), &VP);
		Quads[2].CreateInstance(PrimitiveMgr.GetPrimitive(QuadIndex), &VP);
		Quads[3].CreateInstance(PrimitiveMgr.GetPrimitive(QuadIndex), &VP);
		Quads[4].CreateInstance(PrimitiveMgr.GetPrimitive(QuadIndex), &VP);
		Quads[5].CreateInstance(PrimitiveMgr.GetPrimitive(QuadIndex), &VP);
		Quads[6].CreateInstance(PrimitiveMgr.GetPrimitive(QuadIndex), &VP);
		Quads[7].CreateInstance(PrimitiveMgr.GetPrimitive(QuadIndex), &VP);

		Quads[0].TranslateAbsolute(0.0f, 0.0f, 0.0f);
		Quads[0].Update();
		Quads[1].ScaleAbsolute(0.25f);
		Quads[1].TranslateAbsolute(-0.75f, +0.75f, 0.0f);
		Quads[1].Update();
		Quads[2].ScaleAbsolute(0.25f);
		Quads[2].TranslateAbsolute(0.75f, +0.75f, 0.0f);
		Quads[2].Update();
		Quads[3].ScaleAbsolute(0.25f);
		Quads[3].TranslateAbsolute(-0.75f, -0.75f, 0.0f);
		Quads[3].Update();
		Quads[4].ScaleAbsolute(0.25f);
		Quads[4].TranslateAbsolute(0.75f, -0.75f, 0.0f);
		Quads[4].Update();
		Quads[5].ScaleAbsolute(0.25f);
		Quads[5].TranslateAbsolute(0.75f, 0.0f, 0.0f);
		Quads[5].Update();
		Quads[6].ScaleAbsolute(0.25f);
		Quads[6].TranslateAbsolute(-0.75f, 0.0f, 0.0f);
		Quads[6].Update();
		Quads[7].ScaleAbsolute(1.0f);
		Quads[7].TranslateAbsolute(0.0f, 0.0f, 0.1f);
		Quads[7].Update();

	}

	PrimitiveMgr.SetSceneProps(&SceneProp);

	for (unsigned int i = 0; i < g_args.size(); i++)
	{
        if(g_args[i] == "-l")
           SceneProp.ActiveLights = atoi( g_args[i+1].c_str() );
	}
}

void App::DestroyAssets()
{
	PrimitiveMgr.DestroyPrimitives();
}

void App::OnUpdate()
{
#if defined(OS_LINUX)
	timeval start;
    gettimeofday(&start,0);
#endif

	DtTimer.Update();
	DtSecs = DtTimer.GetDTSecs();

	OnInput();

	ActiveCam->Update();
	VP = ActiveCam->VP;

	//Luces
	{
		float speed = 0.3f;
		static float freq = 0.0f;
		freq += DtSecs*speed;

		float offoseto = (360.0f / NUM_LIGHTS)*Deg2Rad;
		float dist = RADI;

		float ligposX, ligposZ;

		int randomVar = 1;

		for (int i = 0; i < NUM_LIGHTS; i++)
		{
			ligposX = sinf(i*offoseto*freq)*dist * 1.0f / randomVar;
			ligposZ = cosf(i*offoseto*freq)*dist * 1.0f / randomVar;

			randomVar++;
			if (randomVar > 4)
				randomVar = 1;

			SceneProp.Lights[i].Position.x = ligposX;
			SceneProp.Lights[i].Position.z = ligposZ;
		}
	}

	OnDraw();

}

void App::OnDraw()
{
	static int DronePass = 0;

	if (DronePass <= 0)
		pFramework->pVideoDriver->Clear();

	ActiveCam = &Cam;

	pFramework->pVideoDriver->PushRT(DepthPass);
	SceneProp.pCameras[0] = &LightCam;

	for (int i = 0; i < 5; i++)
	{
		Pigs[i].SetSignature(Signature::SHADOW_MAP_PASS);
		Pigs[i].Draw();
		Pigs[i].SetSignature(Signature::FORWARD_PASS);
	}

	pFramework->pVideoDriver->PopRT();

	SceneProp.pCameras[0] = ActiveCam;

	pFramework->pVideoDriver->PushRT(GBufferPass);

	for (int i = 0; i < 5; i++)
	{
		Pigs[i].SetSignature(Signature::GBUFF_PASS);
		Pigs[i].Draw();
		Pigs[i].SetSignature(Signature::FORWARD_PASS);
	}

	pFramework->pVideoDriver->PopRT();

	pFramework->pVideoDriver->PushRT(ShadowAccumPass);
	//pFramework->pVideoDriver->Clear();
	PrimitiveMgr.GetPrimitive(QuadIndex)->SetTexture(pFramework->pVideoDriver->GetRTTexture(GBufferPass, BaseDriver::DEPTH_ATTACHMENT), 0);
	PrimitiveMgr.GetPrimitive(QuadIndex)->SetTexture(pFramework->pVideoDriver->GetRTTexture(DepthPass, BaseDriver::DEPTH_ATTACHMENT), 1);
	Quads[0].SetSignature(Signature::SHADOW_COMP_PASS);
	Quads[0].Draw();
	pFramework->pVideoDriver->PopRT();

	pFramework->pVideoDriver->PushRT(DeferredPass);
	PrimitiveMgr.GetPrimitive(QuadIndex)->SetTexture(pFramework->pVideoDriver->GetRTTexture(GBufferPass, BaseDriver::COLOR0_ATTACHMENT), 0);
	PrimitiveMgr.GetPrimitive(QuadIndex)->SetTexture(pFramework->pVideoDriver->GetRTTexture(GBufferPass, BaseDriver::COLOR1_ATTACHMENT), 1);
	PrimitiveMgr.GetPrimitive(QuadIndex)->SetTexture(pFramework->pVideoDriver->GetRTTexture(GBufferPass, BaseDriver::COLOR2_ATTACHMENT), 2);
	PrimitiveMgr.GetPrimitive(QuadIndex)->SetTexture(pFramework->pVideoDriver->GetRTTexture(GBufferPass, BaseDriver::COLOR3_ATTACHMENT), 3);
	PrimitiveMgr.GetPrimitive(QuadIndex)->SetTexture(pFramework->pVideoDriver->GetRTTexture(GBufferPass, BaseDriver::DEPTH_ATTACHMENT), 4);
	PrimitiveMgr.GetPrimitive(QuadIndex)->SetTexture(pFramework->pVideoDriver->GetRTTexture(ShadowAccumPass, BaseDriver::COLOR0_ATTACHMENT), 5);
	Quads[0].SetSignature(Signature::DEFERRED_PASS);
	Quads[0].Draw();
	pFramework->pVideoDriver->PopRT();

	pFramework->pVideoDriver->PushRT(BloomAccumPass);
	PrimitiveMgr.GetPrimitive(QuadIndex)->SetTexture(pFramework->pVideoDriver->GetRTTexture(DeferredPass, BaseDriver::COLOR0_ATTACHMENT), 0);
	Quads[0].SetSignature(Signature::BRIGHT_PASS);
	Quads[0].Draw();

	pFramework->pVideoDriver->PopRT();

	pFramework->pVideoDriver->PushRT(HorizontalBlurPass);
	PrimitiveMgr.GetPrimitive(QuadIndex)->SetTexture(pFramework->pVideoDriver->GetRTTexture(BloomAccumPass, BaseDriver::COLOR0_ATTACHMENT), 0);
	Quads[0].SetSignature(Signature::HORIZONTAL_BLUR_PASS);
	Quads[0].Draw();

	pFramework->pVideoDriver->PopRT();

	pFramework->pVideoDriver->PushRT(VerticalBlurPass);
	PrimitiveMgr.GetPrimitive(QuadIndex)->SetTexture(pFramework->pVideoDriver->GetRTTexture(HorizontalBlurPass, BaseDriver::COLOR0_ATTACHMENT), 0);
	Quads[0].SetSignature(Signature::VERTICAL_BLUR_PASS);
	Quads[0].Draw();

	pFramework->pVideoDriver->PopRT();
	pFramework->pVideoDriver->Clear();
	
	PrimitiveMgr.GetPrimitive(QuadIndex)->SetTexture(pFramework->pVideoDriver->GetRTTexture(BloomAccumPass, BaseDriver::COLOR0_ATTACHMENT), 0);
	Quads[2].SetSignature(Signature::FSQUAD_1_TEX);
	Quads[2].Draw();
	PrimitiveMgr.GetPrimitive(QuadIndex)->SetTexture(pFramework->pVideoDriver->GetRTTexture(DeferredPass, BaseDriver::COLOR0_ATTACHMENT), 0);
	Quads[1].SetSignature(Signature::FSQUAD_1_TEX);
	Quads[1].Draw();

	PrimitiveMgr.GetPrimitive(QuadIndex)->SetTexture(pFramework->pVideoDriver->GetRTTexture(DeferredPass, BaseDriver::COLOR0_ATTACHMENT), 0);
	PrimitiveMgr.GetPrimitive(QuadIndex)->SetTexture(pFramework->pVideoDriver->GetRTTexture(VerticalBlurPass, BaseDriver::COLOR0_ATTACHMENT), 1);
	Quads[3].SetSignature(Signature::FSQUAD_2_TEX);
	Quads[3].Draw();

	PrimitiveMgr.GetPrimitive(QuadIndex)->SetTexture(pFramework->pVideoDriver->GetRTTexture(DeferredPass, BaseDriver::COLOR0_ATTACHMENT), 0);
	PrimitiveMgr.GetPrimitive(QuadIndex)->SetTexture(pFramework->pVideoDriver->GetRTTexture(VerticalBlurPass, BaseDriver::COLOR0_ATTACHMENT), 1);
	Quads[0].SetSignature(Signature::HDR_COMP_PASS);
	Quads[0].Draw();
	pFramework->pVideoDriver->SwapBuffers();


	FirstFrame = false;
}

void App::OnInput()
{
	if (FirstFrame)
		return;

	const float speedFactor = 10.0f;

	int x, y;
	SDL_GetMouseState(&x, &y);

	if (x <= 3)
		SDL_WarpMouse(1276, y);
	else if (x >= 1277)
		SDL_WarpMouse(4, y);

	float rotX = ((y / 720.0f) - 0.5f)*3.14f;
	float rotY = (((x * 2) / 1280.0f) - 1.0f)*3.14f;

	ActiveCam->SetRotation(-rotX, -rotY, 0);

	if (IManager.PressedOnceKey(SDLK_KP_PLUS))
		SceneProp.ActiveLights *= 2;

	if (IManager.PressedOnceKey(SDLK_KP_MINUS))
	{
		SceneProp.ActiveLights *= 0.5f;

		if(SceneProp.ActiveLights <= 0)
			SceneProp.ActiveLights = 1;
	}

	if (IManager.PressedOnceKey(SDLK_c))
	{
		if (ActiveCam == (&Cam))
			ActiveCam = &LightCam;
		else
			ActiveCam = &Cam;

		SceneProp.pCameras[0] = ActiveCam;
	}

	static float CamSpeed = .02f;

	if (IManager.PressedKey(SDLK_w))
		ActiveCam->Move(CamSpeed, 0.0f, 0.0f);
	if (IManager.PressedKey(SDLK_s))
		ActiveCam->Move(-CamSpeed, 0.0f, 0.0f);

	if (IManager.PressedKey(SDLK_a))
		ActiveCam->Move(0.0f, 0.0f, -CamSpeed);
	if (IManager.PressedKey(SDLK_d))
		ActiveCam->Move(0.0f, 0.0f, CamSpeed);

	if (IManager.PressedKey(SDLK_z))
		ActiveCam->Move(0.0f, CamSpeed, 0.0f);
	if (IManager.PressedKey(SDLK_x))
		ActiveCam->Move(0.0f, -CamSpeed, 0.0f);
}

void App::OnPause()
{

}

void App::OnResume()
{

}

void App::OnReset()
{

}