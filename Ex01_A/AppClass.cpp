#include "AppClass.h"
void AppClass::Update(void)
{
#pragma region DOES NOT NEED CHANGES
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();
	static float fTimer = 0.0f;//creates a timer
	static uint uClock = m_pSystem->GenClock();//ask the system for a new clock id
	float fDeltaTime = m_pSystem->LapClock(uClock);//lap the selected clock
	float fAnimTime = 2.0f;
	float fHalfAnimTime = fAnimTime / 2.0f;
	fTimer += fDeltaTime;//add the delta time to the current clock
#pragma endregion

#pragma region YOUR CODE GOES HERE
	modelMatrix = IDENTITY_M4;

	//transformation variables
	glm::quat quatRotation;
	glm::mat4 mat4Translation;

	//set translation
	if (fmod(fTimer, fAnimTime*2.0f) < fAnimTime) {
		float y = MapValue(fmod(fTimer, fAnimTime), 0.0f, fAnimTime, 0.0f, 3.0f);
		mat4Translation = glm::translate(IDENTITY_M4, vector3(0.0f, y, 0.0f));
	}
	else {
		float y = MapValue(fmod(fTimer, fAnimTime), 0.0f, fAnimTime, 3.0f, 0.0f);
		mat4Translation = glm::translate(IDENTITY_M4, vector3(0.0f, y, 0.0f));
	}

	//set rotation
	if (fmod(fTimer, fAnimTime) < fHalfAnimTime) {
		quatRotation = glm::mix(glm::quat(vector3(0.0f, 0.0f, 0.0f)),
			glm::quat(vector3(0.0f, 0.0f, PI)),
			fmod(fTimer, fHalfAnimTime) / fHalfAnimTime);
	}
	else {
		quatRotation = glm::mix(glm::quat(vector3(0.0f, 0.0f, -PI)),
			glm::quat(vector3(0.0f, 0.0f, 0.0f)),
			fmod(fTimer, fHalfAnimTime) / fHalfAnimTime);
	}

	//apply transformations
	modelMatrix = mat4Translation * glm::mat4_cast(quatRotation) * modelMatrix;


#pragma endregion

#pragma region DOES NOT NEED CHANGES
	m_pMeshMngr->SetModelMatrix(modelMatrix, 0);//Set the model matrix to the model

	m_pMeshMngr->AddSkyboxToRenderList();//Adds a skybox to the renderlist
	m_pMeshMngr->AddInstanceToRenderList("ALL"); //Adds all loaded instances to the render list

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();

	//Print info on the screen
	m_pMeshMngr->PrintLine("\n" + m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->PrintLine("Timer: ");
	m_pMeshMngr->PrintLine(std::to_string(fTimer), REGREEN);

	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
#pragma endregion
}

