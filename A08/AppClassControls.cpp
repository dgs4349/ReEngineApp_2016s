#include "AppClass.h"
void AppClass::ProcessKeyboard(void)
{
	//Flag for the modifier
	bool bModifier = false;

	//ON PRESS/RELEASE
#pragma region ON PRESS/RELEASE DEFINITION
	static bool	bLastF1 = false, bLastF2 = false, bLastF3 = false, bLastF4 = false, bLastF5 = false,
				bLastF6 = false, bLastF7 = false, bLastF8 = false, bLastF9 = false, bLastF10 = false,
				bLastEscape = false;
#define ON_KEY_PRESS_RELEASE(key, pressed_action, released_action){  \
			bool pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::key);			\
			if(pressed){											\
				if(!bLast##key) pressed_action;}/*Just pressed? */\
			else if(bLast##key) released_action;/*Just released?*/\
			bLast##key = pressed; } //remember the state
#pragma endregion

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
		bModifier = true;

	//F1 Controllers
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
	{
		m_m4Projection = m_cCamera->GetProjection(false);
	}

	//F2 Controllers
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2))
	{
		m_m4Projection = m_cCamera->GetProjection(true);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F3)) {
		m_cCamera->SetUp(vector3(0.0f, 1.0f, 0.0f));
		m_cCamera->SetPosition(vector3(0.0f, 0.0f, 0.0f));
		m_cCamera->SetTarget(vector3(0.0f, 0.0f, -14.0f));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		m_cCamera->MoveForward(0.1f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		m_cCamera->MoveForward(-0.1f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		m_cCamera->MoveSideways(0.1f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		m_cCamera->MoveSideways(-0.1f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
		m_cCamera->MoveVertical(0.1f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
		m_cCamera->MoveVertical(-0.1f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
		m_cCamera->ChangePitch((bModifier) ? -0.01f : 0.01f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
		m_cCamera->ChangeYaw((bModifier) ? -0.01f : 0.01f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
		m_cCamera->ChangeRoll((bModifier) ? -0.01f : 0.01f);
	}


	//Exit the program
#pragma region Other Actions
	ON_KEY_PRESS_RELEASE(Escape, NULL, PostMessage(m_pWindow->GetHandler(), WM_QUIT, NULL, NULL))
#pragma endregion
}