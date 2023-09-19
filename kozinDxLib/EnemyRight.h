#pragma once
//右から出現する敵のクラス
class EnemyRight
{
public:
	EnemyRight();
	~EnemyRight();

	void Init();
	void Update();
	void Draw() const;

	//メンバー変数にアクセスする
	void SetHandle(int handle) { m_handle = handle; }

	bool isExist() const { return m_isExist; }

	//敵キャラクターをスタートさせる
	void Start();

private:
	int m_handle;   //グラフィックのハンドル

	bool m_isExist; //存在するかフラグ(使用中かどうか)

	float m_posX;
	float m_posY;
};

