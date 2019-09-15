#include "GameBoard.h"
#include <array>
#include <chrono>

#include "GameEngine\GameEngineMain.h"
#include "Game\Components\PlayermovementComponent.h"
#include "GameEngine\EntitySystem\Components\SpriteRenderComponent.h"
#include "GameEngine\Util\SoundManager.h"
#include <GameEngine\EntitySystem\Components\SoundComponent.h>
#include <iostream>
#include <fstream>
#include <ctime>

#pragma warning(disable : 4996)

using namespace GameEngine;

using namespace Game;

static int point = 0;
static int nextIndex = 0;

//std::time_t result = std::time(nullptr);
//int timer = std::mktime(std::localtime(&result));
static std::vector<int> data;
static std::vector<int> column;
static bool a_pressed = true;
static bool s_pressed = true;
static bool d_pressed = true;
static std::vector<Entity> dots;

GameBoard::GameBoard()

	: m_player(nullptr)
{	

	std::ifstream readFile("Resources/data/twang.txt");
	
	int a, b;
	while (readFile >> a >> b)
	{
		std::cout << a;
		data.push_back(a/147);
		column.push_back(b);
	}

	std::cout << data.size();

	for (int d = 0; d < data.size(); d++) {
		std::cout << d;
	}
	CreatePlayer(0, 0);
}


GameBoard::~GameBoard()
{

}

void GameBoard::Update()
{
	//if (std::time(nullptr) - 3 >= timer) {
	//	CreatePlayer(0, 0);
	//	timer = -1;
	//}
	auto t1 = std::chrono::high_resolution_clock::now();
	if (nextIndex < data.size() && point >= data.at(nextIndex) && point <= data.at(nextIndex) + 1900) {

		CreatePlayer(140 * column.at(nextIndex) - 25, column.at(nextIndex));
		nextIndex++;
		auto t2 = std::chrono::high_resolution_clock::now();

		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
	}
	else {
		point++;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		a_pressed = true;
	}
	else if (a_pressed)
	{
		a_pressed = false;
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
		GameEngine::GameEngineMain::GetInstance()->AddEntity(m_player);

		m_player->SetPos(sf::Vector2f(250.f, 150.f));
		m_player->SetSize(sf::Vector2f(500.f, 700.f));

		GameEngine::SpriteRenderComponent* spriteRender = static_cast<GameEngine::SpriteRenderComponent*>
			(m_player->AddComponent<GameEngine::SpriteRenderComponent>());

		spriteRender->SetFillColor(sf::Color::Transparent);
		spriteRender->SetTexture(GameEngine::eTexture::Background);
		//bg done
	}
	else {
		m_player->AddComponent<PlayerMovementComponent>();
	}
}
