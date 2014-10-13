#include "precompiled_xls.h"
#include "Stxp.h"
#include <Binary/CFRecord.h>

namespace XLS
{;


BiffStructurePtr Stxp::clone()
{
	return BiffStructurePtr(new Stxp(*this));
}


//void Stxp::setXMLAttributes(MSXML2::IXMLDOMElementPtr xml_tag)
//{
//	xml_tag->setAttribute(L"twpHeight", twpHeight);
//	xml_tag->setAttribute(L"ftsItalic", Boolean<unsigned char>(ts.ftsItalic));
//	xml_tag->setAttribute(L"ftsStrikeout", Boolean<unsigned char>(ts.ftsStrikeout));
//	xml_tag->setAttribute(L"bls", bls);
//	xml_tag->setAttribute(L"sss", sss);
//	xml_tag->setAttribute(L"uls", uls);
//	xml_tag->setAttribute(L"bFamily", bFamily);
//	xml_tag->setAttribute(L"bCharSet", bCharSet);
//}
//
//
//void Stxp::getXMLAttributes(MSXML2::IXMLDOMElementPtr xml_tag)
//{
//	twpHeight = getStructAttribute(xml_tag, L"twpHeight");
//	Boolean<unsigned char> ts_ftsItalic;
//	ts_ftsItalic.fromXML(xml_tag, L"ftsItalic");
//	ts.ftsItalic = ts_ftsItalic;
//	Boolean<unsigned char> ts_ftsStrikeout;
//	ts_ftsStrikeout.fromXML(xml_tag, L"ftsStrikeout");
//	ts.ftsStrikeout = ts_ftsStrikeout;
//	bls = getStructAttribute(xml_tag, L"bls");
//	sss = getStructAttribute(xml_tag, L"sss");
//	uls = getStructAttribute(xml_tag, L"uls");
//	bFamily = getStructAttribute(xml_tag, L"bFamily");
//	bCharSet = getStructAttribute(xml_tag, L"bCharSet");
//}
//
//
void Stxp::store(CFRecord& record)
{
	record << twpHeight << ts << bls << sss << uls << bFamily << bCharSet;
	record.reserveNunBytes(1); // unused
}


void Stxp::load(CFRecord& record)
{
	record >> twpHeight >> ts >> bls >> sss >> uls >> bFamily >> bCharSet;
	record.skipNunBytes(1); // unused
}


} // namespace XLS

