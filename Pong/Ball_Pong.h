#pragma once

#include <Box2D/Box2D.h>
#include <glm.hpp>
#include <Engine/Vertex.h>
#include <Engine/SpriteBatch.h>
#include <Engine/GLTexture.h>
#include <Engine\TileSheet.h>
#include <Engine\InputManager.h>
#include <Engine\DebugRenderer.h>

class Ball_Pong
{
public:	
	Ball_Pong();
	~Ball_Pong();

	void init(b2World* world,
		const glm::vec2& position,
		const glm::vec2& dimensions,
		const glm::vec2& screenDims,
		Engine::ColorRGBA8 color,
		int speed,
		glm::vec4 uvRect = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
		void destroy(b2World* world);

	void draw(Engine::SpriteBatch& spriteBatch);
	void update();

	bool isDynamic() const { return m_body->GetType() == b2_dynamicBody; }

	// Test if a point is inside the box
	bool testPoint(float x, float y) const { return m_fixture->TestPoint(b2Vec2(x, y)); }

	// Beautiful accessors
	b2Body*                    getBody()          const { return m_body; }
	b2Fixture*                 getFixture()       const { return m_fixture; }
	const glm::vec2&           getDimensions()    const { return m_dimensions; }
	glm::vec2                  getPosition()      const { return glm::vec2(m_body->GetPosition().x, m_body->GetPosition().y); }
	glm::vec4                  getUvRect()        const { return m_uvRect; }
	const Engine::ColorRGBA8& getColor()         const { return m_color; }
	float                      getAngle()         const { return m_body->GetAngle(); }
	const Engine::TileSheet&  getTexture()       const { return m_texture; }
	const bool&                getFixedRotation() const { return m_fixedRotation; }
	const bool&                getIsDynamic()     const { return m_isDynamic; }
private:
	glm::vec4 m_uvRect;
	b2Body* m_body = nullptr;
	b2Fixture* m_fixture = nullptr;
	glm::vec2 m_dimensions;
	glm::vec2 m_screenDims;
	Engine::ColorRGBA8 m_color;
	bool m_fixedRotation;
	bool m_isDynamic;
	Engine::TileSheet m_texture;
	int m_speed = 0;
};

