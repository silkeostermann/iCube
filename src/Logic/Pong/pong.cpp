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
#include <ctime>    
#include <cstdlib> 
   
const int CANVAS_W = 700;
const int CANVAS_H = 400;
const int BALL_SIZE = 50;
const int PAD_SIZE = 120;
const int LEFTPAD_XPOS = 20;
const int RIGHTPAD_XPOS = 680;

Pong::Pong()
{

	score1 = 0;
	score2 = 0;
	srand(time(0));
    	restart();
	m_leftpad_ypos = m_rightpad_ypos = CANVAS_H / 2 + PAD_SIZE / 2;

	moduleConfig = new ModuleConfig("Pong");

	m_ball = new QImage();
	m_ball->load("Logic/Pong/ball.jpg");
	m_pad = new QImage();
	m_pad->load("Logic/Pong/pad.png");
}

void Pong::restart() 
{
	int sign, magnitude;

	m_waiting_counter = 20;
	m_ball_pos = QPoint(CANVAS_W / 2, CANVAS_H / 2);
	sign = rand() % 2;
	if(sign == 0) sign = -1;
	magnitude = 5 + rand() % 11;
	int sx = sign * magnitude;

	if(sign == 0) sign = -1;
	magnitude = 5 + rand() % 11;
	int sy = sign * magnitude;

	m_ball_speed = QPoint(sx, sy);
}

int sign(int v)
{
	return v > 0 ? 1 : (v < 0 ? -1 : 0);
}

void Pong::randomizeSpeed()
{	
	int xsign = sign(m_ball_speed.x());
	int newx = 5 + rand() % 11;
	int ysign = sign(m_ball_speed.y());
	int newy = 5 + rand() % 11;
	m_ball_speed.setX(xsign * newx);
	m_ball_speed.setY(ysign * newy);
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
	
	if(m_waiting_counter > 0)
	{
		m_waiting_counter--;
	} else 
	{
		m_ball_pos.setX(m_ball_pos.x() + m_ball_speed.x());
		m_ball_pos.setY(m_ball_pos.y() + m_ball_speed.y());
	}	

	if(m_ball_pos.x() + BALL_SIZE > RIGHTPAD_XPOS)
	{
		if(abs(m_rightpad_ypos - m_ball_pos.y() + BALL_SIZE/2) < PAD_SIZE / 2)
		{
                	m_ball_pos.setX(RIGHTPAD_XPOS - BALL_SIZE);
                	m_ball_speed.setX(-m_ball_speed.x());   
			randomizeSpeed();            
		} 
		else 
		{
			score1++; 
			restart();	
		}	
	}
	if(m_ball_pos.x() < LEFTPAD_XPOS + 25)
        {
		if(abs(m_leftpad_ypos - m_ball_pos.y()+ BALL_SIZE/2) < PAD_SIZE / 2)
		{
                	m_ball_pos.setX(LEFTPAD_XPOS + 25);
                	m_ball_speed.setX(-m_ball_speed.x());   
			randomizeSpeed();            
		} 
		else 
		{
			score2++;
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
	
	Image imgs[5];

	QString score_1 = QString::number(score1);
	QImage qImage1 = QImage(QSize(50,50), QImage::Format_RGB16);
	QPainter *painter1 = new QPainter(&qImage1);
	painter1->fillRect(0, 0, 50, 50, QColor(240, 240, 240));		
	painter1->setPen(QColor(0,0,0));
	painter1->setFont(QFont("Arial", 24));
	painter1->drawText(0, 25, score_1);
	QPoint point_score1 = QPoint(0, 40);		
	imgs[0] = Image(qImage1,point_score1);	

	QString score_2 = QString::number(score2);
	QImage qImage2 = QImage(QSize(50,50), QImage::Format_RGB16);
	QPainter *painter2 = new QPainter(&qImage2);
	painter2->fillRect(0, 0, 50, 50, QColor(240, 240, 240));			
	painter2->setPen(QColor(0,0,0));
	painter2->setFont(QFont("Arial", 24));
	painter2->drawText(0, 25, score_2);
	QPoint point_score2 = QPoint(720, 40);		
	imgs[1] = Image(qImage2,point_score2);	

	imgs[2] = Image(*m_ball, m_ball_pos);
	QPoint left = QPoint(LEFTPAD_XPOS, m_leftpad_ypos);
	imgs[3] = Image(*m_pad, left);
	QPoint right = QPoint(RIGHTPAD_XPOS, m_rightpad_ypos);		
	imgs[4] = Image(*m_pad, right);	

	emit SquaresProcessed (imgs, 5);

	delete painter1;
	delete painter2;
}


//---------------------------------------------------------------
// Destructor.
// Releases used resources.
//---------------------------------------------------------------
Pong::~Pong()
{

}

