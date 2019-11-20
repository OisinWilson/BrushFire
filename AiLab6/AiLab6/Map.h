#pragma once

#include<SFML/Graphics.hpp>
#include<vector>
#include "Tile.h"
#include <iostream>


const int TOTAL_SIZE{25};

class Map
{
public:
	Map();
	void update();
	void render(sf::RenderWindow & t_window);


private:

	sf::Font m_font;
	std::vector<Tile> m_grid;
};

