#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H

#include "IRender.h"
#include <vector>
class RenderManager
{
public:
    RenderManager();
    void render() const;
    int registerRenderer(IRender *renderer);
    IRender* unregisterRenderer(int rendererId);

private:
    std::vector<IRender*>* renderers;
};

#endif
