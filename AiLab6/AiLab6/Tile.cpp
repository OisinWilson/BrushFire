#include "Tile.h"

Tile::Tile(sf::Font & t_font, sf::Vector2f & t_pos) :
	m_font(t_font)
{
	m_body.setSize(sf::Vector2f(30, 30));
	m_body.setPosition(t_pos);
	m_body.setFillColor(sf::Color::Red);



	m_text.setFont(m_font);
	m_text.setCharacterSize(30);

	m_displayText = false;
}

void Tile::update()
{
}

void Tile::render(sf::RenderWindow & t_renderWindow)
{
	t_renderWindow.draw(m_body);

	if (m_displayText)
		t_renderWindow.draw(m_text);
}

void Tile::setText(sf::String & t_InputText)
{
	m_text.setString(t_InputText);
}

void Tile::toggleTextDisplay()
{
	m_displayText = !m_displayText;
}