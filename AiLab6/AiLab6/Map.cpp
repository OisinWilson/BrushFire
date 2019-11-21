#include "Map.h"

Map::Map(sf::Font& t_font) :
	m_font(t_font)
{
}

void Map::update()
{
}

void Map::render(sf::RenderWindow& t_window)
{
	for (int i = 0; i < TOTAL_SIZE; i++)
	{
		m_grid[i].render(t_window);
	}
}

void Map::StartPosClick(sf::Vector2i& t_mouseLocation)
{
	m_newInputClick = true;

	int tempX = std::floor(t_mouseLocation.x / 18.0) * 18.0;
	int tempY = std::floor(t_mouseLocation.y / 18.0) * 18.0;


	if (m_priorInputClick)
	{
		if (m_grid[m_startIndex].getTile().getPosition().x == tempX && m_grid[m_startIndex].getTile().getPosition().y == tempY)
		{
			m_grid[m_startIndex].setColour(sf::Color::Blue);
			m_grid[m_startIndex].setCost(-1);
			m_startIndex = -1;
			m_newInputClick = false;
			m_priorInputClick = false;
		}
		else
		{
			m_grid[m_startIndex].setColour(sf::Color::Blue);
			m_grid[m_startIndex].setCost(-1);
			m_priorInputClick = false;
		}
		brushfireClear();
	}


	if (m_newInputClick)
	{
		int temp = getTileIndex(t_mouseLocation);

		if (temp == m_goalIndex)
		{
			m_startIndex = -1;
		}

		m_startIndex = temp;
		m_grid[temp].setCost(0);
		m_priorInputClick = true;
		m_grid[temp].setColour(sf::Color::Red);
		brushfireStart();
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

void Map::wallPosClick(sf::Vector2i& t_mouseLocation)
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
				m_grid[i].setCost(-2);
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
				m_grid[i].setCost(-2);
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
					m_grid[i].setCost(-2);
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
					m_grid[i].setCost(-2);
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
			m_grid[m_wallIndex[i]].setCost(-1);
		}
		brushfireClear();
		brushfireStart();
		m_wallIndex.clear();
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

std::vector<int> Map::brushFire(int t_tileIndex)
{
	std::vector<int> indexes;
	for (int i = 0; i < 8; i++)
	{
		int neighbourIndex = getLocalIndex(i, t_tileIndex);

		if (neighbourIndex != -1)
		{
			if (m_grid[neighbourIndex].getCost() == -1)
			{
				indexes.push_back(neighbourIndex);
			}
		}
	}

	for (int i = 0; i < indexes.size(); i++)
	{
		m_grid[indexes[i]].setCost(m_grid[t_tileIndex].getCost() + 1);


		int cheapistIndex = 0;
		float cheapistCost = INT_MAX;

		for (int q = 0; q < 8; q++)
		{
			int neighbourIndex = getLocalIndex(q, t_tileIndex);

			if (neighbourIndex > -1)
			{
				sf::Vector2f distVec{ m_grid[m_startIndex].getTile().getPosition() - m_grid[neighbourIndex].getTile().getPosition() };

				float disLen = std::sqrt(std::pow(distVec.x, 2) + std::pow(distVec.y, 2));

				if (disLen < cheapistCost)
				{
					cheapistCost = disLen;
					cheapistIndex = neighbourIndex;
				}
			}
		}

		m_grid[t_tileIndex].setFlowField(m_grid[cheapistIndex].getTile().getPosition());

	}


	/*for (int i = 0; i < indexes.size(); i++)
	{
		m_grid[indexes[i]].setCost(m_grid[t_tileIndex].getCost() + 1);
		m_grid[indexes[i]].setFlowField(m_grid[t_tileIndex].getTile().getPosition());

	}*/

	return indexes;
}

int Map::getLocalIndex(int t_desiredIndex, int t_currentIndex)
{

	sf::Vector2f tempLocation = m_grid[t_currentIndex].getTile().getPosition();

	for (int i = 0; i < TOTAL_SIZE; i++)
	{
		switch (t_desiredIndex)
		{
		case 0:
			if ((tempLocation.x - 18) == m_grid[i].getTile().getPosition().x
				&& (tempLocation.y - 18) == m_grid[i].getTile().getPosition().y)
			{
				return i;
			}
			break;
		case 1:
			if ((tempLocation.x) == m_grid[i].getTile().getPosition().x
				&& (tempLocation.y - 18) == m_grid[i].getTile().getPosition().y)
			{
				return i;
			}
			break;
		case 2:
			if ((tempLocation.x + 18) == m_grid[i].getTile().getPosition().x
				&& (tempLocation.y - 18) == m_grid[i].getTile().getPosition().y)
			{
				return i;
			}
			break;
		case 3:
			if ((tempLocation.x + 18) == m_grid[i].getTile().getPosition().x
				&& tempLocation.y == m_grid[i].getTile().getPosition().y)
			{
				return i;
			}
			break;
		case 4:
			if ((tempLocation.x + 18) == m_grid[i].getTile().getPosition().x
				&& (tempLocation.y + 18) == m_grid[i].getTile().getPosition().y)
			{
				return i;
			}
			break;
		case 5:
			if ((tempLocation.x) == m_grid[i].getTile().getPosition().x
				&& (tempLocation.y + 18) == m_grid[i].getTile().getPosition().y)
			{
				return i;
			}
			break;
		case 6:
			if ((tempLocation.x - 18) == m_grid[i].getTile().getPosition().x
				&& (tempLocation.y + 18) == m_grid[i].getTile().getPosition().y)
			{
				return i;
			}
			break;
		case 7:
			if ((tempLocation.x - 18) == m_grid[i].getTile().getPosition().x
				&& (tempLocation.y) == m_grid[i].getTile().getPosition().y)
			{
				return i;
			}
			break;
		default:
			break;
		}
	}

	return -1;
}


int Map::getTileIndex(sf::Vector2i t_mousePos)
{
	int col = t_mousePos.x / 18;
	int row = t_mousePos.y / 18;

	if (col < 0)
	{
		col = 0;
	}
	else if (col > 49)
	{
		col = 49;
	}
	if (row < 0)
	{
		row = 0;
	}
	else if (row > 49)
	{
		row = 49;
	}
	return  row + (col * 50);
}

void Map::brushfireStart()
{
	neighbourIndexVec.push_back(m_startIndex);
	std::vector<int> newNabors;

	while (!neighbourIndexVec.empty())
	{
		newNabors = brushFire(neighbourIndexVec[0]);
		neighbourIndexVec.insert(neighbourIndexVec.end(), newNabors.begin(), newNabors.end());
		neighbourIndexVec.erase(neighbourIndexVec.begin());
		newNabors.clear();
	}
}

void Map::brushfireClear()
{
	for (int i = 0; i < TOTAL_SIZE; i++)
	{
		if (m_grid[i].getCost() > 0)
		{
			m_grid[i].setCost(-1);
			m_grid[i].setColour(sf::Color::Blue);
		}
	}
}