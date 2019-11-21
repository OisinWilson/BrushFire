#pragma once

#include<SFML/Graphics.hpp>
#include<vector>
#include "Tile.h"
#include <iostream>


const int TOTAL_SIZE{2500};

class Map
{
public:
	Map(sf::Font & t_font);
	void update();
	void render(sf::RenderWindow & t_window);
	void StartPosClick(sf::Vector2i & t_mouseLocation);
	void goalPosClick(sf::Vector2i & t_mouseLocation);
	void wallPosClick(sf::Vector2i & t_mouseLocation);
	void resetWalls();
	void valueDisplayChange();
	void init();
	std::vector<int> brushFire(int t_tileIndex);

	int getLocalIndex(int t_desiredIndex, int t_currentIndex);

	int getTileIndex(sf::Vector2i t_mousePos);

	std::vector<int> neighbourIndexVec;

	void brushfireStart();
	void brushfireClear();


private:

	bool m_priorInputClick{ false };
	bool m_newInputClick{ false };


	bool m_goalInputClick{ false };
	bool m_priorGoalClick{ false };

	int m_startIndex = -1;
	int m_goalIndex = -1;

	std::vector<int> m_wallIndex;

	sf::Font & m_font;
	std::vector<Tile> m_grid;
};

