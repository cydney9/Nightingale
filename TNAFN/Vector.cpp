#include "Vector.h"

vec2::vec2()
{
}

vec2::vec2(float _x, float _y)
{
	//Sets x and y
	x = _x;
	y = _y;
}

void vec2::Subtract(vec2 v2)
{
	//Subtracts v2 from THIS
	this->x -= v2.x;
	this->y -= v2.y;
}

void vec2::MultScalar(float s)
{
	//multiplies s into THIS
	this->x *= s;
	this->y *= s;
}

float vec2::Dot(vec2 v2)
{
	//Returns the dot product between THIS and v2
	return float (x*v2.x + y * v2.y);
}

void vec2::DivScalar(float s)
{
	//Divides THIS by s
	this->x /= s;
	this->y /= s;
}

float vec2::GetMagnitude()
{
	return float(sqrt((x * x) + (y * y)));
}

float vec2::GetMagnitudeSquared()
{
	//Stores the result of Getmagnitude
	float magnitude = GetMagnitude();

	//Squares the magnitude
	return magnitude * magnitude;
}

vec2 vec2::Normalize()
{
	//Divides this by the magnitude to get a vector in the same
	//direction, but with a magnitude of 1
	vec2 normalized = *this / GetMagnitude();

	return normalized;
}

vec2 vec2::Project(vec2 b)
{
	//Just for easy readability
	vec2 a = *this;

	//Equation
	//		A dot B
	//B *   ------
	//		||B||^2
	float numerator = a.Dot(b);
	float denominator = b.GetMagnitudeSquared();
	
	return (b*(numerator/denominator));
}

float vec2::operator[](int i)
{
	//Indexes the variables at i
	//* 0 = x
	//* 1 = y
	return *hold[i];
}

vec2 vec2::operator-()
{
	return vec2(-x, -y);
}

vec2 vec2::operator+(vec2 v1)
{
	return vec2(this->x + v1.x, this->y + v1.y);
}

vec2 vec2::operator-(vec2 v1)
{
	return vec2(this->x - v1.x, this->y - v1.y);
}

vec2 vec2::operator*(float f)
{
	return vec2(this->x * f, this->y * f);
}

vec2 vec2::operator/(float s)
{
	return vec2(this->x /s, this->y /s);
}

vec3::vec3()
{
}

vec3::vec3(float _x, float _y, float _z)
{
	//Sets x,y, and z
	x = _x;
	y = _y;
	z = _z;
}

float vec3::GetMagnitude()
{
	return float(sqrt((x * x) + (y * y) + (z * z)));
}

float vec3::operator[](int i)
{
	//Indexes the variables at i
	//* 0 = x
	//* 1 = y
	//* 2 = z
	return *hold[i];
}

vec3 vec3::operator-()
{
	return vec3(-z,-y,-z);
}

vec3 vec3::operator+(vec3 v2)
{
	return vec3(this->x + v2.x, this->y + v2.y, this->z + v2.z);
}

vec3 vec3::operator-(vec3 v2)
{
	return vec3(this->x - v2.x, this->y - v2.y, this->z - v2.z);
}

vec3 vec3::operator*(float f)
{
	return vec3(this->x * f, this->y * f, this->z * f);
}

vec3 vec3::operator/(float f)
{
	return vec3(this->x / f, this->y / f, this->z / f);
}

vec4::vec4()
{
}

vec4::vec4(float _x, float _y, float _z, float _w)
{
	//Sets x, y, z, and w
	x = _x;
	y = _y;
	z = _z;
	w = _w;
}

float vec4::GetMagnitude()
{
	return float(sqrt((x * x) + (y * y) + (z * z) + (w * w)));
}

float vec4::operator[](int i)
{
	//Indexes the variables at i
	//* 0 = x
	//* 1 = y
	//* 2 = z
	//* 3 = w
	return *hold[i];
}
