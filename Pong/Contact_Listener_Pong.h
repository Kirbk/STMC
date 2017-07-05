#pragma once

#include <Box2D\Box2D.h>

class Contact_Listener_Pong : public b2ContactListener
{
public:
	Contact_Listener_Pong();
	~Contact_Listener_Pong();

	virtual void BeginContact(b2Contact* contact);
	virtual void EndContact(b2Contact* contact);
};

