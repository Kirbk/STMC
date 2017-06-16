#pragma once

#include "Entity_Clung.h"

class Item_Clung : public Entity_Clung
{
public:
	Item_Clung();
	virtual ~Item_Clung();

	// Inherited via Entity_Clung
	virtual void update() override;
};

