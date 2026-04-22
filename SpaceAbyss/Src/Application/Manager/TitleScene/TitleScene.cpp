#include"TitleScene.h"
#include"../SceneManager.h"

void C_TitleScene::Draw()
{

	/*Math::Color color = { 255, 0, 0 };
	SHADER.m_spriteShader.DrawBox(0, 0, 1280, 720, &color, 1.0f);*/

	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle(0, 0, 1280, 720),1.0f);

	SHADER.m_spriteShader.SetMatrix(m_pressEnterMat);
	SHADER.m_spriteShader.DrawTex(&m_pressEnterTex, Math::Rectangle(0, 0, 300, 100), m_pressEnterAlpha);


}

void C_TitleScene::MatUpdate()
{

	m_mat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);

	m_pressEnterMat = Math::Matrix::CreateTranslation(m_pressEnterPos.x, m_pressEnterPos.y, 0);

}

void C_TitleScene::Update()
{

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
		SCENEMANAGER.ChangeState(new C_GameScene());
		return;
	}

}

void C_TitleScene::Init()
{

	// テクスチャの読み込み
	m_tex.Load("Asset/texture/TitleScene/title.png");
	m_pressEnterTex.Load("Asset/texture/TitleScene/pressEnter.png");

	// タイトルの初期化
	m_pos = { 0, 0 };
	
	// Press Enterの初期化
	m_pressEnterPos = { 0, -200 };
	m_pressEnterAlpha = 0.0f;
	m_addAlpha = 0.01f;


}

void C_TitleScene::Release()
{

}
