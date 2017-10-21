#include "ObjectManager.hpp"

ObjectManager::ObjectManager() :
	  m_running(false)
	  , m_player("textures/triangle-green-double.png")
	  , m_playerSpeed({0.f, 0.f})
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

// Make sure to have call sf::Joystick::update() berfore
void	ObjectManager::updateAccFromJoystickPos()
{
	float position = sf::Joystick::getAxisPosition(0, sf::Joystick::R);
	if (position < -99.f)
		m_acceleration = 0.f;
	else
		//Acceleration
		m_acceleration = (position + 100.f) * 0.07f;
	assert(m_acceleration == m_acceleration && "Magnitude is NaN, ERROR");
}

void	ObjectManager::updatePlayerSpeed()
{
	float	mag = math::magnitude(m_playerSpeed);
	assert(mag == mag && "Magnitude is NaN, ERROR");
	if (m_acceleration < EPSILON)
	{
		if (mag < EPSILON)
			m_playerSpeed = {0.0f, 0.0f};
		else
			//Deceleration
			//To optimize (can be done without normalizing)
			m_playerSpeed = math::normalize(m_playerSpeed, mag) * (mag - 3.f);
	}
	else
	{
		sf::Vector2f	currentAcc = {std::sin(m_playerRotation) * -m_acceleration, std::cos(m_playerRotation) * -m_acceleration};
		m_playerSpeed = m_playerSpeed + currentAcc;
	}

	//Update magnitude with new speed
	mag = math::magnitude(m_playerSpeed);

	if (mag > 1000.f)
	{
		m_playerSpeed = math::normalize(m_playerSpeed, mag) * 1000.f;
	}
	m_player.SetVelocity(m_playerSpeed);
}

void	ObjectManager::updatePlayerRotation()
{
	float rotation = -sf::Joystick::getAxisPosition(0, sf::Joystick::X);
	if (rotation < 15.f && rotation > -15.f)
		return ;
	if (rotation < 0.f)
		rotation += 10.f;
	else
		rotation -= 10.f;
	rotation *= 0.1f;
	m_playerRotation += rotation * 0.01f;
	while (m_playerRotation > 2 * M_PI)
		m_playerRotation -= 2 * M_PI;
	assert(m_playerRotation == m_playerRotation && "m_playerRotation is NaN");
	float	degTotRotation = RAD_TO_DEG(-m_playerRotation);
	m_player.setRotation(PLAYER_BASE_ROTATION + degTotRotation);
	m_playerDirection = {std::sin(m_playerRotation), std::cos(m_playerRotation)};
	m_windowManager->SetViewRotation(degTotRotation);
}

void	ObjectManager::updateVelocity()//To optimized by only calling when update
{
	sf::Joystick::update();
	updateAccFromJoystickPos();
	updatePlayerRotation();
	updatePlayerSpeed();
}

void	ObjectManager::Loop(const sf::Time &time)
{
	updateVelocity();
	m_player.Move(time);
	m_windowManager->SetViewCenter(m_player.GetPosition());
}

ObjectManager::~ObjectManager(void) {
}
