#include "ObjectManager.hpp"

ObjectManager::ObjectManager() :
	  m_running(false)
	  , m_player("textures/triangle-green-double.png")
	  , m_playerSpeed(0.f)
	  , m_playerRotation(0.f)
	  , triangle(sf::PrimitiveType::Triangles, 3)
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
	triangle[0].color = sf::Color::Red;
	triangle[1].color = sf::Color::Blue;
	triangle[2].color = sf::Color::Green;
	m_player.SetId(ret);
	m_player.CenterOrigin();
	m_player.AddPosition({200.f, 200.f});
	m_player.setRotation(PLAYER_BASE_ROTATION);
	m_player.setScale({0.3f, 0.3f});
}

void	ObjectManager::JoystickMoved()
{
	float position = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
	std::cout << "Position: " << position << std::endl;
	m_playerSpeed = 100.f * ((position) / 50.f);
	if (m_playerSpeed > 0.f)
	{
		m_player.SetVelocity({0.f, 0.f});
		return;
	}
	m_player.SetVelocity({m_playerSpeed * std::sin(m_playerRotation), m_playerSpeed * std::cos(m_playerRotation)});
	auto playerPos = m_player.getPosition();
	triangle[0].position = sf::Vector2f(playerPos.x, playerPos.y + 20.f);
	triangle[1].position = sf::Vector2f(playerPos.x, playerPos.y - 20.f);
	triangle[2].position = sf::Vector2f(playerPos.x - std::sin(m_playerRotation) * 300.f, playerPos.y - std::cos(m_playerRotation) * 300.f);
}

void	ObjectManager::updateVelocity()//To optimized by only calling when update
{
	auto playerPos = m_player.getPosition();
	triangle[0].position = sf::Vector2f(playerPos.x, playerPos.y + 20.f);
	triangle[1].position = sf::Vector2f(playerPos.x, playerPos.y - 20.f);
	triangle[2].position = sf::Vector2f(playerPos.x - std::sin(m_playerRotation) * 300.f, playerPos.y - std::cos(m_playerRotation) * 300.f);
	float rotation = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
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
	m_player.setRotation(PLAYER_BASE_ROTATION + RAD_TO_DEG(-m_playerRotation));
	std::cout << "Rotation: " << RAD_TO_DEG(m_playerRotation) << std::endl;
}

void	ObjectManager::Loop(const sf::Time &time)
{
	updateVelocity();
	m_player.Move(time);
}

ObjectManager::~ObjectManager(void) {
}
