#pragma once

#include <Box2D\Box2D.h>

class Entity_Clung;
class Player_Clung;

class Listener_Contact_Clung : public b2ContactListener
{
public:
	Listener_Contact_Clung();
	~Listener_Contact_Clung();

	virtual void BeginContact(b2Contact* contact);
	virtual void EndContact(b2Contact* contact);

private:
	void playerWithItem(Player_Clung* player, Entity_Clung* item);
};

