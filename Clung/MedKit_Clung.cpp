#include "MedKit_Clung.h"

#include <iostream>

#include <Engine\ResourceManager.h>


MedKit_Clung::MedKit_Clung(float benefit) : m_benefit(benefit)
{
}


MedKit_Clung::~MedKit_Clung()
{
	//m_box.getBody()->GetWorld()->DestroyBody(m_box.getBody());
}

void MedKit_Clung::init(b2World * world, const glm::vec2 & position, glm::vec2 & direction, float speed, const glm::vec2 & drawDims, glm::vec2 & collisionDims, glm::vec4& uvRect, Engine::Camera2D * camera, Engine::ColorRGBA8 color)
{
	Engine::GLTexture texture = Engine::ResourceManager::getTexture("Assets/textures/medkit.png");
	m_texture.init(texture, glm::ivec2(1, 1));
	m_position = position;
	m_direction = direction;
	m_speed = speed;
	m_drawDims = drawDims;
	m_camera = camera;
	m_color = color;
	m_box.init(world, b2_dynamicBody, this, position, collisionDims);
	m_collisionDims = collisionDims;
	m_type = EntityCategory::ITEM;
	m_itemType = ItemList::MedKit;
	m_shape = Shape::RECTANGLE;
	m_item = true;
	m_uvRect = uvRect;
	//m_box.getFixture()->SetSensor(true);
	
	b2Filter filter = m_box.getFixtures()[0]->GetFilterData();
	filter.categoryBits = EntityCategory::ITEM;
	filter.maskBits = EntityCategory::PLAYER | EntityCategory::BOUNDARY;
	m_box.getFixtures()[0]->SetFilterData(filter);

	b2Body* body = m_box.getBody();

	body->SetLinearDamping(2.0f);
	body->SetAngularDamping(0.8f);
}

void MedKit_Clung::update()
{
	m_angle = m_box.getBody()->GetAngle();

	m_position.x = m_box.getBody()->GetPosition().x;
	m_position.y = m_box.getBody()->GetPosition().y;

	m_direction.x = cos(m_box.getBody()->GetAngle());
	m_direction.y = sin(m_box.getBody()->GetAngle());
}

void MedKit_Clung::drawDebug(Engine::DebugRenderer& debugRenderer) {
	m_box.drawDebug(debugRenderer);
}