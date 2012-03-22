#ifndef PONG_H
#define PONG_H

#include <QtGui/QImage>
#include "../../Recognition/Square.h"
#include "../Image.h"
#include <qobject.h>
#include "ModuleConfig.h"

//---------------------------------------------------------------
// Represents logic implementation, such strange name because no concrete logic chosen yet
//---------------------------------------------------------------

class Pong : public QObject
{
	Q_OBJECT

  	private:
		QImage *m_ball;
		QImage *m_pad;
		QPoint m_ball_pos;
		QPoint m_ball_speed;
		QPoint m_leftpad_pos;
		QPoint m_rightpad_pos;
  		ModuleConfig *moduleConfig;
		int m_leftpad_ypos, m_rightpad_ypos;
		int m_waiting_counter;
		void restart();	
		void randomizeSpeed();
		int score1;
		int score2;
	public:
		Pong();
		~Pong();

	public slots:
		void ProcessSquares(const Square* squares, int size);

	signals:
		void SquaresProcessed(const Image *image, int size);

};

#endif
