#pragma once

#include <Logic/CompositeObject.h>

namespace XLS
{;


// Logical representation of BACKGROUND union of records 
class BACKGROUND: public CompositeObject
{
	BASE_OBJECT_DEFINE_CLASS_NAME(BACKGROUND)
public:
	BACKGROUND();
	~BACKGROUND();

	BaseObjectPtr clone();

	virtual const bool loadContent(BinProcessor& proc);

};

} // namespace XLS

