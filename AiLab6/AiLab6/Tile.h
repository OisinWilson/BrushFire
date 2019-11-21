#pragma once

#include<SFML/Graphics.hpp>
#include<vector>


class Tile
{
public:
	Tile(sf::Font & t_font, sf::Vector2f t_pos);

	void update();
	void render(sf::RenderWindow & t_renderWindow);

	void setText(sf::String & t_InputText);

	void toggleTextDisplay();


	void setColour(sf::Color t_colour);
	sf::Color getColour();


	sf::RectangleShape getTile();


private:


	sf::RectangleShape m_body;

	sf::Font & m_font;
	sf::Text m_text;

	bool m_displayText{ false };

};

