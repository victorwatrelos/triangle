#include "Entity.hpp"

Entity::Entity(const char *texturePath) {
	if (!this->m_texture.loadFromFile(texturePath))
	{
		std::cerr << "Unable to load texture " << texturePath << std::endl;
	}
	this->setTexture(m_texture);
}

Entity::Entity(const Entity &obj) {
	*this = obj;
}

Entity::~Entity(void) {

}

Entity    &Entity::operator=(const Entity &p) {
	this->m_texture = p.m_texture;
	return *this;
}

void		Entity::SetId(U16 id)
{
	this->m_id = id;
}

void		Entity::CenterOrigin()
{
	auto size = m_texture.getSize();
	this->setOrigin(size.x / 2.f, size.y / 2.f);
}

void		Entity::AddPosition(const sf::Vector2f& pos)
{
	this->setPosition(this->getPosition() + pos);
}
