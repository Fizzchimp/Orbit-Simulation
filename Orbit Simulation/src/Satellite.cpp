#include "Satellite.h"

Satellite::Satellite(vec3 position, float radius, float mass, vec3 colour)
	: position(position), mass(mass), radius(radius), colour(colour) {}

vec3 Satellite::getPosition() const
{
	return position;
}

float Satellite::getMass() const
{
	return mass;
}

float Satellite::getRadius() const
{
	return radius;
}

vec3 Satellite::getColour() const
{
	return colour;
}
