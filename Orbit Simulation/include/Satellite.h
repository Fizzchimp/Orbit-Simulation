#pragma once
#include "maths/vec3.h"

class Satellite
{
private:
	vec3 position;
	vec3 velocity = vec3(0.0f, 0.0f, 0.0f);

	float mass;
	float radius;

	vec3 colour;

public:
	Satellite(vec3 position, float radius, float mass, vec3 colour);

	vec3 getPosition() const;
	float getMass() const;
	float getRadius() const;
	vec3 getColour() const;
};