#ifndef _BALL_HPP_
#define _BALL_HPP_

#include "commun.h"

int prevX, prevY, prevRad;
float radius_init = 50.;

class Ball
{
public:
	Ball()
	{
		m_radius = radius_init;
		m_canUpdateTouch = true;
		m_lost = false;

		SetNewPos();
	}
	void UpdateAndDraw(touchPosition const* touch, unsigned& score, bool const pause)
	{
		if(!pause)
		{
			if(hidKeysHeld() & KEY_TOUCH)
			{
				if(!m_canUpdateTouch)
					if((touch->px - m_x)*(touch->px - m_x) + (touch->py - m_y)*(touch->py - m_y) <= m_radius*m_radius)	//fun fact: ^ give me an error and I'm too lazy to fix it
					{
						m_canUpdateTouch = true;
						
						score++;

						prevX = m_x;
						prevY = m_y;
						prevRad = m_radius;
						if(radius_init > 5)
							radius_init-=0.5;
						m_radius = radius_init;

						SetNewPos();
					}
			}

			else
				m_canUpdateTouch = false;

			m_radius-=0.5;
			if(m_radius <= 0)
				m_lost = true;
		}

		sf2d_draw_fill_circle(m_x, m_y, m_radius, m_color);
	}
	bool hasLost()
	{
		return m_lost;
	}
	void SetNewPos()
	{
		m_color = RGBA8(rand() % 200 + 50, rand() % 255, rand() % 255, 255);		//note: [1985;2015[ -> rand() 30 + 1985;
		do
			m_x = rand() % (BOT_WIDTH - 2 * (int)m_radius) + (int)m_radius /* or ... + (0+m_radius)*/;	//MIN:0+width, MAX:bot-width, while
		while((m_x+m_radius > prevX-prevRad && m_x-m_radius < prevX+prevRad));
		do
			m_y = rand() % (BOT_HEIGHT - 2 * (int)m_radius) + (int)m_radius;//idem
		while((m_y+m_radius > prevY-prevRad && m_y-m_radius < prevY+prevRad));
	}
	void Reset()
	{
		radius_init = 50.;
	}
private:
	float m_x, m_y, m_radius;
	bool m_lost, m_canUpdateTouch;

	u32 m_color;
};

#endif