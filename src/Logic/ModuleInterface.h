class ModuleInterface
{
public:
  virtual ~ModuleInterface() {}
  
  virtual ModuleName();
  virtual ProcessSquares();
};

Q_DECLARE_INTERFACE(ModuleInterface, "org.iCubes.ModuleInterface/1.0")