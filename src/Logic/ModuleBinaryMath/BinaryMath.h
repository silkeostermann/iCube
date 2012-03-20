#ifndef BINARY_MATH_H
#define BINARY_MATH_H

#include <string>
#include <qobject.h>

#include "../ModuleInterface.h"
#include "../../Recognition/Square.h"
#include "../Image.h"
#include "ModuleConfig.h"

using namespace std;

class BinaryMath : public ModuleInterface
{
	Q_OBJECT

	public:
    BinaryMath();
		~BinaryMath();
    QString moduleName();

	public slots:
		void ProcessSquares(const Square* squares, int size);

	signals:
		void SquaresProcessed(const Image *image, int size);
	
	private:
		string executeOperation(char operation, string *numberStrings, int clusterSize);
		char resolveOperation(vector<Square> operatorSquares);
		bool isSquareNumber(Square *square);
		char binNumberCharForSquare(Square *square);
		
		ModuleConfig *moduleConfig;

};

#endif
