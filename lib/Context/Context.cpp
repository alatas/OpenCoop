#include <Context.h>

Context::Context()
{
}

void Context::AddComponent(Component *component)
{
  components[lastIndex] = component;
  lastIndex++;
}

void Context::Setup()
{
  for (int i = 0; i < lastIndex; i++)
  {
    Component *component = components[i];
    if (component)
      component->Setup();
  }
}

void Context::Loop()
{
  for (int i = 0; i < lastIndex; i++)
  {
    Component *component = components[i];
    if (component)
      component->Loop();
  }

  if (state)
    state->Loop();
}