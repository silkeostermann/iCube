#ifndef DYNAMIC_PINGUIN_H
#define DYNAMIC_PINGUIN_H

#include <QtGui/QImage>
#include <QObject>

#include "Logic/ModuleInterface.h"
#include "Logic/Image.h"
#include "Recognition/Square.h"

class DynamicPinguin : public ModuleInterface
{
	Q_OBJECT
	Q_INTERFACES(ModuleInterface)

	private:
  		QImage penguin0, penguin90, penguin180, penguin270;

	public:
		DynamicPinguin();
		~DynamicPinguin();
    QString moduleName();

	public slots:
		void ProcessSquares(const Square* squares, int size);

	signals:
		void SquaresProcessed(const Image *image, int size);

};

#endif
