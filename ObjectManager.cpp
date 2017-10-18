#include "ObjectManager.hpp"

ObjectManager::ObjectManager() :
	  m_running(false)
	  , m_player("textures/triangle-green-double.png")
	  , m_playerSpeed(0.f)
	  , m_playerRotation(0.f)
	  , triangle(sf::PrimitiveType::Triangles, 3)
	  , triangle2(sf::PrimitiveType::Triangles, 3)
{
}

void	ObjectManager::Stop()
{
	m_running = false;
}

void	ObjectManager::Init(WindowManagerBase *windowManager)
{
	m_running = true;
	m_windowManager = windowManager;
	auto ret = m_windowManager->AddObject(&m_player, true);
	m_windowManager->AddObject(&triangle, true);
	m_windowManager->AddObject(&triangle2, true);
	triangle[0].color = sf::Color::Red;
	triangle[1].color = sf::Color::Blue;
	triangle[2].color = sf::Color::Green;

	triangle2[0].color = sf::Color::Red;
	triangle2[1].color = sf::Color::Red;
	triangle2[2].color = sf::Color::Red;
	triangle2[0].position = sf::Vector2f(600.f, 600.f);
	triangle2[1].position = sf::Vector2f(100.f, 100.f);
	triangle2[2].position = sf::Vector2f(-100.f, 0.f);

	m_player.SetId(ret);
	m_player.CenterOrigin();
	m_player.AddPosition({200.f, 200.f});
	m_player.setRotation(PLAYER_BASE_ROTATION);
	m_player.setScale({0.2f, 0.2f});
}

void	ObjectManager::JoystickMoved()
{
}

void	ObjectManager::updateVelocity()//To optimized by only calling when update
{
	sf::Joystick::update();
	{
		float position = sf::Joystick::getAxisPosition(0, sf::Joystick::R);
		std::cout << "Pos: " << position << std::endl;
		if (position < -99.f)
			m_acceleration = 0.f;
		else
			//Acceleration
			m_acceleration = (position + 100.f) * 0.07f;
		if (m_acceleration < 0.1f)
		{
			m_acceleration = 0.f;
			if (m_playerSpeed < 0.2f)
				m_playerSpeed = 0.0f;
			else
				//Deceleration
				m_playerSpeed -= 14.0f;//TODO Calc with time and not frame rate
		}
		else
		{
			m_playerSpeed += m_acceleration;
		}
		if (m_playerSpeed > 1000.f)
			m_playerSpeed = 1000.f;
		std::cout << "acc: " << m_acceleration << std::endl;
		std::cout << "player speed: " << m_playerSpeed << std::endl;
		m_player.SetVelocity({-m_playerSpeed * std::sin(m_playerRotation), -m_playerSpeed * std::cos(m_playerRotation)});
	}
	{
		auto playerPos = m_player.getPosition();
		/*
		triangle[0].position = sf::Vector2f(playerPos.x, playerPos.y + 20.f);
		triangle[1].position = sf::Vector2f(playerPos.x, playerPos.y - 20.f);
		triangle[2].position = sf::Vector2f(playerPos.x - std::sin(m_playerRotation) * 300.f, playerPos.y - std::cos(m_playerRotation) * 300.f);
		*/
		float rotation = -sf::Joystick::getAxisPosition(0, sf::Joystick::X);
		if (rotation < 10.f && rotation > -10.f)
			return ;
		if (rotation < 0.f)
			rotation += 10.f;
		else
			rotation -= 10.f;
		rotation *= 0.1f;
		m_playerRotation += rotation * 0.01f;
		while (m_playerRotation > 2 * M_PI)
			m_playerRotation -= 2 * M_PI;
		float	degTotRotation = RAD_TO_DEG(-m_playerRotation);
		m_player.setRotation(PLAYER_BASE_ROTATION + degTotRotation);
		m_windowManager->SetViewRotation(degTotRotation);
	}
	{
		float position = sf::Joystick::getAxisPosition(0, sf::Joystick::R);
		std::cout << "POSITION: " << position << std::endl;
		m_acceleration = 5.f * ((position) / 50.f);
	}
}

void	ObjectManager::Loop(const sf::Time &time)
{
	updateVelocity();
	m_player.Move(time);
	m_windowManager->SetViewCenter(m_player.GetPosition());
}

ObjectManager::~ObjectManager(void) {
}
