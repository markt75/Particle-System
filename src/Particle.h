#pragma once
#include "ofMain.h"

enum particleMode{
	PARTICLE_MODE_ATTRACT = 0,
	PARTICLE_MODE_REPEL,
	PARTICLE_MODE_NEAREST_POINTS,
	PARTICLE_MODE_NOISE,
	PARTICLE_MODE_DRAW
	
};

enum keyMode{
	ogMode = 0,

}; 

class Particle{

	public:
		Particle();
		Particle(int x, int y);  
		
		void setMode(particleMode newMode);	
		void setKey(keyMode modeVal);	
		void setAttractPoints( vector <glm::vec3> * attract );
		void attractToPoint(int, int);
		void repelFromPoint(int, int);
		void reset();
		void update();
		void draw();	
		void increaseVelocity();
		void decreaseVelocity(); 
		void increaseSize(); 
		void decreaseSize(); 
		
		glm::vec3 pos;
		glm::vec3 vel;
		glm::vec3 frc;
		
		float drag; 
		float uniqueVal;
		float scale; 
		
		particleMode mode;
		keyMode modeVal;

		
		vector <glm::vec3> * attractPoints; 

		bool inc_dec_vel = false;

		ofColor color;
};
