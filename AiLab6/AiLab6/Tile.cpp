#include "Tile.h"

Tile::Tile(sf::Font & t_font, sf::Vector2f t_pos) :
	m_font(t_font)
{
	m_body.setSize(sf::Vector2f(18, 18));
	m_body.setPosition(t_pos);
	m_body.setFillColor(sf::Color::Blue);
	m_body.setOutlineThickness(1);
	m_body.setOutlineColor(sf::Color::Black);

	
	m_direction.setSize(sf::Vector2f(9.5, 2));
	m_direction.setPosition(sf::Vector2f(t_pos.x + 9.5, t_pos.y + 9.5));
	m_direction.setOrigin(sf::Vector2f(0, 1));
//	m_direction.setOrigin(sf::Vector2f(m_direction.getPosition().x, m_direction.getPosition().y +1));
	m_direction.setFillColor(sf::Color::Yellow);



	m_text.setFont(m_font);
	m_text.setCharacterSize(10);
	m_text.setPosition(m_body.getPosition());

	setCost(-1);
}

void Tile::update()
{
}

void Tile::render(sf::RenderWindow & t_renderWindow)
{
	t_renderWindow.draw(m_body);

	t_renderWindow.draw(m_direction);

	if (m_displayText)
	{
		t_renderWindow.draw(m_text);
	}
}

void Tile::setCost(int t_InputCost)
{
	m_cost = t_InputCost;
	m_text.setString(std::to_string(m_cost));
}

int Tile::getCost()
{
	return m_cost;
}

void Tile::toggleTextDisplay()
{
	m_displayText = !m_displayText;
}

void Tile::setColour(sf::Color t_colour)
{
	m_body.setFillColor(t_colour);
}

sf::Color Tile::getColour()
{
	return m_body.getFillColor();
}

sf::RectangleShape & Tile::getTile()
{
	return m_body;
}

void Tile::setFlowField(sf::Vector2f t_pos)
{
	if (m_body.getPosition().x > t_pos.x
		&& m_body.getPosition().y > t_pos.y) 
	{//top left
		m_direction.setRotation(225);
	}
	if (m_body.getPosition().x == t_pos.x
		&& m_body.getPosition().y > t_pos.y) 
	{//top mid
		m_direction.setRotation(270);
	}
	if (m_body.getPosition().x < t_pos.x
		&& m_body.getPosition().y > t_pos.y) 
	{//top right
		m_direction.setRotation(315);
	}
	if (m_body.getPosition().x < t_pos.x
		&& m_body.getPosition().y == t_pos.y) 
	{//right
		m_direction.setRotation(0);
	}
	if (m_body.getPosition().x < t_pos.x
		&& m_body.getPosition().y < t_pos.y) 
	{ //down right
		m_direction.setRotation(45);
	}
	if (m_body.getPosition().x == t_pos.x
		&& m_body.getPosition().y < t_pos.y) 
	{//down mid
		m_direction.setRotation(90);
	}
	if (m_body.getPosition().x > t_pos.x
		&& m_body.getPosition().y < t_pos.y) 
	{//down left
		m_direction.setRotation(135);
	}
	if (m_body.getPosition().x > t_pos.x
		&& m_body.getPosition().y == t_pos.y) 
	{//left
		m_direction.setRotation(180);
	}
}
