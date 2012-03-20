#include <QtGui>
#include <QtGui/QPainter>
#include <QtGui/QColor>
#include <QtGui/QFont>

#include "BlankLogic.h"


BlankLogic::BlankLogic() {
  
}

QString BlankLogic::moduleName() {
  return "Blank Logic!";
}

void BlankLogic::ProcessSquares(const Square* recognizedSquares, int size) {
  printf("Processing squares\n");
}

BlankLogic::~BlankLogic () {

}

Q_EXPORT_PLUGIN2(cubes_blanklogic, BlankLogic)