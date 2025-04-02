namespace ftypes
{
	struct Vector2
	{
		float x, y;

		Vector2(float x = 0, float y = 0)
		{
			this->x = x;
			this->y = y;
		}

		Vector2 operator+(const Vector2& other)
		{
			return { (this->x + other.x), (this->y + other.y) };
		}

		Vector2 operator-(const Vector2& other)
		{
			return { (this->x - other.x), (this->y - other.y) };
		}

		Vector2 operator*(const Vector2& other)
		{
			return { (this->x * other.x), (this->y * other.y) };
		}

		Vector2 operator/(const Vector2& other)
		{
			return { (this->x / other.x), (this->y / other.y) };
		}
	};
	struct Matrix4x4;
}