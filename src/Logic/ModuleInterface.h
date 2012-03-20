#ifndef MODULE_INTERFACE_H
#define MODULE_INTERFACE_H

#include <QtPlugin>
#include <QObject>

#include "Recognition/Square.h"

class ModuleInterface : public QObject
{
  // Q_OBJECT
  
  public:
    virtual ~ModuleInterface() {}
  
    virtual QString moduleName() = 0;
  
  public slots:
    virtual void ProcessSquares(const Square* squares, int size) = 0;
};

Q_DECLARE_INTERFACE(ModuleInterface, "org.iCubes.ModuleInterface/1.0")

#endif