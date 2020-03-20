#include "Transform.h"
#include "JSON.h"

class Barrel
{
public:
	void CreateBarrel(unsigned int entity, int x, int y, int z);
	void Update();
	int getBarrelID();
	float getAngle();
private:
	unsigned int LinkedEntity;
	unsigned int BarrelID;
	float x;
	float y;
	float playerDir ;
};
