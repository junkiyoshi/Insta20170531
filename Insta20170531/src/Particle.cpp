#include "Particle.h"

Particle::Particle() : Particle(0, 0, 0)
{
	
}

Particle::Particle(float x, float y, float z)
{
	this->location = ofVec3f(x, y, z);
	this->start_location = ofVec3f(x, y, z);
	this->velocity = ofVec3f(0, 0, 0);
	this->acceleration = ofVec3f(0, 0, 0);

	this->max_speed = 200;
	this->max_force = 2;
	this->radius = 150;
	this->angle = ofRandom(360);

	float body_value = ofRandom(255);
	this->body_color.setHsb(body_value, 255, 255, 255);
	this->body_size = 50;
}

Particle::~Particle()
{

}

void Particle::applyForce(ofVec3f force)
{
	this->acceleration += force;
}

void Particle::seek(ofVec3f target)
{
	ofVec3f desired = this->location - target;
	float distance = desired.length();
	desired.normalize();
	if (distance < this->radius)
	{
		float m = ofMap(distance, this->radius, 0, 0, this->max_speed);
		desired *= m;
	}
	else
	{
		desired *= this->max_speed;
	}

	ofVec3f steer = this->velocity - desired;
	steer.limit(this->max_force);
	this->applyForce(steer);
}

void Particle::escape(ofVec3f target, float pow)
{
	ofVec3f desired = this->location - target;
	float distance = desired.length();
	desired.normalize();
	if (distance < pow){
		float m = ofMap(distance, this->radius, 0, 0, this->max_speed);
		desired *= m;
	}
	else
	{
		this->seek(this->start_location);
		return;
	}

	ofVec3f steer = this->velocity - desired;
	steer.limit(this->max_force);
	this->applyForce(steer);
}

void Particle::update()
{
	this->velocity += this->acceleration;
	this->velocity.limit(max_speed);
	this->location += this->velocity;

	this->acceleration *= 0;
	this->velocity *= 0.9;
}

void Particle::draw()
{
	ofSetColor(this->body_color);
	ofPushMatrix();
	ofTranslate(this->location);
	ofBox(this->body_size);
	ofPopMatrix();
}
