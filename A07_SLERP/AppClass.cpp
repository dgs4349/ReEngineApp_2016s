#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("SLERP - Davis Smith"); // Window Name

	//Setting the color to black
	m_v4ClearColor = vector4(0.0f);
}

void AppClass::InitVariables(void)
{
	//Setting the position in which the camera is looking and its interest point
	m_pCameraMngr->SetPositionTargetAndView(vector3(12.12f, 28.52f, 11.34f), ZERO_V3, REAXISY);

	//Setting the color to black
	m_v4ClearColor = vector4(0.0f);

	//Loading the models
	m_pMeshMngr->LoadModel("Planets\\00_Sun.obj", "Sun");
	m_pMeshMngr->LoadModel("Planets\\03_Earth.obj", "Earth");
	m_pMeshMngr->LoadModel("Planets\\03A_Moon.obj", "Moon");

	m_pMeshMngr->LoadModel("Planets\\02_Venus.obj", "Venus");

	//Setting the days duration
	m_fDay = 1.0f;
}

void AppClass::Update(void)
{
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();

	//First person camera movement
	if (m_bFPC == true)
		CameraRotation();

	//Getting the time between calls
	double fCallTime = m_pSystem->LapClock();
	//Counting the cumulative time
	static double fRunTime = 0.0f;
	fRunTime += fCallTime;

	//Earth Orbit
	double fEarthHalfOrbTime = 182.5f * m_fDay; //Earths orbit around the sun lasts 365 days / half the time for 2 stops
	float fEarthHalfRevTime = 0.5f * m_fDay; // Move for Half a day
	float fMoonHalfOrbTime = 14.0f * m_fDay; //Moon's orbit is 28 earth days, so half the time for half a route
	float fVenusHalfOrbTime = 113.2 * m_fDay; //Venus orbit for half a revolution
	float fVenusHalfRevTime = -121.5 * m_fDay; //Venus for half a rotation

	//scaling matrices
	glm::mat4 m_m4Sun_scale = glm::scale(IDENTITY_M4, vector3(5.936f, 5.936f, 5.936f));
	glm::mat4 m_m4Earth_scale = glm::scale(IDENTITY_M4, vector3(0.524f, 0.524f, 0.524f));
	glm::mat4 m_m4Moon_scale = glm::scale(IDENTITY_M4, vector3(0.270f, 0.270f, 0.270f));
	glm::mat4 m_m4Venus_scale = glm::scale(IDENTITY_M4, vector3(0.497f, 0.497f, 0.497f));

	//translation matrices
	glm::mat4 m_m4Sun_translate = glm::translate(IDENTITY_M4, m_vSun_pos);
	glm::mat4 m_m4Earth_translate = glm::translate(IDENTITY_M4, vector3(11.0f, 0.0f, 0.0f));
	glm::mat4 m_m4Moon_translate = glm::translate(IDENTITY_M4, vector3(2.0f, 0.0f, 0.0f));
	glm::mat4 m_m4Venus_translate = glm::translate(IDENTITY_M4, vector3(7.92f, 0.0f, 0.0f));

	//orbit math and matrices
	glm::quat qEarthOrbit;
	if (fmod(fRunTime, (fEarthHalfOrbTime * 2)) < fEarthHalfOrbTime) {
		//if we're less than halfway through a total orbit, rotate from 0-PI
		qEarthOrbit = glm::mix(glm::quat(vector3(0.0f, 0.0f, 0.0f)),
			glm::quat(vector3(0.0f, PI, 0.0f)),
			(float)(fmod(fRunTime, fEarthHalfOrbTime) / fEarthHalfOrbTime));
	}
	else {
		//else rotate from -PI-0
		qEarthOrbit = glm::mix(glm::quat(vector3(0.0f, -PI, 0.0f)),
			glm::quat(vector3(0.0f, 0.0f, 0.0f)),
			(float)(fmod(fRunTime, fEarthHalfOrbTime) / fEarthHalfOrbTime));
	}

	glm::quat qMoonOrbit;
	if (fmod(fRunTime, (fMoonHalfOrbTime * 2)) < fMoonHalfOrbTime) {
		qMoonOrbit = glm::mix(glm::quat(vector3(0.0f, 0.0f, 0.0f)),
			glm::quat(vector3(0.0f, PI, 0.0f)),
			(float)(fmod(fRunTime, fMoonHalfOrbTime) / fMoonHalfOrbTime));
	}
	else {
		qMoonOrbit = glm::mix(glm::quat(vector3(0.0f, -PI, 0.0f)),
			glm::quat(vector3(0.0f, 0.0f, 0.0f)),
			(float)(fmod(fRunTime, fMoonHalfOrbTime) / fMoonHalfOrbTime));
	}

	glm::quat qVenusOrbit;
	if (fmod(fRunTime, (fVenusHalfOrbTime * 2)) < fVenusHalfOrbTime) {
		qVenusOrbit = glm::mix(glm::quat(vector3(0.0f, 0.0f, 0.0f)),
			glm::quat(vector3(0.0f, PI, 0.0f)),
			(float)(fmod(fRunTime, fVenusHalfOrbTime) / fVenusHalfOrbTime));
	}
	else {
		qVenusOrbit = glm::mix(glm::quat(vector3(0.0f, -PI, 0.0f)),
			glm::quat(vector3(0.0f, 0.0f, 0.0f)),
			(float)(fmod(fRunTime, fVenusHalfOrbTime) / fVenusHalfOrbTime));
	}


	glm::mat4 m_m4Earth_orbit = glm::mat4_cast(qEarthOrbit);
	glm::mat4 m_m4Moon_orbit = glm::mat4_cast(qMoonOrbit);
	glm::mat4 m_m4Venus_orbit = glm::mat4_cast(qVenusOrbit);

	//rotation math and matrices
	glm::quat qEarthRotation;
	if (fmod(fRunTime, (fEarthHalfRevTime * 2)) < fEarthHalfRevTime) {
		qEarthRotation = glm::mix(glm::quat(vector3(0.0f, 0.0f, 0.0f)),
			glm::quat(vector3(0.0f, PI, 0.0f)),
			(float)(fmod(fRunTime, fEarthHalfRevTime) / fEarthHalfRevTime));
	}
	else {
		qEarthRotation = glm::mix(glm::quat(vector3(0.0f, -PI, 0.0f)),
			glm::quat(vector3(0.0f, 0.0f, 0.0f)),
			(float)(fmod(fRunTime, fEarthHalfRevTime) / fEarthHalfRevTime));
	}
	glm::quat qVenusRotation;
	if (fmod(fRunTime, (fVenusHalfRevTime * 2)) < fVenusHalfRevTime) {
		qVenusRotation = glm::mix(glm::quat(vector3(0.0f, 0.0f, 0.0f)),
			glm::quat(vector3(0.0f, PI, 0.0f)),
			(float)(fmod(fRunTime, fVenusHalfRevTime) / fVenusHalfRevTime));
	}
	else {
		qVenusRotation = glm::mix(glm::quat(vector3(0.0f, -PI, 0.0f)),
			glm::quat(vector3(0.0f, 0.0f, 0.0f)),
			(float)(fmod(fRunTime, fVenusHalfRevTime) / fVenusHalfRevTime));
	}

	glm::mat4 m_m4Earth_rotation = glm::mat4_cast(qEarthRotation);
	glm::mat4 m_m4Venus_rotation = glm::mat4_cast(qVenusRotation);

	//finding the final transformations
	glm::mat4 m_m4Sun = m_m4Sun_translate * m_m4Sun_scale;
	glm::mat4 m_m4Earth = m_m4Sun_translate * m_m4Earth_orbit * m_m4Earth_translate * m_m4Earth_scale;
	glm::mat4 m_m4Moon = m_m4Earth * m_m4Moon_orbit * m_m4Moon_translate * m_m4Moon_scale;
	m_m4Earth *= m_m4Earth_rotation; //moon's transformations are based on all Earth's except for rotation

	glm::mat4 m_m4Venus = m_m4Sun_translate * m_m4Venus_orbit * m_m4Venus_translate * m_m4Venus_scale * m_m4Venus_rotation;

	m_pMeshMngr->SetModelMatrix(m_m4Sun, "Sun");
	m_pMeshMngr->SetModelMatrix(m_m4Earth, "Earth");
	m_pMeshMngr->SetModelMatrix(m_m4Moon, "Moon");
	m_pMeshMngr->SetModelMatrix(m_m4Venus, "Venus");


	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//had to remove static context for these to work correctly
	int nEarthOrbits = fRunTime / (fEarthHalfOrbTime * 2.0f);
	int nEarthRevolutions = fRunTime / (fEarthHalfRevTime * 2.0f);
	int nMoonOrbits = fRunTime / (fMoonHalfOrbTime * 2.0f);
	int nVenusOrbits = fRunTime / (fVenusHalfOrbTime * 2.0f);
	int nVenusRevolutions = fRunTime / (fVenusHalfRevTime * 2.0f);

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();

	//Print info on the screen
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	
	m_pMeshMngr->Print("Time:");
	m_pMeshMngr->PrintLine(std::to_string(fRunTime));

	m_pMeshMngr->Print("Day:");
	m_pMeshMngr->PrintLine(std::to_string(m_fDay));

	m_pMeshMngr->Print("E_Orbits:");
	m_pMeshMngr->PrintLine(std::to_string(nEarthOrbits));

	m_pMeshMngr->Print("E_Revolutions:");
	m_pMeshMngr->PrintLine(std::to_string(nEarthRevolutions));

	m_pMeshMngr->Print("M_Orbits:");
	m_pMeshMngr->PrintLine(std::to_string(nMoonOrbits));

	m_pMeshMngr->Print("V_Orbits:");
	m_pMeshMngr->PrintLine(std::to_string(nVenusOrbits));

	m_pMeshMngr->Print("V_Revolutions:");
	m_pMeshMngr->PrintLine(std::to_string(nVenusRevolutions));

	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();

	//Render the grid based on the camera's mode:
	switch (m_pCameraMngr->GetCameraMode())
	{
	default:
		break;
	case CAMERAMODE::CAMROTHOX:
		m_pMeshMngr->AddGridToRenderList(1.0f, REAXIS::YZ, RERED * 0.75f); //renders the YZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOY:
		m_pMeshMngr->AddGridToRenderList(1.0f, REAXIS::XZ, REGREEN * 0.75f); //renders the XZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOZ:
		m_pMeshMngr->AddGridToRenderList(1.0f, REAXIS::XY, REBLUE * 0.75f); //renders the XY grid with a 100% scale
		break;
	}
	
	m_pMeshMngr->Render(); //renders the render list
	m_pMeshMngr->ClearRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	super::Release(); //release the memory of the inherited fields
}