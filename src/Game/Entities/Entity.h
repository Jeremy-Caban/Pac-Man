#pragma once
#include "ofMain.h"

class Entity {
	protected:
		int x, y, width, height, health;
		ofImage sprite;
		int ticks = 0;
	public:
		explicit Entity(int x, int y, int width, int height);
		virtual void tick();
		virtual void render();
		bool remove = false;
		void damage(Entity* damageSource);
		bool collides(Entity* entity);
		void setX(int x){this->x = x;}
		void setY(int y){this->y = y;}
		int getX(){return x;}
		int getY(){return y;}
		ofRectangle getBounds();
		ofRectangle getBounds(int x, int y);
};