#ifndef __STATE_H
#define __STATE_H

class Context;

class State
{
protected:
public:
  Context *context;

  State(Context *context)
  {
    this->context = context;
  };

  virtual void Setup() {}
  virtual void Loop() {}
};

#endif