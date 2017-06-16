#include "Listener_Contact_Clung.h"

#include <iostream>
#include <Box2D\Box2D.h>

#include "Entity_Clung.h"
#include "Player_Clung.h"
#include "MedKit_Clung.h"

Listener_Contact_Clung::Listener_Contact_Clung()
{
}


Listener_Contact_Clung::~Listener_Contact_Clung()
{
}

void Listener_Contact_Clung::BeginContact(b2Contact* contact) 
{
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();
	Entity_Clung* entityA = static_cast<Entity_Clung*>(fixtureA->GetUserData());
	Entity_Clung* entityB = static_cast<Entity_Clung*>(fixtureB->GetUserData());

	if ((entityA != nullptr) && (entityB != nullptr)) {
		switch (entityA->getType()) {
		case EntityCategory::BOUNDARY:

			break;
		case EntityCategory::ENEMY:

			break;
		case EntityCategory::ITEM:
			if (entityB->getType() == EntityCategory::PLAYER) {
				playerWithItem(static_cast<Player_Clung*>(entityB), entityA);
			}

			break;
		case EntityCategory::PLAYER:
			if (entityB->getType() == EntityCategory::ITEM) {
				playerWithItem(static_cast<Player_Clung*>(entityA), entityB);
			}
			break;
		}
	}
}

void Listener_Contact_Clung::EndContact(b2Contact* contact)
{

}

void Listener_Contact_Clung::playerWithItem(Player_Clung * player, Entity_Clung * item)
{
	if (item->getItemType() == ItemList::MedKit) {
		MedKit_Clung* medkit = static_cast<MedKit_Clung*>(item);
		if ((player->getHealth() != player->getMaxHealth()) && (!medkit->isUsed())) {
			medkit->setUsed();
			player->addHealth(medkit->getBenefit());
			medkit->destroy();
		}
	}
}
