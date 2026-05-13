#pragma once

class Scene
{
public:

	// 初期設定
	void Init();
	// 解放
	void Release();
	// 更新処理
	void Update();
	// 描画処理
	void Draw2D();
	// GUI処理
	void ImGuiUpdate();

	//ゲームシーンからresultを持ってくる用
	void SetResult(bool result) { m_result = result; }
	//リザルトシーンに結果を持っていく用
	bool GetResult() { return m_result; }

	bool GetEnter() { return m_enter; }
	void SetEnter(bool en) { m_enter = en; }

	void SetScore(unsigned int score) { m_score = score; }
	unsigned int GetScore() { return m_score; }

private:

	bool m_result = true;//true:クリア false:ゲームオーバー
	bool m_enter = true;
	unsigned int m_score = 0;

private:

	Scene() {}

public:
	static Scene& GetInstance()
	{
		static Scene instance;
		return instance;
	}
};

#define SCENE Scene::GetInstance()
