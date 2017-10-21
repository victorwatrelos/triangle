#include "ObjectManager.hpp"

ObjectManager::ObjectManager() :
	  m_running(false)
	  , m_player("textures/triangle-green-double.png")
	  , m_playerSpeed({0.f, 0.f})
	  , m_acceleration(0.f)
	  , m_playerAngle()
	  , triangle(sf::PrimitiveType::Triangles, 3)
	  , triangle2(sf::PrimitiveType::Triangles, 3)
{
	m_playerAngle.SetDegAngle(PLAYER_BASE_ROTATION);
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
		sf::Vector2f	currentAcc = {m_playerAngle.GetDirection().x * -m_acceleration, m_playerAngle.GetDirection().y * -m_acceleration};
		m_playerSpeed = m_playerSpeed + currentAcc;
	}

	//Update magnitude with new speed
	mag = math::magnitude(m_playerSpeed);

	if (mag > 500.f)
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
	m_playerAngle += rotation * 0.01f;
	m_player.setRotation(m_playerAngle.GetDegAngle());
	m_windowManager->SetViewRotation(m_playerAngle.GetDegAngle());
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

std::string	ObjectManager::GetPlayerInfo() const
{
	std::stringstream	ss;
	ss << "COORD: " << std::setprecision(2) << m_player.GetPosition().x << "; " << m_player.GetPosition().y << " VEL: " << m_playerSpeed.x << "; " << m_playerSpeed.y << " Acc: " << m_acceleration;
	return ss.str();
}

ObjectManager::~ObjectManager(void) {
}
