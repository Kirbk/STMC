#pragma once

#include <Engine\IGameScreen.h>
#include <Engine\SpriteBatch.h>
#include <Engine\GLSLProgram.h>
#include <Engine\Camera2D.h>
#include <Engine\GLTexture.h>
#include <Engine\Window.h>
#include <Engine\DebugRenderer.h>
#include <Engine\SpriteFont.h>
#include <Engine\GUI.h>
#include <vector>

#include "ScreenIndices.h"

class EditorScreen : public Engine::IGameScreen
{
public:
	EditorScreen(Engine::Window* window);
	~EditorScreen();

	// Inherited via IGameScreen
	virtual int getNextScreenIndex() const override;
	virtual int getPreviousScreenIndex() const override;
	virtual void build() override;
	virtual void destroy() override;
	virtual void onEntry() override;
	virtual void onExit() override;
	virtual void update() override;
	virtual void draw() override;

private:
	void initUI();
	void checkInput();
	bool onExitClicked(const CEGUI::EventArgs& e);

	float m_colorPickerRed = 255.0f;
	float m_colorPickerGreen = 255.0f;
	float m_colorPickerBlue = 255.0f;

	Engine::Camera2D m_camera;
	Engine::Window* m_window;
	Engine::GUI m_gui;
};

