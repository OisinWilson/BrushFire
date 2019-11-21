#include "Map.h"

Map::Map(sf::Font & t_font) :
	m_font(t_font)
{
}

void Map::update()
{

}

void Map::render(sf::RenderWindow & t_window)
{
	for (int i = 0; i < TOTAL_SIZE; i++)
	{
		m_grid[i].render(t_window);
	}
}

void Map::StartPosClick(sf::Vector2i & t_mouseLocation)
{
	m_newInputClick = true;

	int tempX = std::floor(t_mouseLocation.x / 18.0) * 18.0;
	int tempY = std::floor(t_mouseLocation.y / 18.0) * 18.0;


	if (m_priorInputClick)
	{
		if (m_grid[m_startIndex].getTile().getPosition().x == tempX && m_grid[m_startIndex].getTile().getPosition().y == tempY)
		{
			m_grid[m_startIndex].setColour(sf::Color::Blue);
			m_startIndex = -1;
			m_newInputClick = false;
			m_priorInputClick = false;
		}
		else
		{
			m_grid[m_startIndex].setColour(sf::Color::Blue);
			m_priorInputClick = false;
		}
	}


	if (m_newInputClick)
	{
		for (int i = 0; i < TOTAL_SIZE; i++)
		{
			if (m_grid[i].getTile().getPosition().x == tempX && m_grid[i].getTile().getPosition().y == tempY)
			{
				if (i == m_goalIndex)
				{
					m_startIndex = -1;
					break;
				}

				m_startIndex = i;
				m_priorInputClick = true;
				m_grid[i].setColour(sf::Color::Red);
				break;
			}
		}
	}
}

void Map::goalPosClick(sf::Vector2i& t_mouseLocation)
{
	m_goalInputClick = true;

	int tempX = std::floor(t_mouseLocation.x / 18.0) * 18.0;
	int tempY = std::floor(t_mouseLocation.y / 18.0) * 18.0;

	if (m_priorGoalClick)
	{
		if (m_grid[m_goalIndex].getTile().getPosition().x == tempX && m_grid[m_goalIndex].getTile().getPosition().y == tempY)
		{
			m_grid[m_goalIndex].setColour(sf::Color::Blue);
			m_goalIndex = -1;
			m_goalInputClick = false;
			m_priorGoalClick = false;
		}
		else
		{
			m_grid[m_goalIndex].setColour(sf::Color::Blue);
			m_priorGoalClick = false;
		}
	}


	if (m_goalInputClick)
	{
		for (int i = 0; i < TOTAL_SIZE; i++)
		{
			if (m_grid[i].getTile().getPosition().x == tempX && m_grid[i].getTile().getPosition().y == tempY)
			{
				if (i == m_startIndex)
				{
					m_goalIndex = -1;
					break;
				}

				m_goalIndex = i;
				m_priorGoalClick = true;
				m_grid[i].setColour(sf::Color::Green);
				break;
			}
		}
	}
}

void Map::wallPosClick(sf::Vector2i & t_mouseLocation)
{
	int tempX = std::floor(t_mouseLocation.x / 18.0) * 18.0;
	int tempY = std::floor(t_mouseLocation.y / 18.0) * 18.0;

	if (m_goalIndex == -1 && m_startIndex == -1)
	{
		for (int i = 0; i < TOTAL_SIZE; i++)
		{
			if (m_grid[i].getTile().getPosition().x == tempX
				&& m_grid[i].getTile().getPosition().y == tempY)
			{
				m_wallIndex.push_back(i);
				m_grid[i].setColour(sf::Color::Black);
			}
		}
	}
	else if (m_goalIndex > -1 && m_startIndex > -1)
	{
		for (int i = 0; i < TOTAL_SIZE; i++)
		{
			if (m_grid[i].getTile().getPosition().x == tempX && m_grid[i].getTile().getPosition().y == tempY
				&& !(m_grid[m_goalIndex].getTile().getPosition().x == tempX && m_grid[m_goalIndex].getTile().getPosition().y == tempY)
				&& !(m_grid[m_startIndex].getTile().getPosition().x == tempX && m_grid[m_startIndex].getTile().getPosition().y == tempY))
			{
				m_wallIndex.push_back(i);
				m_grid[i].setColour(sf::Color::Black);
			}
		}
	}
	else
	{
		if (m_goalIndex > -1)
		{
			for (int i = 0; i < TOTAL_SIZE; i++)
			{
				if (m_grid[i].getTile().getPosition().x == tempX && m_grid[i].getTile().getPosition().y == tempY
					&& !(m_grid[m_goalIndex].getTile().getPosition().x == tempX && m_grid[m_goalIndex].getTile().getPosition().y == tempY))
				{
					m_wallIndex.push_back(i);
					m_grid[i].setColour(sf::Color::Black);
				}
			}
		}
		else if (m_startIndex > -1)
		{
			for (int i = 0; i < TOTAL_SIZE; i++)
			{
				if (m_grid[i].getTile().getPosition().x == tempX && m_grid[i].getTile().getPosition().y == tempY
					&& !(m_grid[m_startIndex].getTile().getPosition().x == tempX && m_grid[m_startIndex].getTile().getPosition().y == tempY))
				{
					m_wallIndex.push_back(i);
					m_grid[i].setColour(sf::Color::Black);
				}
			}
		}
	}

	
}

void Map::resetWalls()
{
	if (m_wallIndex.size() > 0)
	{
		for (int i = 0; i < m_wallIndex.size(); i++)
		{
			m_grid[m_wallIndex[i]].setColour(sf::Color::Blue);
		}
		m_wallIndex.empty();
	}
}

void Map::valueDisplayChange()
{
	for (int i = 0; i < TOTAL_SIZE; i++)
	{
		m_grid[i].toggleTextDisplay();
	}
}

void Map::init()
{
	m_grid.reserve(TOTAL_SIZE);

	for (int i = 0; i < 50; i++)
	{
		for (int q = 0; q < 50; q++)
		{
			Tile temp(m_font, sf::Vector2f(18.0f * i, 18.0f * q));
			m_grid.push_back(temp);
		}
	}
}
