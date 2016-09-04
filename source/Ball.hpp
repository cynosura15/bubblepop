#ifndef _BALL_HPP_
#define _BALL_HPP_

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
		m_touched = false;

		m_color = RGBA8(rand() % 200 + 50, rand() % 255, rand() % 255, 255);		//note: [1985;2015[ -> rand() 30 + 1985;
		do
			m_x = rand() % (BOT_WIDTH - 2 * (int)m_radius) + (int)m_radius /* or ... + (0+m_radius)*/;	//MIN:0+width, MAX:bot-width, while
		while((m_x+m_radius > prevX-prevRad && m_x-m_radius < prevX+prevRad));
		do
			m_y = rand() % (BOT_HEIGHT - 2 * (int)m_radius) + (int)m_radius;//idem
		while((m_y+m_radius > prevY-prevRad && m_y-m_radius < prevY+prevRad));
	}
	void UpdateAndDraw(touchPosition const& touch)
	{
		printf("\x1b[10;10H%f", radius_init);

		if(hidKeysHeld() & KEY_TOUCH)
			if((touch.px < m_x+m_radius) && (touch.px > m_x-m_radius) && (touch.py < m_y+m_radius) & (touch.py > m_y-m_radius))
			{
				m_touched = true;
				prevX = m_x;
				prevY = m_y;
				prevRad = m_radius;
				if(radius_init > 5)
					radius_init-=0.5;
			}

		m_radius-=0.5;
		if(m_radius <= 0)
			m_lost = true;

		sf2d_draw_fill_circle(m_x, m_y, m_radius, m_color);
	}
	bool newBall()
	{
		return m_touched;
	}
	bool hasLost()
	{
		return m_lost;
	}
	bool hasBeenTouch()
	{
		return m_touched;
	}
private:
	float m_radius_init;
	float m_x, m_y, m_radius;
	bool m_lost, m_canUpdateTouch, m_touched;

	u32 m_color;
};

#endif