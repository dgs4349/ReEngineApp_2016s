#include "CameraManager.h"

Camera* Camera::instance = nullptr;
/*
Camera* Camera::GetInstance() {
	static Camera* instance = &Camera();
	return instance;
}
*/

void Camera::SetUp(vector3 v3Up) {
	m_vUp = v3Up;
	m_vPosition = vector3(0.0f, 0.0f, 0.0f);
	m_vTarget = vector3(0.0f, 0.0f, 0.0f);
	m_qOrientation = glm::quat(vector3(0.0f, 0.0f, 0.0f));
	pitch = 0;
	yaw = 0;
	roll = 0;
}

void Camera::update() {
	m_qOrientation = glm::quat(vector3(pitch, roll, yaw));
	m_mView = glm::translate(IDENTITY_M4, m_vPosition);
	m_mView = glm::mat4_cast(m_qOrientation) * m_mView;
}

glm::mat4 Camera::GetView(void) {
	return m_mView;
}

glm::mat4 Camera::GetProjection(bool bOrthographic) {
	if (bOrthographic) return glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.01f, 1000.0f);
	return glm::perspective(45.0f, 4.0f / 2.5f, 0.01f, 1000.0f);
}

void Camera::SetPosition(vector3 v3Position) {
	m_vPosition = v3Position;
	update();
}

void Camera::SetTarget(vector3 v3Target) {
	m_vTarget = v3Target;
	m_mView = glm::lookAt(m_vPosition, m_vTarget, m_vUp);
	update();
}

void Camera::MoveForward(float fIncrement) {
	m_vPosition.z += fIncrement;
	update();
}

void Camera::MoveSideways(float fIncrement) {
	m_vPosition.x += fIncrement;
	update();
}

void Camera::MoveVertical(float fIncrement) {
	m_vPosition.y += fIncrement;
	update();
}

void Camera::ChangePitch(float fIncrement) {
	pitch += fIncrement;
	//m_qOrientation = glm::angleAxis(pitch, vector3(1.0f, 0.0f, 0.0f));
	update();
}

void Camera::ChangeRoll(float fIncrement) {
	roll += fIncrement;
	//m_qOrientation = glm::angleAxis(roll, vector3(0.0f, 0.0f, 1.0f));
	update();
}

void Camera::ChangeYaw(float fIncrement) {
	yaw += fIncrement;

	//m_qOrientation = glm::angleAxis(yaw, vector3(0.0f, 1.0f, 0.0f));
	update();
}