#ifndef VIEW_3D_H
#define VIEW_3D_H

#include "View.h"

class View_3D : public View
{
public:
	View_3D(Model* model) : View(model) {}
	~View_3D();

protected:
	virtual void RenderWorldSceneNode(SceneNode *node = nullptr);
};

#define RENDEROBB

#endif