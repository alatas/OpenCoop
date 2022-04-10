#ifndef __COMPONENT_H
#define __COMPONENT_H

class Context;

class Component
{

public:
  Context *context = nullptr;

  Component(Context *context)
  {
    this->context = context;
  };

  virtual void Setup(){};
  virtual void Loop(){};

private:
};

#endif