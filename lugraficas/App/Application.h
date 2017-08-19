#include <core/Core.h>

#include <scene/PrimitiveManager.h>
#include <scene/PrimitiveInstance.h>
#include <scene/SceneProp.h>

#include <CMatrix4D.h>
#include <utils/Camera.h>
#include <utils/Timer.h>

#include <SDL\SDL_mouse.h>

enum
{
	DRAW_CUBE_SPINNING = 0,
	DRAW_CUBE_BIG,
	DRAW_MESH,
	DRAW_ALL,
};

class App : public AppBase
{
public:
	App() : AppBase() {}
	void InitVars();
	void CreateAssets();
	void DestroyAssets();

	void OnUpdate();
	void OnDraw();
	void OnInput();

	void OnPause();
	void OnResume();

	void OnReset();

	PrimitiveManager PrimitiveMgr;
	PrimitiveInst	Cubes[10];
	PrimitiveInst	Triangles[10];
	PrimitiveInst   Pigs[10];
	PrimitiveInst	QuadInst;

	PrimitiveInst	Quads[10];


	Camera			Cam;
	Camera			LightCam;

	Camera			*ActiveCam;

	CMatrix4D		View;
	CMatrix4D		Projection;
	CMatrix4D		VP;

	SceneProps		SceneProp;

	bool			FirstFrame;
	Timer			DtTimer;
	float			DtSecs;
	int				SelectedMesh;
	int				RTIndex;

	int				QuadIndex;

	int				GBufferPass;
	int				DeferredPass;
	int				DepthPass;
	int				ShadowAccumPass;
	int				HorizontalBlurPass;
	int				BloomAccumPass;
	int				VerticalBlurPass;
};