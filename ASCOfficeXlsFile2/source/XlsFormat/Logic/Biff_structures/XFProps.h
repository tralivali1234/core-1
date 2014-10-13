#pragma once

#include "BiffStructure.h"
#include <Logic/Biff_structures/XFProp.h>

namespace XLS
{;

class CFRecord;

class XFProps : public BiffStructure
{
	BASE_OBJECT_DEFINE_CLASS_NAME(XFProps)
public:
	BiffStructurePtr clone();

	//virtual void toXML(BiffStructurePtr & parent);
	//virtual const bool fromXML(BiffStructurePtr & parent);
	virtual void load(CFRecord& record);
	virtual void store(CFRecord& record);

private:
	unsigned __int16 cprops;
	std::vector<XFProp> xfPropArray;
};

} // namespace XLS
