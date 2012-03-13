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

	return a.exec();
}
