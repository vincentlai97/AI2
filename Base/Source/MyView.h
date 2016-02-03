#ifndef MYVIEW_H
#define MYVIEW_H

#include "View_3D.h"

class MyView : public View
{
public:
	MyView(Model *model);
	~MyView();

	virtual void Render();

private:
};

#endif