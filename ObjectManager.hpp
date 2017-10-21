#pragma once

#include "Entity.hpp"
#include "ObjectManagerBase.hpp"
#include "WindowManagerBase.hpp"
#include "Types.hpp"
#include "MathUtils.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <cmath>
#include <mutex>

#define PLAYER_BASE_ROTATION -30.f
#define EPSILON 0.1f

#define DEG_TO_RADIAN(deg) (deg / M_PI * 180.f)
#define RAD_TO_DEG(rad) (rad * 57.2958)

class ObjectManager : public ObjectManagerBase
{
	public:
		ObjectManager();
		virtual ~ObjectManager(void);
		ObjectManager(const ObjectManager &obj) = delete;
		ObjectManager &operator=(const ObjectManager &p) = delete;

		void	Loop(const sf::Time &time) override;
		void	Init(WindowManagerBase *window) override;
		void	JoystickMoved() override;
		void	Stop();
	private:
		void	updateVelocity();//TODO optimized by only calling when update
		void	updateAccFromJoystickPos();
		void	updatePlayerSpeed();
		void	updatePlayerRotation();

		WindowManagerBase			*m_windowManager;
		std::atomic<bool>			m_running;
		Entity						m_player;
		sf::Vector2f				m_playerSpeed;
		float						m_acceleration;
		float						m_playerRotation;
		sf::Vector2f				m_playerDirection;
		sf::Vertex 					line[2];
		sf::VertexArray				triangle;
		sf::VertexArray				triangle2;

};
