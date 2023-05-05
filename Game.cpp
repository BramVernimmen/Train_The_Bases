#include "pch.h"
#include "Game.h"
#include "utils.h"

Game::Game( const Window& window ) 
	:m_Window{ window }
	, m_MousePos{ Point2f{} }
	, m_LineColor{ Color4f{0.f, 0.f, 0.f, 1.f} }
{
	Initialize( );
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	m_GivenNumbers.push_back(new GivenNumber(InputNumber::BaseTypes::hexadecimal, Point2f{7.5f, 285.f}));
	m_GivenNumbers.push_back(new GivenNumber(InputNumber::BaseTypes::binary, Point2f{ 457.5f, 285.f }));
	m_GivenNumbers.push_back(new GivenNumber(InputNumber::BaseTypes::decimal, Point2f{ 907.5f, 285.f }));
}

void Game::Cleanup( )
{
	for (GivenNumber* ptr: m_GivenNumbers)
	{
		delete ptr;
		ptr = nullptr;
	}
	m_GivenNumbers.clear();
}

void Game::Update( float elapsedSec )
{
	// Check keyboard state
	//const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
	//if ( pStates[SDL_SCANCODE_RIGHT] )
	//{
	//	std::cout << "Right arrow key is down\n";
	//}
	//if ( pStates[SDL_SCANCODE_LEFT] && pStates[SDL_SCANCODE_UP])
	//{
	//	std::cout << "Left and up arrow keys are down\n";
	//}
}

void Game::Draw( ) const
{
	ClearBackground( );
	for (GivenNumber* ptr : m_GivenNumbers)
	{
		ptr->Draw();
	}
	utils::SetColor(m_LineColor);
	float lineThickness{ 5.f };
	utils::DrawLine(Point2f{ 0.f, m_Window.height - lineThickness/2.f }, Point2f{ m_Window.width, m_Window.height - lineThickness / 2.f }, lineThickness);
	utils::DrawLine(Point2f{ 0.f, lineThickness/2.f }, Point2f{ m_Window.width, lineThickness / 2.f }, lineThickness);
	utils::DrawLine(Point2f{ 0.f, 245.f }, Point2f{ m_Window.width, 245.f }, lineThickness);
	utils::DrawLine(Point2f{2.5f, 0.f}, Point2f{2.5f, m_Window.height}, lineThickness);
	utils::DrawLine(Point2f{452.5f, 0.f}, Point2f{452.5f, m_Window.height}, lineThickness);
	utils::DrawLine(Point2f{902.5f, 0.f}, Point2f{902.5f, m_Window.height}, lineThickness);
	utils::DrawLine(Point2f{ m_Window.width - lineThickness / 2.f, 0.f}, Point2f{ m_Window.width - lineThickness / 2.f, m_Window.height}, lineThickness);
	utils::DrawLine(Point2f{}, Point2f{}, lineThickness);
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	switch ( e.keysym.sym )
	{
	case SDLK_0:
		for (GivenNumber* ptr : m_GivenNumbers)
		{
			ptr->InputCharacter('0');
		}
		break;
	case SDLK_KP_0:
		for (GivenNumber* ptr : m_GivenNumbers)
		{
			ptr->InputCharacter('0');
		}
		break;
	case SDLK_1:
		for (GivenNumber* ptr : m_GivenNumbers)
		{
			ptr->InputCharacter('1');
		}
		break;
	case SDLK_KP_1:
		for (GivenNumber* ptr : m_GivenNumbers)
		{
			ptr->InputCharacter('1');
		}
		break;
	case SDLK_2:
		for (GivenNumber* ptr : m_GivenNumbers)
		{
			ptr->InputCharacter('2');
		}
		break;
	case SDLK_KP_2:
		for (GivenNumber* ptr : m_GivenNumbers)
		{
			ptr->InputCharacter('2');
		}
		break;
	case SDLK_3:
		for (GivenNumber* ptr : m_GivenNumbers)
		{
			ptr->InputCharacter('3');
		}
		break;
	case SDLK_KP_3:
		for (GivenNumber* ptr : m_GivenNumbers)
		{
			ptr->InputCharacter('3');
		}
		break;
	case SDLK_4:
		for (GivenNumber* ptr : m_GivenNumbers)
		{
			ptr->InputCharacter('4');
		}
		break;
	case SDLK_KP_4:
		for (GivenNumber* ptr : m_GivenNumbers)
		{
			ptr->InputCharacter('4');
		}
		break;
	case SDLK_5:
		for (GivenNumber* ptr : m_GivenNumbers)
		{
			ptr->InputCharacter('5');
		}
		break;
	case SDLK_KP_5:
		for (GivenNumber* ptr : m_GivenNumbers)
		{
			ptr->InputCharacter('5');
		}
		break;
	case SDLK_6:
		for (GivenNumber* ptr : m_GivenNumbers)
		{
			ptr->InputCharacter('6');
		}
		break;
	case SDLK_KP_6:
		for (GivenNumber* ptr : m_GivenNumbers)
		{
			ptr->InputCharacter('6');
		}
		break;
	case SDLK_7:
		for (GivenNumber* ptr : m_GivenNumbers)
		{
			ptr->InputCharacter('7');
		}
		break;
	case SDLK_KP_7:
		for (GivenNumber* ptr : m_GivenNumbers)
		{
			ptr->InputCharacter('7');
		}
		break;
	case SDLK_8:
		for (GivenNumber* ptr : m_GivenNumbers)
		{
			ptr->InputCharacter('8');
		}
		break;
	case SDLK_KP_8:
		for (GivenNumber* ptr : m_GivenNumbers)
		{
			ptr->InputCharacter('8');
		}
		break;
	case SDLK_9:
		for (GivenNumber* ptr : m_GivenNumbers)
		{
			ptr->InputCharacter('9');
		}
		break;
	case SDLK_KP_9:
		for (GivenNumber* ptr : m_GivenNumbers)
		{
			ptr->InputCharacter('9');
		}
		break;
	case SDLK_a:
		for (GivenNumber* ptr : m_GivenNumbers)
		{
			ptr->InputCharacter('a');
		}
		break;
	case SDLK_b:
		for (GivenNumber* ptr : m_GivenNumbers)
		{
			ptr->InputCharacter('b');
		}
		break;
	case SDLK_c:
		for (GivenNumber* ptr : m_GivenNumbers)
		{
			ptr->InputCharacter('c');
		}
		break;
	case SDLK_d:
		for (GivenNumber* ptr : m_GivenNumbers)
		{
			ptr->InputCharacter('d');
		}
		break;
	case SDLK_e:
		for (GivenNumber* ptr : m_GivenNumbers)
		{
			ptr->InputCharacter('e');
		}
		break;
	case SDLK_f:
		for (GivenNumber* ptr : m_GivenNumbers)
		{
			ptr->InputCharacter('f');
		}
		break;
	}
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
	m_MousePos.x = float(e.x);
	m_MousePos.y = float(e.y);
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONUP event: ";
	switch ( e.button )
	{
	case SDL_BUTTON_LEFT:
		//std::cout << " left button " << std::endl;
		for (size_t index{0}; index < m_GivenNumbers.size(); ++index)
		{
			m_GivenNumbers[index]->HandleClick(m_MousePos);
		}
		break;
	case SDL_BUTTON_RIGHT:
		//std::cout << " right button " << std::endl;
		break;
	case SDL_BUTTON_MIDDLE:
		//std::cout << " middle button " << std::endl;
		break;
	}
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.15f, 0.15f, 0.15f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}
