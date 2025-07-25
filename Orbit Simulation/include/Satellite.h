#pragma once
#include "maths/vec3.h"
#include "maths/vec3d.h"


class Satellite
{
private:
	vec3d position; // Position in m
	vec3d velocity; // Velocity in m/s per second

	float mass; // Mass in kg
	float radius; // Radius in m

	vec3 colour;

public:
	bool stationary; // If true the satellite does not move

	Satellite(vec3d position, vec3d velocity, double radius, double mass, vec3 colour, bool isStationary = false);

	vec3d getPosition() const;
	double getMass() const;
	double getRadius() const;
	vec3 getColour() const;

	void update(vec3d force, double deltaTime);
};