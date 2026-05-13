#include"ResultScene.h"
#include"../SceneManager.h"
#include "../../Scene.h"


void C_ResultScene::Draw()
{
	if (SCENE.GetResult())//クリア
	{

		SHADER.m_spriteShader.SetMatrix(m_backMat);
		SHADER.m_spriteShader.DrawTex(&m_backTex, Math::Rectangle(0, 0, 1280, 720), 1.0f);

		SHADER.m_spriteShader.SetMatrix(m_clearMat);
		SHADER.m_spriteShader.DrawTex(&m_clearTex, Math::Rectangle(0, 0, 364, 106), 1.0f);

		Math::Color col = { 1,1,1,0.6f };
		for(int i = 0;i < maxDigit;i++)
		{
			Math::Rectangle rec = { 32 * m_digit[i],0,32,46 };

			SHADER.m_spriteShader.SetMatrix(m_scoreMat[i]);
			SHADER.m_spriteShader.DrawTex(&m_scoreTex,rec, &col);
		}

		SHADER.m_spriteShader.SetMatrix(m_scMat);
		SHADER.m_spriteShader.DrawTex(&m_scTex, Math::Rectangle(0, 0, 116, 46), &col);

		SHADER.m_spriteShader.SetMatrix(m_peMat);
		SHADER.m_spriteShader.DrawTex(&m_peTex, Math::Rectangle(0, 0, 547, 121), m_peAlpha);

	}
	else//ゲームオーバー
	{

		SHADER.m_spriteShader.SetMatrix(m_blackMat);
		SHADER.m_spriteShader.DrawTex(&m_blackTex, Math::Rectangle(0, 0, 1280, 720), 1.0f);


		SHADER.m_spriteShader.SetMatrix(m_gameoverMat);
		SHADER.m_spriteShader.DrawTex(&m_gameoverTex, Math::Rectangle(0, 0, 351, 107), m_goAlpha);

		SHADER.m_spriteShader.SetMatrix(m_peMat);
		SHADER.m_spriteShader.DrawTex(&m_peTex, Math::Rectangle(0, 0, 547, 121), m_peAlpha);
	
	}
}

void C_ResultScene::Update()
{
	if (SCENE.GetResult())//クリア
	{

		if (!m_sizeFlg)
		{
			m_size += 0.05;
			for (int i = 0; i < maxDigit; i++)
			{
				m_scorePos[i].y += 1;
			}
		}
		else
		{
			m_size -= 0.2;
			for (int i = 0; i < maxDigit; i++)
			{
				m_scorePos[i].y -= 4;
			}

			if (m_size <= 1.0f)
			{
				m_size = 1.0f;
				m_peFlg = true;
				for (int i = 0; i < maxDigit; i++)
				{
					m_scorePos[i].y = -100;
				}
			}
		}

		if (m_size >= 2.0f)
		{
			m_size = 2.0f;
			m_sizeFlg = true;
		}

		if (!m_peFlg)
		{
			std::random_device rd;
			std::mt19937 mt(rd());
			std::uniform_int_distribution<int> dist(0, 99999999);

			m_score = dist(mt);

		}

		if (m_peFlg)
		{
			m_peAlpha += m_peAnim;
			if (m_peAlpha >= 1.0f)
			{
				m_peAlpha = 1.0f;
				m_peAnim = -0.01;
			}
			if (m_peAlpha <= 0.3)
			{
				m_peAlpha = 0.3f;
				m_peAnim = 0.01f;
			}
		}

		//配列に各桁の数値を格納
		if(m_peFlg)m_score = SCENE.GetScore();

		for (int i = maxDigit - 1; i >= 0; --i)
		{
			//下位の桁から抽出し配列に格納していく
			m_digit[i] = m_score % 10;
			m_score /= 10;
		}

		if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		{
			if (!SCENE.GetEnter() && m_peFlg)
			{
				SCENE.SetEnter(true);
				SCENEMANAGER.ChangeState(new C_TitleScene());
				return;
			}
		}
		else
		{
			SCENE.SetEnter(false);
		}

	}
	else//ゲームオーバー
	{

		m_goAlpha += 0.005;
		if (m_goAlpha >= 0.9f && m_peAnim == 0)
		{
			m_goAlpha = 1.0f;
			m_peAnim += 0.01f;
		}
		
		m_peAlpha += m_peAnim;
		if (m_peAlpha >= 1.0f)
		{
			m_peAlpha = 1.0f;
			m_peAnim = -0.01;
		}
		if (m_peAlpha <= 0.3 && m_peAnim < 0)
		{
			m_peAlpha = 0.3f;
			m_peAnim = 0.01f;
		}

		if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		{
			if (!SCENE.GetEnter() && m_goAlpha >= 1.0f)
			{
				SCENE.SetEnter(true);
				SCENEMANAGER.ChangeState(new C_TitleScene());
				return;
			}
		}
		else
		{
			SCENE.SetEnter(false);
		}

	}
}

void C_ResultScene::MatUpdate()
{
	
	Math::Matrix trans = Math::Matrix::CreateTranslation(m_clearPos.x, m_clearPos.y, 0);
	Math::Matrix scale = Math::Matrix::CreateScale(2, 2, 1);
	m_clearMat = scale * trans;

	for(int i = 0;i < maxDigit;i++)
	{
		trans = Math::Matrix::CreateTranslation(m_scorePos[i].x, m_scorePos[i].y, 0);
		scale = Math::Matrix::CreateScale(m_size, m_size, 1);
		m_scoreMat[i] = trans * scale;
	}
	
	trans = Math::Matrix::CreateTranslation(-200, m_scorePos[0].y, 0);
	scale = Math::Matrix::CreateScale(m_size, m_size, 1);
	m_scMat = trans * scale;

	trans = Math::Matrix::CreateTranslation(0, 0, 0);
	scale = Math::Matrix::CreateScale(2, 2, 1);
	m_backMat = trans * scale;


	//gameover
	m_blackMat = Math::Matrix::CreateTranslation(0, 0, 0);

	trans = Math::Matrix::CreateTranslation(m_gameoverPos.x, m_gameoverPos.y, 0);
	scale = Math::Matrix::CreateScale(2.5, 2.5, 1);
	m_gameoverMat = scale * trans;

	trans = Math::Matrix::CreateTranslation(0, -270, 0);
	scale = Math::Matrix::CreateScale(0.6, 0.3, 1);
	m_peMat = scale * trans;
	
}

void C_ResultScene::Init()
{
	//画像ロード
	m_clearTex.Load("Asset/texture/ResultScene/clear.png");
	m_scoreTex.Load("Asset/texture/GameScene/UI/num.png");
	m_backTex.Load("Asset/texture/GameScene/Back/back.png");
	m_scTex.Load("Asset/texture/ResultScene/score.png");

	m_gameoverTex.Load("Asset/texture/ResultScene/gameover.png");
	m_blackTex.Load("Asset/texture/ResultScene/black.png");
	m_peTex.Load("Asset/texture/TitleScene/pe.png");

	if (SCENE.GetResult())//クリア
	{

		m_clearPos = {0,160};
		

		m_peAlpha = 0;
		m_peAnim = 0;

		m_score = 0;
		m_size = 0;
		m_sizeFlg = false;
		m_cnt = 0;

		m_peFlg = false;

		float x = -100;

		for (int i = 0; i < maxDigit; i++)
		{
			m_scorePos[i] = { x + i * 40 ,-100 };
			m_digit[i] = {};
		}

	}
	else//ゲームオーバー
	{


		m_gameoverPos = { 0,100 };
		m_goAlpha = 0;
		m_peAlpha = 0;
		m_peAnim = 0;

		m_cnt = 0;

	}
	
}


void C_ResultScene::Release()
{

	m_clearTex.Release();
	m_scoreTex.Release();
	m_backTex.Release();
	m_scTex.Release();

	m_gameoverTex.Release();
	m_blackTex.Release();
	m_peTex.Release();

}
