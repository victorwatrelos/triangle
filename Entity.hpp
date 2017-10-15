#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Types.hpp"

class Entity : public sf::Sprite
{
	public:
		Entity(const char *texturePath);
		Entity(const Entity &obj);
		Entity &operator=(const Entity &p);
		virtual ~Entity();

		void	SetId(U16 id);
		void	CenterOrigin();
		void	AddPosition(const sf::Vector2f& pos);
		void	Move(const sf::Time &time);
		void	SetVelocity(const sf::Vector2f &velocity);
	private:
		sf::Texture		m_texture;
		U16				m_id;
		sf::Vector2f	m_velocity;
};
