#include "backgroundComponent.h"
#include "GameEngine\GameEngineMain.h"

#include "GameEngine\EntitySystem\Components\SpriteRenderComponent.h"

#include <SFML/Window/Keyboard.hpp>

using namespace Game;


backgroundComponent::backgroundComponent()
	: m_lastFaceIndex(0)
	, m_wasFaceSwapButtonPressed(false)
{

}


backgroundComponent::~backgroundComponent()
{

}

void backgroundComponent::OnAddToWorld()
{
	__super::OnAddToWorld();
}


void backgroundComponent::Update()
{
	__super::Update();

}