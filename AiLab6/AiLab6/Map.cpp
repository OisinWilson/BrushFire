#include "Map.h"

Map::Map()
{
	//sf::VideoMode::getDesktopMode().width;

	if (!m_font.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}


	m_grid.reserve(TOTAL_SIZE);

	m_grid.push_back(Tile(m_font, sf::Vector2f(0, 0)));

}

void Map::update()
{

}

void Map::render(sf::RenderWindow& t_window)
{
	m_grid[0].render(t_window);
}
