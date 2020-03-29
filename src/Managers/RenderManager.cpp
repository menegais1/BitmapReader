#include "RenderManager.h"
#include <vector>
#include <iostream>
using namespace std;

RenderManager::RenderManager()
{
}

void RenderManager::render() const
{

    for(int i =0; i< renderers.size();i++){
        renderers[i]->render();
    }

}

int RenderManager::registerRenderer(IRender *renderer)
{
    renderers.push_back(renderer);
    return renderers.size() - 1;
}

IRender *RenderManager::unregisterRenderer(int rendererId)
{
    IRender *renderer = renderers[rendererId];
    renderers.erase(renderers.begin() + rendererId);
    return renderer;
}
