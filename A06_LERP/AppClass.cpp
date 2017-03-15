#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Assignment  06 - LERP"); // Window Name
}

void AppClass::InitVariables(void)
{
	m_pCameraMngr->SetPositionTargetAndView(vector3(0.0f, 0.0f, 15.0f), ZERO_V3, REAXISY);

	// Color of the screen
	m_v4ClearColor = vector4(REBLACK, 1); // Set the clear color to black

	m_pMeshMngr->LoadModel("Sorted\\WallEye.bto", "WallEye");
	for (int i = 0; i < 11; i++) {
		//m_pMeshMngr->LoadModel("Sorted\\WallEye.bto", ("vertex" + i));
		m_pMeshMngr->InstanceSphere(0.1f, 6, vector3(1.0f, 0.0f, 0.0f), ("vertex" + i));
	}
	fDuration = 1.0f;
}

void AppClass::Update(void)
{
#pragma region Does not change anything here
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();
#pragma region

#pragma region Does not need changes but feel free to change anything here
	//Lets us know how much time has passed since the last call
	double fTimeSpan = m_pSystem->LapClock(); //Delta time (between frame calls)

	//cumulative time
	static double fRunTime = 0.0f; //How much time has passed since the program started
	fRunTime += fTimeSpan; 
#pragma endregion

#pragma region Your Code goes here
	//translation matrix and animation points
	matrix4 translateMatrix = IDENTITY_M4;
	vector3 animationVerteces[] = {
		vector3(-4.0f,-2.0f, 5.0f),
		vector3(1.0f,-2.0f, 5.0f),
		vector3(-3.0f,-1.0f, 3.0f),
		vector3(2.0f,-1.0f, 3.0f),
		vector3(-2.0f, 0.0f, 0.0f),
		vector3(3.0f, 0.0f, 0.0f),
		vector3(-1.0f, 1.0f,-3.0f),
		vector3(4.0f, 1.0f,-3.0f),
		vector3(0.0f, 2.0f,-5.0f),
		vector3(5.0f, 2.0f,-5.0f),
		vector3(1.0f, 3.0f,-5.0f)
	};
	float arraySize = sizeof(animationVerteces) / sizeof(vector3);

	//period of animation defined by duration between points * number of points
	float fPeriod = fDuration * arraySize;

	//current positionin period defined by current runtime % total period length
	float fCurrentPeriod = fmod(fRunTime, fPeriod);

	//find the points we're going to and where we came from
	int iNext = (int)(fCurrentPeriod / fDuration);
	int iPrev = (iNext <= 0) ? arraySize - 1 : iNext - 1;

	//find the inerpolated values from previous point to next point
	//use MapValue for each componenet
	//current distance between points defined as (run time + (error correction)) % (duration between points )
	float x = MapValue((float)fmod(fRunTime + (fTimeSpan/2), fDuration), 0.0f, fDuration, animationVerteces[iPrev].x, animationVerteces[iNext].x);
	float y = MapValue((float)fmod(fRunTime + (fTimeSpan/2), fDuration), 0.0f, fDuration, animationVerteces[iPrev].y, animationVerteces[iNext].y);
	float z = MapValue((float)fmod(fRunTime + (fTimeSpan/2), fDuration), 0.0f, fDuration, animationVerteces[iPrev].z, animationVerteces[iNext].z);
	translateMatrix = glm::translate(vector3(x, y, z)); //translate to current position

	//std::cout << "Period: " << fPeriod << " CurrentPeriod: " << fCurrentPeriod << " iNext: " << iNext << " fRunTime: " << fRunTime << std::endl;
	std::cout << "fDuration: " << fDuration << " sizeof: " << arraySize << " fPeriod " << fPeriod << std::endl;

	//translate the model to this position
	m_pMeshMngr->SetModelMatrix(translateMatrix, "WallEye");

	//add in spheres for each point
	for (int i = 0; i < 11; i++) {
		matrix4 addModel = IDENTITY_M4;
		addModel = glm::translate(animationVerteces[i]);
		m_pMeshMngr->SetModelMatrix(addModel, (("vertex" + i)));
	}
#pragma endregion

#pragma region Does not need changes but feel free to change anything here
	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();

	//Print info on the screen
	m_pMeshMngr->PrintLine("");
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
#pragma endregion
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();
	//Render the grid based on the camera's mode:
	m_pMeshMngr->AddGridToRenderListBasedOnCamera(m_pCameraMngr->GetCameraMode());
	m_pMeshMngr->Render(); //renders the render list
	m_pMeshMngr->ClearRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	super::Release(); //release the memory of the inherited fields
}