#pragma once
class Vector3
{
public:
	float x, y, z;

	Vector3();
	Vector3(float x, float y, float z);
	Vector3(const Vector3 & vec);
	~Vector3();

	void operator=(const Vector3 & vec);
	void add(const Vector3 & vec);
	void mult(float num);
	void div(float num);

	float getLength();
	void normalize();
};

