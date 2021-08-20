#pragma once

#include <math.h>

// ��ǥ�� �����ϱ� ���� ��ü ����!
struct Point
{
private:
	int m_x, m_y;

public:
	Point()
	{
		m_x = m_y = 0;
	}

	void SetPos(int a_x, int a_y)
	{
		m_x = a_x;
		m_y = a_y;
	}

	int &SetX()
	{
		return m_x;
	}

	int &SetY()
	{
		return m_y;
	}

	int GetX()
	{
		return m_x;
	}

	int GetY()
	{
		return m_y;
	}

	double GetDistance(Point a_targer_pos)
	{
		double distance = sqrt(pow(a_targer_pos.GetX() - this->GetX(), 2) +
			pow(a_targer_pos.GetY() - this->GetY(), 2));
		return distance;
	}
};
