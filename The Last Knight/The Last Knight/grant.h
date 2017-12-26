#include "Entity.h"

#ifndef __GRANT_H__ 
#define __GRANT_H__ 

class Grant : public Entity
{
public:
	Grant();
	void update(float,float);
	void control();
	void setHP(int);
	bool radiusDamage(float,float);
};

#endif