#include "icubes.h"

#include <QtGui>
#include <QApplication>
#include <stdio.h>
#include <opencv2/core/core_c.h>

#include "Recognition/Square.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    iCubes w;
    w.show();

	ColorPalette *palette = new ColorPalette();
	CvPoint p = cvPoint(3, 4);
	Square *sq1 = new Square(1, p, 5, 6);
	Square *squares[1] = {sq1};
	palette->ProcessSquares((const Square **)squares);

	return a.exec();
}
