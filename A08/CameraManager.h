#ifndef __CAMERAMANAGER_H_
#define __CAMERAMANAGER_H_

#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>

class Camera {
private:
Camera() {};
static Camera* instance;

Camera(Camera const& other) {};
Camera& operator=(Camera const& other) {};

vector3 m_vUp;
vector3 m_vPosition;
vector3 m_vTarget;

matrix4 m_mView;
quaternion m_qOrientation;

float pitch;
float roll;
float yaw;

void update();
~Camera() {}

public:
	//static Camera* GetInstance();
	static Camera* GetInstance() {
		if (instance == nullptr) {
			instance = new Camera();
		}
		return instance;
	}

static void ReleaseInstance() {
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}


glm::mat4 GetView(void);
glm::mat4 GetProjection(bool bOrthographic);

void SetPosition(vector3 v3Position);
void SetTarget(vector3 v3Target);
void SetUp(vector3 v3Up);

void MoveForward(float fIncrement);
void MoveSideways(float fIncrement);
void MoveVertical(float fIncrement);

void ChangePitch(float fIncrement);
void ChangeRoll(float fIncrement);
void ChangeYaw(float fIncrement);

};
//Camera* Camera::instance = nullptr;

#endif