#include "Tile.h"

Tile::Tile(sf::Font & t_font, sf::Vector2f t_pos) :
	m_font(t_font)
{
	m_body.setSize(sf::Vector2f(18, 18));
	m_body.setPosition(t_pos);
	m_body.setFillColor(sf::Color::Blue);
	m_body.setOutlineThickness(1);
	m_body.setOutlineColor(sf::Color::Black);

	m_text.setFont(m_font);
	m_text.setString("1");
	m_text.setCharacterSize(10);
	m_text.setPosition(m_body.getPosition());
}

void Tile::update()
{
}

void Tile::render(sf::RenderWindow & t_renderWindow)
{
	t_renderWindow.draw(m_body);

	if (m_displayText)
	{
		t_renderWindow.draw(m_text);
	}
}

void Tile::setText(sf::String & t_InputText)
{
	m_text.setString(t_InputText);
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

sf::RectangleShape Tile::getTile()
{
	return m_body;
}
