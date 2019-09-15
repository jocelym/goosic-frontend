#pragma once
#include "GameEngine\EntitySystem\Component.h"

namespace Game
{
	class backgroundComponent : public GameEngine::Component
	{
	public:
		backgroundComponent();
		~backgroundComponent();

		virtual void Update() override;
		virtual void OnAddToWorld() override;

	private:
		int m_lastFaceIndex;
		bool m_wasFaceSwapButtonPressed;
	};
}