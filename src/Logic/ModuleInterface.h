class ModuleInterface
{
public:
  virtual ~ModuleInterface() {}
  
  virtual QString moduleName() = 0;
  // virtual void ProcessSquares();
};

Q_DECLARE_INTERFACE(ModuleInterface, "org.iCubes.ModuleInterface/1.0")