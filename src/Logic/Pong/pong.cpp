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

Pong::Pong()
{
	m_ball_pos = QPoint(250, 200);
	m_ball_speed = QPoint(20, 20);

	moduleConfig = new ModuleConfig("Pong");

	m_ball      = new QImage(QSize(52, 54),   QImage::Format_RGB16);
	m_ball->load ("Logic/ModuleColorPalette/ball.png");
	m_pad = new QImage(QSize(50, 200), QImage::Format_RGB16);
	m_pad->load ("Logic/Pong/pad.png");
}

void Pong::ProcessSquares (const Square *recognizedSquares, int size)
{
	m_ball_pos.setX(m_ball_pos.x() + m_ball_speed.x());
	m_ball_pos.setY(m_ball_pos.y() + m_ball_speed.y());
	if(m_ball_pos.x() > 600)
	{
		m_ball_pos.setX(600);
		m_ball_speed.setX(-m_ball_speed.x());		
	}
	if(m_ball_pos.x() < 10)
        {
                m_ball_pos.setX(10);
                m_ball_speed.setX(-m_ball_speed.x());               
        }
	if(m_ball_pos.y() > 300)
        {
                m_ball_pos.setY(300);
                m_ball_speed.setY(-m_ball_speed.y());               
        }
        if(m_ball_pos.y() < 10)
        {
                m_ball_pos.setY(10);
                m_ball_speed.setY(-m_ball_speed.y());
        }

	
	Image imgs[2];
	imgs[0] = Image(*m_ball, m_ball_pos);
	QPoint p = QPoint(20, recognizedSquares[0].GetCenterCoordinates().y);
	printf("%d %d\n", p.x(), p.y()); 
	imgs[1] = Image(*m_pad, p);
	emit SquaresProcessed (imgs, 2);
}


//---------------------------------------------------------------
// Destructor.
// Releases used resources.
//---------------------------------------------------------------
Pong::~Pong()
{

}

