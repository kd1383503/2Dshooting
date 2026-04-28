#include"ResultScene.h"
#include"../SceneManager.h"
#include "../../Scene.h"

void C_ResultScene::Init()
{
	if (SCENE.GetResult())//クリア
	{
		m_clearTex.Load("");


	}
	else//ゲームオーバー
	{
		m_gameoverTex.Load("");

		

	}
}

void C_ResultScene::MatUpdate()
{
	if (SCENE.GetResult())//クリア
	{

		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			SCENEMANAGER.ChangeState(new C_TitleScene());
		}

	}
	else//ゲームオーバー
	{

		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			SCENEMANAGER.ChangeState(new C_TitleScene());
		}

	}
}

void C_ResultScene::Update()
{
	if (SCENE.GetResult())//クリア
	{

	}
	else//ゲームオーバー
	{

	}
}

void C_ResultScene::Draw()
{
	if (SCENE.GetResult())//クリア
	{

	}
	else//ゲームオーバー
	{

	}
}

void C_ResultScene::Release()
{

	m_clearTex.Release();
	m_gameoverTex.Release();

}
