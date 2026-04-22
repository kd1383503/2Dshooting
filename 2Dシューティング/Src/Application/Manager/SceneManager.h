#pragma once
#include"TitleScene/TitleScene.h"
#include"GameScene/GameScene.h"
#include"ResultScene/ResultScene.h"

class C_SceneManager
{
public:

	~C_SceneManager() {}

	static C_SceneManager& GetInstance()
	{
		static C_SceneManager instance;
		return instance;
	}

	void ChangeState(C_StateScene* newState)
	{

		if (m_currentState != nullptr) m_currentState->Release();

		delete m_currentState;
		m_currentState = newState;

		m_currentState->Init();

		m_currentState->MatUpdate();

	}

	void Init()
	{
		m_currentState->Init();

	}

	void MatUpdate()
	{

		m_currentState->MatUpdate();

	}

	void Update()
	{
		m_currentState->Update();
	}



	void Draw()
	{
		m_currentState->Draw();
	}


	void Release()
	{
		m_currentState->Release();
	}

	C_StateScene* GetCurrentState() { return m_currentState; }



private:

	C_SceneManager() {}

	C_StateScene* m_currentState = nullptr;

};

#define SCENEMANAGER C_SceneManager::GetInstance()