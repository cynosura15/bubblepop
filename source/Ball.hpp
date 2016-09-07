#ifndef _BALL_HPP_
#define _BALL_HPP_

#include "commun.h"

int prevX, prevY, prevRad;
float radius_init = 50., radius_init_easy = 70.;

class Ball
{
public:
	Ball()
	{
		if(easy_mode)
			m_radius = radius_init_easy;
		else
			m_radius = radius_init;
		m_canUpdateTouch = true;
		m_lost = false;

		SetNewPos();
	}
	void UpdateAndDraw(touchPosition const* touch, unsigned& score, bool const& pause)
	{
		if(!pause)
		{
			if(hidKeysHeld() & KEY_TOUCH)
			{
				if(easy_mode || !m_canUpdateTouch)
					if((touch->px - m_x)*(touch->px - m_x) + (touch->py - m_y)*(touch->py - m_y) <= m_radius*m_radius)	//fun fact: ^ give me an error and I'm too lazy to fix it
					{
						if(!easy_mode) m_canUpdateTouch = true;
						
						score++;

						prevX = m_x;
						prevY = m_y;
						prevRad = m_radius;
						if(!easy_mode)
							if(radius_init > 5)
								radius_init-=0.5;
						else
							if(radius_init_easy > 5)
								radius_init_easy-=0.5;
							
						m_radius = radius_init;

						SetNewPos();
					}
			}

			else
				if(!easy_mode) m_canUpdateTouch = false;

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
	void SetNewPos()	//TODO: improve
	{
		m_color = RGBA8(rand() % 200 + 40, rand() % 255, rand() % 255, 255);		//note: [1985;2015[ -> rand() 30 + 1985;
		do
		{
			if(!easy_mode)
			{
				m_x = rand() % (BOT_WIDTH - (int)m_radius) + 0;
				m_y = rand() % (BOT_HEIGHT - (int)m_radius) + 0;
			}
			else
			{
				m_x = rand() % (BOT_HEIGHT - 40 - (int)m_radius)+ (40 + m_radius);
				m_y = rand() % (BOT_HEIGHT - 2 * (int)m_radius) + 0;
			}
		}while((m_x+m_radius > prevX-prevRad && m_x-m_radius < prevX+prevRad) && (m_y+m_radius > prevY-prevRad && m_y-m_radius < prevY+prevRad));
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