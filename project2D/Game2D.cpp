#include "Game2D.h"

#include "Application.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "TextureManager.h"
#include "CollisionManager.h"

Game2D::Game2D(const char* title, int width, int height, bool fullscreen) : Game(title, width, height, fullscreen)
{
	// Initalise the textures.
	TextureManager::Create();

	// Initalise the collision manager.
	CollisionManager::Create();

	// Initalise the 2D renderer.
	m_2dRenderer = new aie::Renderer2D();
	
	// Initalise the state machine.
	m_pStateMachine = new StateMachine();

	// Turn VSync off.
	aie::Application* pApplication = aie::Application::GetInstance();
	pApplication->SetVSync(true);
}

Game2D::~Game2D()
{
	// Delete the textures.
	TextureManager::Delete();

	// Delete the collision manager.
	CollisionManager::Delete();

	// Delete the renderer.
	delete m_2dRenderer;

	// Delete the state machine.
	delete m_pStateMachine;
}

void Game2D::Update(float deltaTime)
{
	m_pStateMachine->Update(deltaTime);
}

void Game2D::Draw()
{
	aie::Application* application = aie::Application::GetInstance();
	float time = application->GetTime();

	// Wipe the screen to clear away the previous frame.
	application->ClearScreen();

	// Prepare the renderer. This must be called before any sprites are drawn.
	m_2dRenderer->Begin();

	// Render the state.
	m_pStateMachine->Draw(m_2dRenderer);

	// Done drawing sprites. Must be called at the end of the Draw().
	m_2dRenderer->End();
}