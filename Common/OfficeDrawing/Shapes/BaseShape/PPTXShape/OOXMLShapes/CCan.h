#pragma once
#include "../PPTXShape.h"

namespace OOXMLShapes
{
	class CCan : public CPPTXShape
	{
		public:
			CCan()
			{
				LoadFromXML(
					_T("<ooxml-shape>")
					_T("<avLst xmlns=\"http://schemas.openxmlformats.org/drawingml/2006/main\">")
					  _T("<gd name=\"adj\" fmla=\"val 25000\" />")
					_T("</avLst>")
					_T("<gdLst xmlns=\"http://schemas.openxmlformats.org/drawingml/2006/main\">")
					  _T("<gd name=\"maxAdj\" fmla=\"*/ 50000 h ss\" />")
					  _T("<gd name=\"a\" fmla=\"pin 0 adj maxAdj\" />")
					  _T("<gd name=\"y1\" fmla=\"*/ ss a 200000\" />")
					  _T("<gd name=\"y2\" fmla=\"+- y1 y1 0\" />")
					  _T("<gd name=\"y3\" fmla=\"+- b 0 y1\" />")
					_T("</gdLst>")
					_T("<ahLst xmlns=\"http://schemas.openxmlformats.org/drawingml/2006/main\">")
					  _T("<ahXY gdRefY=\"adj\" minY=\"0\" maxY=\"maxAdj\">")
						_T("<pos x=\"hc\" y=\"y2\" />")
					  _T("</ahXY>")
					_T("</ahLst>")
					_T("<cxnLst xmlns=\"http://schemas.openxmlformats.org/drawingml/2006/main\">")
					  _T("<cxn ang=\"3cd4\">")
						_T("<pos x=\"hc\" y=\"y2\" />")
					  _T("</cxn>")
					  _T("<cxn ang=\"3cd4\">")
						_T("<pos x=\"hc\" y=\"t\" />")
					  _T("</cxn>")
					  _T("<cxn ang=\"cd2\">")
						_T("<pos x=\"l\" y=\"vc\" />")
					  _T("</cxn>")
					  _T("<cxn ang=\"cd4\">")
						_T("<pos x=\"hc\" y=\"b\" />")
					  _T("</cxn>")
					  _T("<cxn ang=\"0\">")
						_T("<pos x=\"r\" y=\"vc\" />")
					  _T("</cxn>")
					_T("</cxnLst>")
					_T("<rect l=\"l\" t=\"y2\" r=\"r\" b=\"y3\" xmlns=\"http://schemas.openxmlformats.org/drawingml/2006/main\" />")
					_T("<pathLst xmlns=\"http://schemas.openxmlformats.org/drawingml/2006/main\">")
					  _T("<path stroke=\"false\" extrusionOk=\"false\">")
						_T("<moveTo>")
						  _T("<pt x=\"l\" y=\"y1\" />")
						_T("</moveTo>")
						_T("<arcTo wR=\"wd2\" hR=\"y1\" stAng=\"cd2\" swAng=\"-10800000\" />")
						_T("<lnTo>")
						  _T("<pt x=\"r\" y=\"y3\" />")
						_T("</lnTo>")
						_T("<arcTo wR=\"wd2\" hR=\"y1\" stAng=\"0\" swAng=\"cd2\" />")
						_T("<close />")
					  _T("</path>")
					  _T("<path stroke=\"false\" fill=\"lighten\" extrusionOk=\"false\">")
						_T("<moveTo>")
						  _T("<pt x=\"l\" y=\"y1\" />")
						_T("</moveTo>")
						_T("<arcTo wR=\"wd2\" hR=\"y1\" stAng=\"cd2\" swAng=\"cd2\" />")
						_T("<arcTo wR=\"wd2\" hR=\"y1\" stAng=\"0\" swAng=\"cd2\" />")
						_T("<close />")
					  _T("</path>")
					  _T("<path fill=\"none\" extrusionOk=\"false\">")
						_T("<moveTo>")
						  _T("<pt x=\"r\" y=\"y1\" />")
						_T("</moveTo>")
						_T("<arcTo wR=\"wd2\" hR=\"y1\" stAng=\"0\" swAng=\"cd2\" />")
						_T("<arcTo wR=\"wd2\" hR=\"y1\" stAng=\"cd2\" swAng=\"cd2\" />")
						_T("<lnTo>")
						  _T("<pt x=\"r\" y=\"y3\" />")
						_T("</lnTo>")
						_T("<arcTo wR=\"wd2\" hR=\"y1\" stAng=\"0\" swAng=\"cd2\" />")
						_T("<lnTo>")
						  _T("<pt x=\"l\" y=\"y1\" />")
						_T("</lnTo>")
					  _T("</path>")
					_T("</pathLst>")
					_T("</ooxml-shape>")
				);
			}
	};
}