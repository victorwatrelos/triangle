#include "Angle.hpp"

Angle::Angle()
	: m_radAngle(0)
	, m_degAngle(0)
{
	dirFromRad();
}

Angle::Angle(const sf::Vector2f &direction)
: m_direction(direction)
{
	
}

Angle::Angle(const Angle &obj) {
	*this = obj;
}

Angle::~Angle(void) {

}

float	Angle::GetRadAngle() const
{
	return this->m_radAngle;
}

float	Angle::GetDegAngle() const
{
	return this->m_degAngle;
}

const sf::Vector2f	&Angle::GetDirection() const
{
	return this->m_direction;
}

void			Angle::dirFromRad()
{
	this->m_direction = {std::sin(m_radAngle), std::cos(m_radAngle)};
}

void		Angle::degFromRad()
{
	this->m_degAngle = m_radAngle * (180.f / M_PI);
}

void				Angle::SetDegAngle(float angle)
{
	while (angle < 0)
		angle += 360.f;
	angle = std::fmod(angle, 360.f);
	this->m_degAngle = angle;
	this->m_radAngle = angle * (M_PI / 180.f);
	dirFromRad();
	assert(m_degAngle == m_degAngle && "Rotation is NaN");
}

void				Angle::SetRadAngle(float angle)
{
	while (angle < 0)
		angle += PI2;
	angle = std::fmod(angle, PI2);
	this->m_radAngle = angle;
	degFromRad();
	dirFromRad();
	assert(m_degAngle == m_degAngle && "Rotation is NaN");
}

void				Angle::SetDirection(const sf::Vector2f direction)
{
	this->m_direction = direction;
	this->m_radAngle = std::atan2(direction.y, direction.x);
	degFromRad();
	assert(m_degAngle == m_degAngle && "Rotation is NaN");
}

Angle    &Angle::operator=(const Angle &p) {
	(void)p;
	this->m_direction = p.m_direction;
	this->m_radAngle = p.GetRadAngle();
	this->m_degAngle = p.GetDegAngle();
	assert(m_degAngle == m_degAngle && "Rotation is NaN");
	return *this;
}

Angle& Angle::operator+=(const Angle& rhs)
{
	this->SetDirection(math::normalize(this->GetDirection() + rhs.GetDirection()));
	return *this;
}

Angle&	Angle::operator+=(float radAngle)
{
	this->SetRadAngle(radAngle + this->m_radAngle);
	return *this;
}
