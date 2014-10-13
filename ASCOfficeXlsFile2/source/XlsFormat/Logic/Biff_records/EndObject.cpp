#include "precompiled_xls.h"
#include "EndObject.h"
#include <Logic/Biff_structures/FrtHeaderOld.h>

namespace XLS
{;

EndObject::EndObject()
{
}


EndObject::~EndObject()
{
}


BaseObjectPtr EndObject::clone()
{
	return BaseObjectPtr(new EndObject(*this));
}


void EndObject::writeFields(CFRecord& record)
{
	FrtHeaderOld rt(rt_EndObject);
	record >> rt;
	unsigned __int16 unused1 = 0, unused2 = 0, unused3 = 0;
	record << iObjectKind << unused1 << unused2 << unused3;
}


void EndObject::readFields(CFRecord& record)
{
	FrtHeaderOld rt;
	record >> rt;
	unsigned __int16 unused1, unused2, unused3;
	record >> iObjectKind >> unused1 >> unused2 >> unused3;
}

} // namespace XLS

