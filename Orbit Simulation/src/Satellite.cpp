#include "Satellite.h"

Satellite::Satellite(vec3d position, vec3d velocity, double radius, double mass, vec3 colour, bool isStationary)
	: position(position), velocity(velocity), radius(radius), mass(mass), colour(colour), stationary(isStationary) {}

vec3d Satellite::getPosition() const
{
	return position;
}

double Satellite::getMass() const
{
	return (double)mass;
}

double Satellite::getRadius() const
{
	return radius;
}

vec3 Satellite::getColour() const
{
	return colour;
}

void Satellite::update(vec3d acceleration, double deltaTime)
{
	if (!stationary) 
	{
		vec3d newVelocity = velocity + acceleration * deltaTime; // Update velocity
		position = position + (newVelocity + velocity) * 0.5 * deltaTime + acceleration * (deltaTime * deltaTime * 0.5); // Update position using S = ut + 1/2 a t^2
		velocity = newVelocity;
		
	}
}
