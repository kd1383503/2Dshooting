#include"TitleScene.h"
#include"../SceneManager.h"
#include "../../Scene.h"

#include "../GameScene/Back/Back.h"

void C_TitleScene::Draw()
{

	m_back->Draw();

	

	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle(0, 0, 542, 106), 1.0f);

	SHADER.m_spriteShader.SetMatrix(m_pressEnterMat);
	SHADER.m_spriteShader.DrawTex(&m_pressEnterTex, Math::Rectangle(0, 0, 200, 70), m_pressEnterAlpha);


}

void C_TitleScene::MatUpdate()
{

	m_back->MatUpdate();

	Math::Matrix scale = Math::Matrix::CreateScale(2.0, 2.5, 1);
	Math::Matrix trans = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_mat = scale * trans;
	
	scale = Math::Matrix::CreateScale(2, 1.5, 1);
	trans = Math::Matrix::CreateTranslation(m_pressEnterPos.x, m_pressEnterPos.y, 0);
	m_pressEnterMat = scale * trans;

}

void C_TitleScene::Update()
{

	m_back->Update();

	m_pressEnterAlpha += m_addAlpha;
	if (m_pressEnterAlpha > 0.9f)
	{
		m_addAlpha = -0.01f;
		m_pressEnterAlpha = 0.9f;
	}
	else if (m_pressEnterAlpha < 0.3f)
	{
		m_addAlpha = 0.01f;
		m_pressEnterAlpha = 0.3f;
	}

	if(GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		if (!SCENE.GetEnter())
		{
			SCENE.SetEnter(true);
			SCENEMANAGER.ChangeState(new C_GameScene());
			return;
		}
	}
	else
	{
		SCENE.SetEnter(false);
	}

}

void C_TitleScene::Init()
{

	// テクスチャの読み込み
	m_tex.Load("Asset/texture/TitleScene/SPACE_FIGHTER.png");
	//m_shadowTex.Load("Asset/texture/TitleScene/titleShadow.png");
	m_pressEnterTex.Load("Asset/texture/TitleScene/pressEnter.png");

	// タイトルの初期化
	m_pos = { 0, 100 };
	
	// Press Enterの初期化
	m_pressEnterPos = { 0, -240 };
	m_pressEnterAlpha = 0.0f;
	m_addAlpha = 0.01f;


	m_back = new C_Back;
	m_back->Init();


}

void C_TitleScene::Release()
{

	if (m_back != nullptr) delete m_back;
	m_tex.Release();
	m_pressEnterTex.Release();

}
