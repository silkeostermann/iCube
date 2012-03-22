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
const int PAD_SIZE = 120;
const int LEFTPAD_XPOS = 20;
const int RIGHTPAD_XPOS = 680;

Pong::Pong()
{
	m_leftpad_ypos = m_rightpad_ypos = CANVAS_H / 2 + PAD_SIZE / 2;
	m_ball_pos = QPoint(CANVAS_W / 2, CANVAS_H / 2);
	m_ball_speed = QPoint(10, 10);

	moduleConfig = new ModuleConfig("Pong");

	m_ball = new QImage();
	m_ball->load("Logic/Pong/ball.jpg");
	m_pad = new QImage();
	m_pad->load("Logic/Pong/pad.png");
}

void Pong::restart() 
{
	m_ball_pos = QPoint(CANVAS_W / 2, CANVAS_H / 2);
}

void Pong::ProcessSquares (const Square *recognizedSquares, int size)
{
	
	for(int i = 0; i < size; i++)
	{
		int pos = (recognizedSquares[i].GetCenterCoordinates().y - 50) * 10 + CANVAS_H / 2;
		if(recognizedSquares[i].GetContoursCount() == 1)
		{			
			m_leftpad_ypos = pos;
		}
		if(recognizedSquares[i].GetContoursCount() == 2)
		{
			m_rightpad_ypos = pos;
		}
	}
	
	m_ball_pos.setX(m_ball_pos.x() + m_ball_speed.x());
	m_ball_pos.setY(m_ball_pos.y() + m_ball_speed.y());
	
	if(m_ball_pos.x() + BALL_SIZE > RIGHTPAD_XPOS)
	{
		//printf("%d %d\n", m_rightpad_ypos, m_ball_pos.y());
		if(abs(m_rightpad_ypos - m_ball_pos.y() + BALL_SIZE/2) < PAD_SIZE / 2)
		{
                	m_ball_pos.setX(RIGHTPAD_XPOS - BALL_SIZE);
                	m_ball_speed.setX(-m_ball_speed.x());               
		} 
		else 
		{
			restart();	
		}	
	}
	if(m_ball_pos.x() < LEFTPAD_XPOS + 15)
        {
		if(abs(m_leftpad_ypos - m_ball_pos.y()+ BALL_SIZE/2) < PAD_SIZE / 2)
		{
                	m_ball_pos.setX(LEFTPAD_XPOS + 15);
                	m_ball_speed.setX(-m_ball_speed.x());               
		} 
		else 
		{
			restart();	
		}
        }
	if(m_ball_pos.y() + BALL_SIZE > CANVAS_H)
        {
                m_ball_pos.setY(CANVAS_H - BALL_SIZE);
                m_ball_speed.setY(-m_ball_speed.y());               
        }
        if(m_ball_pos.y() < 0)
        {
                m_ball_pos.setY(0);
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

