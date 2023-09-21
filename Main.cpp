# include <Siv3D.hpp> // OpenSiv3D v0.6.10

const int SIZE{ 64 };
const double SPEED{ 200 };

void SetRect(RectF& _rec, Vec2 _pos, Vec2 _wh)
{
	//_rec = Rect{ Arg::center(_pos), _wh };
	_rec.setCenter(_pos);
	_rec.setSize(_wh);
}

enum direction
{
	UP, LEFT, DOWN, RIGHT, NONE
};

direction GetDirection()
{
	if ((KeyUp | KeyW).pressed())
	{
		return UP;
	}
	else if ((KeyLeft | KeyA).pressed())
	{
		return LEFT;
	}
	else if ((KeyDown | KeyS).pressed())
	{
		return DOWN;
	}
	else if ((KeyRight | KeyD).pressed())
	{
		return RIGHT;
	}
	else
		return NONE;
}

void PlayerUpdate(RectF& _rec, Vec2& _pos)
{
	direction d = GetDirection();
	Vec2 dirs[5] =
	{
		{0,-1}, {-1,0}, {0,1}, {1,0}, {0,0}
	};
	;
	_pos = _pos + SPEED * Scene::DeltaTime() * dirs[d];
	_pos.x = Clamp(_pos.x, SIZE / 2.0, Scene::Width() - SIZE / 2.0);
	_pos.y = Clamp(_pos.y, SIZE / 2.0, Scene::Height() - SIZE / 2.0);

	SetRect(_rec, _pos, Vec2{SIZE,SIZE});
}

bool IntersectsRect(const RectF& _rectA, const RectF& _rectB)
{
	float Ax = _rectA.pos.x;
	float Ay = _rectA.pos.y;
	float Bx = _rectB.pos.x;
	float By = _rectB.pos.y;
	float Aw = _rectA.w;
	float Ah = _rectA.h;
	float Bw = _rectB.w;
	float Bh = _rectB.h;
	if (
			//ここに自分の当たり判定を入れる
	)
		return true;
	return false;
}

void Main()
{
	// 背景の色を設定する | Set the background color
	Scene::SetBackground(ColorF{ 0.6, 0.8, 0.7 });

	// 絵文字からテクスチャを作成する | Create a texture from an emoji
	const Texture player{ U"🤖"_emoji };
	const Texture enemy{ U"👹"_emoji };



	Vec2 playerPos{ Scene::Center() };
	Vec2 enemyPos{ 400, 400 };
	RectF playerRect{ playerPos, Vec2{SIZE,SIZE} };
	RectF enemyRect;


	while (System::Update())
	{
		PlayerUpdate(playerRect, playerPos);
		SetRect(playerRect, playerPos, Vec2(SIZE, SIZE));
		SetRect(enemyRect, enemyPos, Vec2(SIZE, SIZE));
		player.resized(SIZE).drawAt(playerPos);
		playerRect.drawFrame(1, 1, Palette::Red);

		if (IntersectsRect(playerRect, enemyRect)) {
			enemy.resized(SIZE).drawAt(enemyPos);
			enemyRect.draw({ Palette::Red, 0.6 }).drawFrame(1, 1, Palette::Red);
		}
		else
		{
			enemy.resized(SIZE).drawAt(enemyPos);
			enemyRect.drawFrame(1, 1, Palette::Red);
		}
	}
}


