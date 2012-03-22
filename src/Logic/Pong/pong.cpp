#include "pong.h"
#include <cstdio>
#include <QtGui/QImage>
#include <QtGui/QColor>
#include <QtGui/QPainter>
#include <QtGui/QImage>
#include <QtGui/QColor>
#include <QtGui/QTransform>
#include <QtCore/QRect>
#include <QThread>
#include <opencv/highgui.h>

const int CANVAS_W = 700;
const int CANVAS_H = 400;
const int BALL_SIZE = 50;
const int PAD_SIZE = 80;
const int LEFTPAD_XPOS = 20;
const int RIGHTPAD_XPOS = 680;

Pong::Pong()
{
	m_leftpad_ypos = m_rightpad_ypos = CANVAS_H / 2 + PAD_SIZE / 2;
	m_ball_pos = QPoint(CANVAS_W / 2, CANVAS_H / 2);
	m_ball_speed = QPoint(15, 15);

	moduleConfig = new ModuleConfig("Pong");

	m_ball = new QImage();
	m_ball->load("Logic/ModuleColorPalette/ball.png");
	m_pad = new QImage();
	m_pad->load("Logic/Pong/pad.png");
}

void Pong::ProcessSquares (const Square *recognizedSquares, int size)
{
	
	for(int i = 0; i < size; i++)
	{
		if(recognizedSquares[i].GetContoursCount() == 1)
		{
			m_leftpad_ypos = recognizedSquares[i].GetCenterCoordinates().y * 5 + PAD_SIZE / 2;
		}
		if(recognizedSquares[i].GetContoursCount() == 2)
		{
			m_rightpad_ypos = recognizedSquares[i].GetCenterCoordinates().y * 5 + PAD_SIZE / 2;
		}
	}
	
	m_ball_pos.setX(m_ball_pos.x() + m_ball_speed.x());
	m_ball_pos.setY(m_ball_pos.y() + m_ball_speed.y());
	
	if(m_ball_pos.x() + BALL_SIZE / 2 > CANVAS_W)
	{
		m_ball_pos.setX(CANVAS_W - BALL_SIZE / 2);
		m_ball_speed.setX(-m_ball_speed.x());		
	}
	if(m_ball_pos.x()- BALL_SIZE / 2 < LEFTPAD_XPOS)
        {
		if(abs(m_leftpad_ypos - m_ball_pos.y()) < PAD_SIZE / 2)
		{
                	m_ball_pos.setX(LEFTPAD_XPOS + BALL_SIZE / 2);
                	m_ball_speed.setX(-m_ball_speed.x());               
		} 
		else 
		{
			m_ball_pos = QPoint(CANVAS_W / 2, CANVAS_H / 2);	
		}
        }
	if(m_ball_pos.y() + BALL_SIZE / 2 > CANVAS_H )
        {
                m_ball_pos.setY(CANVAS_H - BALL_SIZE / 2);
                m_ball_speed.setY(-m_ball_speed.y());               
        }
        if(m_ball_pos.y() < BALL_SIZE / 2)
        {
                m_ball_pos.setY(BALL_SIZE / 2);
                m_ball_speed.setY(-m_ball_speed.y());
        }
	
	Image imgs[3];
	imgs[0] = Image(*m_ball, m_ball_pos);
	QPoint left = QPoint(LEFTPAD_XPOS, m_leftpad_ypos);
	imgs[1] = Image(*m_pad, left);
	QPoint right = QPoint(RIGHTPAD_XPOS, m_rightpad_ypos);		
	imgs[2] = Image(*m_pad, right);		
	emit SquaresProcessed (imgs, 3);
}


//---------------------------------------------------------------
// Destructor.
// Releases used resources.
//---------------------------------------------------------------
Pong::~Pong()
{

}

