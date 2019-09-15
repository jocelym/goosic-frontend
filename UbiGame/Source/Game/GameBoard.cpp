#include "GameBoard.h"
#include <array>
#include <chrono>

#include "GameEngine\GameEngineMain.h"
#include "Game\Components\PlayermovementComponent.h"
#include "GameEngine\EntitySystem\Components\SpriteRenderComponent.h"
#include "GameEngine\Util\SoundManager.h"
#include <GameEngine\EntitySystem\Components\SoundComponent.h>
#include <iostream>


using namespace GameEngine;

using namespace Game;

static int point = 0;
static int nextIndex = 0;
static int data[] = { 0, 100, 200 , 500, 750, 1005, 1600, 2000};
static int column[] = { 1, 3, 2 , 1, 2, 3, 2, 1, 1, 2, 3, 1};
static bool a_pressed = true;
static bool s_pressed = true;
static bool d_pressed = true;
static std::vector<Entity> dots;

GameBoard::GameBoard()
	
	: m_player(nullptr)
	{
		CreatePlayer(0, 0);
	}


GameBoard::~GameBoard()
{

}

void GameBoard::Update()
{
	auto t1 = std::chrono::high_resolution_clock::now();
	if (point >= data[nextIndex] && point <= data[nextIndex] + 1900) {

		CreatePlayer(140 * column[nextIndex] - 25, column[nextIndex]);
		nextIndex++;
		auto t2 = std::chrono::high_resolution_clock::now();

		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
		std::cout << duration << "\n";
	}
	else {
		point++;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		a_pressed = true;
	}
	else
	{
		if (a_pressed)
		{
			a_pressed = false;
		}
	}

}

void GameBoard::CreatePlayer(float x, int a) {
	m_player = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(m_player);

	m_player->SetPos(sf::Vector2f(x, 10.f));
	m_player->SetSize(sf::Vector2f(60.f, 60.f));

	if (a != 0) {
		 
		GameEngine::SpriteRenderComponent* spriteRender = static_cast<GameEngine::SpriteRenderComponent*>
			(m_player->AddComponent<GameEngine::SpriteRenderComponent>());

		spriteRender->SetFillColor(sf::Color::Transparent);

		if (a == 1) {
			spriteRender->SetTexture(GameEngine::eTexture::Player);
		}
		else if (a == 2) {
			spriteRender->SetTexture(GameEngine::eTexture::Player2);
		}
		else {
			spriteRender->SetTexture(GameEngine::eTexture::Player3);
		}

	}

	//move the box
	if (a == 0) {
		m_player->AddComponent<SoundComponent>();

		//create bg
		m_player = new GameEngine::Entity();
		GameEngine::SpriteRenderComponent* spriteRender = static_cast<GameEngine::SpriteRenderComponent*>
			(m_player->AddComponent<GameEngine::SpriteRenderComponent>());

		spriteRender->SetFillColor(sf::Color::Transparent);
		spriteRender->SetTexture(GameEngine::eTexture::Player);
		//bg done
	}
	else {
		m_player->AddComponent<PlayerMovementComponent>();
	}
}

void GameBoard::Update()
{	
	auto t1 = std::chrono::high_resolution_clock::now();
	if (point >= data[nextIndex] && point <= data[nextIndex]+1900) {

		CreatePlayer(140 * column[nextIndex] - 25, column[nextIndex]);
		nextIndex++;
		auto t2 = std::chrono::high_resolution_clock::now();

		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
		std::cout << duration << "\n";
	}
	else {
		point++;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		a_pressed = true;
	}
	else
	{
		if (a_pressed)
		{
			a_pressed = false;
		}
	}

}
void GameBoard:: 