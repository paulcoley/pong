#pragma once
#include <math.h>

struct Vector2f {
	float x;
	float y;

	// Unit vector is a vector with a magnitude (length) of 1.
	// Relevant if vector is a direction.
	void convertToUnitVector() {
		float magnitude = sqrtf(x*x + y*y);
		x /= magnitude;
		y /= magnitude;
	}

	Vector2f operator+(Vector2f element) {
		Vector2f sum = { x + element.x, y + element.y};
		return sum;
	}

	Vector2f operator-(Vector2f element) {
		Vector2f sum = { x - element.x, y - element.y };
		return sum;
	}

	Vector2f& operator*(float scaler) {
		Vector2f product = { x * scaler, y * scaler };
		return product;
	}

	void operator*=(float scaler) {
		x *= scaler;
		y *= scaler;
	}

	Vector2f getUnitVector() {
		Vector2f unitVector = { x, y };
		unitVector.convertToUnitVector();
		return unitVector;
	}
};