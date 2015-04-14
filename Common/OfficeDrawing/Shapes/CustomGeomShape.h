#pragma once
#include ".\..\BinaryReader.h"
#include ".\..\ElementSettings.h"
#include "BaseShape\BaseShape.h"
#include "..\Attributes.h"

using namespace NSAttributes;
using namespace NSGuidesVML;

namespace NSCustomVML
{
	class CSegment
	{
	public:
		RulesType m_eRuler;
		WORD m_nCount;

	public:
		CSegment(RulesType eType = rtMoveTo, WORD nCount = 2)
		{
			m_eRuler = eType;
			m_nCount = nCount;
		}

		CSegment(const CSegment& oSrc)
		{
			m_eRuler = oSrc.m_eRuler;
			m_nCount = oSrc.m_nCount;
		}

		CSegment& operator=(const CSegment& oSrc)
		{
			m_eRuler = oSrc.m_eRuler;
			m_nCount = oSrc.m_nCount;
			
			return (*this);
		}

		~CSegment()
		{
		}

		void Read(IStream* pStream)
		{
			WORD mem = StreamUtils::ReadWORD(pStream);

			BYTE type = mem & 0x07;
			if (type <= 4)
			{
				m_eRuler	= (RulesType)type;
				m_nCount	= (mem >> 3) & 0x1FFF;
				return;
			}

			mem = (mem >> 3) & 0x1FFF;
			type = mem & 0x1F;

			switch (type)
			{
			case 0x00:
				{
					m_eRuler = rtLineTo;
					break;
				}
			case 0x01:
				{
					m_eRuler = rtAngleEllipseTo;
					break;
				}
			case 0x02:
				{
					m_eRuler = rtAngleEllipse;
					break;
				}
			case 0x03:
				{
					m_eRuler = rtArcTo;
					break;
				}
			case 0x04:
				{
					m_eRuler = rtArc;
					break;
				}
			case 0x05:
				{
					m_eRuler = rtClockwiseArcTo;
					break;
				}
			case 0x06:
				{
					m_eRuler = rtClockwiseArc;
					break;
				}
			case 0x07:
				{
					m_eRuler = rtEllipticalQuadrX;
					break;
				}
			case 0x08:
				{
					m_eRuler = rtEllipticalQuadrY;
					break;
				}
			case 0x09:
				{
					m_eRuler = rtQuadrBesier;
					break;
				}
			case 0x0A:
				{
					m_eRuler = rtNoFill;
					break;
				}
			case 0x0B:
				{
					m_eRuler = rtNoStroke;
					break;
				}
			case 0x15:
				{
					m_eRuler = rtFillColor;
					break;
				}
			case 0x16:
				{
					m_eRuler = rtLineColor;
					break;
				}
			default:
				{
					m_eRuler = rtCurveTo;
				}
			};

			m_nCount = (mem >> 5) & 0x00FF;
		}

		void Read(NSOfficeDrawing::CBinaryReader& oReader)
		{
			WORD mem = oReader.ReadWORD();

			BYTE type = (mem >> 13 & 0x07);
			if (type <= 4)
			{
				m_eRuler	= (RulesType)type;
				m_nCount	= (mem & 0x1FFF);
				//m_nCount = (WORD)GetCountPoints2(m_eRuler);
				m_nCount = (WORD)GetCountPoints2(m_eRuler, m_nCount);
				return;
			}

			type = (mem >> 8) & 0x1F;
			mem = mem & 0xFF;

			switch (type)
			{
			case 0x00:
				{
					m_eRuler = rtLineTo;
					break;
				}
			case 0x01:
				{
					m_eRuler = rtAngleEllipseTo;
					break;
				}
			case 0x02:
				{
					m_eRuler = rtAngleEllipse;
					break;
				}
			case 0x03:
				{
					m_eRuler = rtArcTo;
					break;
				}
			case 0x04:
				{
					m_eRuler = rtArc;
					break;
				}
			case 0x05:
				{
					m_eRuler = rtClockwiseArcTo;
					break;
				}
			case 0x06:
				{
					m_eRuler = rtClockwiseArc;
					break;
				}
			case 0x07:
				{
					m_eRuler = rtEllipticalQuadrX;
					break;
				}
			case 0x08:
				{
					m_eRuler = rtEllipticalQuadrY;
					break;
				}
			case 0x09:
				{
					m_eRuler = rtQuadrBesier;
					break;
				}
			case 0x0A:
				{
					m_eRuler = rtNoFill;
					break;
				}
			case 0x0B:
				{
					m_eRuler = rtNoStroke;
					break;
				}
			case 0x0C:
			case 0x10:
				{
					m_eRuler = rtLineTo;
					break;
				}
			case 0x0D:
			case 0x0E:
			case 0x0F:
			case 0x11:
			case 0x12:
			case 0x13:
			case 0x14:
				{
					m_eRuler = rtCurveTo;
					break;
				}
			case 0x15:
				{
					m_eRuler = rtFillColor;
					break;
				}
			case 0x16:
				{
					m_eRuler = rtLineColor;
					break;
				}
			default:
				{
					m_eRuler = rtCurveTo;
				}
			};

			m_nCount = (WORD)mem;
			m_nCount = (WORD)GetCountPoints2(m_eRuler, m_nCount);
			//m_nCount = (WORD)GetCountPoints2(m_eRuler);
		}
	};

	class CGuide
	{
	private:
		FormulaType m_eType;

		BYTE m_param_type1;
		BYTE m_param_type2;
		BYTE m_param_type3;

		WORD m_param_value1;
		WORD m_param_value2;
		WORD m_param_value3;

		LONG m_lShapeWidth;
		LONG m_lShapeHeight;

	public:

		CGuide()
		{
			m_eType = ftVal;

			m_param_type1 = 0;
			m_param_type2 = 0;
			m_param_type3 = 0;

			m_param_value1 = 0;
			m_param_value2 = 0;
			m_param_value3 = 0;

			m_lShapeWidth	= ShapeSizeVML;
			m_lShapeHeight	= ShapeSizeVML;
		}

		CGuide(const CGuide& oSrc)
		{
			*this = oSrc;
		}

		CGuide& operator=(const CGuide& oSrc)
		{
			m_eType			= oSrc.m_eType;

			m_param_type1	= oSrc.m_param_type1;
			m_param_type2	= oSrc.m_param_type2;
			m_param_type3	= oSrc.m_param_type3;

			m_param_value1	= oSrc.m_param_value1;
			m_param_value2	= oSrc.m_param_value2;
			m_param_value3	= oSrc.m_param_value3;

			m_lShapeWidth	= oSrc.m_lShapeWidth;
			m_lShapeHeight	= oSrc.m_lShapeHeight;

			return *this;
		}

		void SetToFormula(NSGuidesVML::CFormula& oFormula)
		{
			oFormula.m_eFormulaType = m_eType;

			SetParam(m_param_type1, m_param_value1, oFormula.m_eType1, oFormula.m_lParam1);
			SetParam(m_param_type2, m_param_value2, oFormula.m_eType2, oFormula.m_lParam2);
			SetParam(m_param_type3, m_param_value3, oFormula.m_eType3, oFormula.m_lParam3);
		}

		void Read(IStream* pStream)
		{
			WORD ftType = StreamUtils::ReadWORD(pStream);

			m_eType = FormulaType(ftType & 0x1FFF);

			m_param_type1 = (BYTE)(ftType & 0x04);
			m_param_type2 = (BYTE)(ftType & 0x02);
			m_param_type3 = (BYTE)(ftType & 0x01);

			m_param_value1 = StreamUtils::ReadWORD(pStream);
			m_param_value2 = StreamUtils::ReadWORD(pStream);
			m_param_value3 = StreamUtils::ReadWORD(pStream);
		}

		void Read(NSOfficeDrawing::CBinaryReader& oReader)
		{
			WORD ftType = oReader.ReadWORD();

			m_eType = FormulaType(ftType & 0x1FFF);

			m_param_type1 = (BYTE)(ftType & 0x04);
			m_param_type2 = (BYTE)(ftType & 0x02);
			m_param_type3 = (BYTE)(ftType & 0x01);

			m_param_value1 = oReader.ReadWORD();
			m_param_value2 = oReader.ReadWORD();
			m_param_value3 = oReader.ReadWORD();
		}

	private:
		void SetParam(BYTE type, WORD param, ParamType& param_type, LONG& param_value)
		{
			if (0 == type)
			{
				param_type	= ptValue;
				param_value = (LONG)param;
			}
			
			if (0x0140 == param)
			{
				param_type	= ptValue;
				param_value	= ShapeSizeVML / 2;
				return;
			}
			if (0x0141 == param)
			{
				param_type	= ptValue;
				param_value	= ShapeSizeVML / 2;
				return;
			}
			if (0x0142 == param)
			{
				param_type	= ptValue;
				param_value	= ShapeSizeVML;
				return;
			}
			if (0x0143 == param)
			{
				param_type	= ptValue;
				param_value	= ShapeSizeVML;
				return;
			}

			if ((0x0147 <= param) && (param <= 0x014E))
			{
				param_type	= ptAdjust;
				param_value	= (LONG)(param - 0x0147);
				return;
			}
			
			if ((0x0400 <= param) && (param <= 0x047F))
			{
				param_type	= ptFormula;
				param_value	= (LONG)(param - 0x0400);
				return;
			}

			param_type	= ptValue;
			param_value	= ShapeSizeVML;
		}
	};

	class CCustomVML
	{
	private:
		RulesType m_ePath;

		CAtlArray<POINT>	m_arVertices;
		CAtlArray<CSegment> m_arSegments;
		CAtlArray<CGuide>	m_arGuides;
		CSimpleArray<LONG>*	m_pAdjustValues;

		BOOL m_bIsVerticesPresent;
		BOOL m_bIsPathPresent;

		CBrush_ m_oBrush;
		CPen_	m_oPen;

	public:
		CCustomVML() : 
			m_arVertices(), m_arSegments(), m_arGuides(), m_pAdjustValues(NULL)
		{
			m_ePath = rtCurveTo/*rtLineTo*/;
			
			m_bIsVerticesPresent	= FALSE;
			m_bIsPathPresent		= FALSE;
		}
		
		CCustomVML(const CCustomVML& oSrc)
		{
			*this = oSrc;
		}

		CCustomVML& operator=(const CCustomVML& oSrc)
		{
			m_ePath		= oSrc.m_ePath;

			m_arVertices.RemoveAll();
			m_arVertices.Copy(oSrc.m_arVertices);

			m_arSegments.RemoveAll();
			m_arSegments.Copy(oSrc.m_arSegments);

			m_arGuides.RemoveAll();
			m_arGuides.Copy(oSrc.m_arGuides);

			m_pAdjustValues = oSrc.m_pAdjustValues;
			
			m_bIsPathPresent		= oSrc.m_bIsPathPresent;
			m_bIsVerticesPresent	= oSrc.m_bIsVerticesPresent;

			m_oBrush	= oSrc.m_oBrush;
			m_oPen		= oSrc.m_oPen;

			return *this;
		}

		~CCustomVML()
		{
		}

	public:
		BOOL IsCustom()
		{
			return (m_bIsVerticesPresent && m_bIsPathPresent);
		}

	public:
		void SetPath(RulesType ePath)
		{
			m_ePath = ePath;
			m_bIsPathPresent = TRUE;
		}
		void LoadVertices(CProperty* pProperty)
		{
			NSOfficeDrawing::CBinaryReader oReader(pProperty->m_pOptions, pProperty->m_lValue);

			m_arVertices.RemoveAll();
			
			WORD lCount = (WORD)(pProperty->m_lValue / 8);
			if (pProperty->m_bIsTruncated)
			{
				lCount = (WORD)(pProperty->m_lValue / 4);
			}

			if (lCount > 0)
			{
				m_bIsVerticesPresent = TRUE;
			}

			for (WORD lIndex = 0; lIndex < lCount; ++lIndex)
			{
				POINT oPoint;
				if (pProperty->m_bIsTruncated)
				{
					oPoint.x = (LONG)oReader.ReadWORD();
					oPoint.y = (LONG)oReader.ReadWORD();
				}
				else
				{
					oPoint.x = oReader.ReadLONG();
					oPoint.y = oReader.ReadLONG();
				}

				LONG lMinF = (LONG)0x80000000;
				LONG lMaxF = (LONG)0x8000007F;
				if (lMinF <= oPoint.x)
				{
					int nGuideIndex = (DWORD)oPoint.x - 0x80000000;	

					bool b = false;
				}
				if (lMinF <= oPoint.y)
				{
					int nGuideIndex = (DWORD)oPoint.y - 0x80000000;					

					bool b = false;
				}

				m_arVertices.Add(oPoint);
			}
		}
		void LoadSegments(CProperty* pProperty)
		{
			NSOfficeDrawing::CBinaryReader oReader(pProperty->m_pOptions, pProperty->m_lValue);
			m_arSegments.RemoveAll();

			WORD lCount = (WORD)(pProperty->m_lValue / 2);

			if (lCount > 0)
			{
				m_bIsPathPresent = TRUE;
			}

			for (WORD lIndex = 0; lIndex < lCount; ++lIndex)
			{
				CSegment oInfo;
				oInfo.Read(oReader);

				if (0 == oInfo.m_nCount)
				{
					if ((rtEnd		!= oInfo.m_eRuler) &&
						(rtNoFill	!= oInfo.m_eRuler) &&
						(rtNoStroke != oInfo.m_eRuler) &&
						(rtClose	!= oInfo.m_eRuler))
					{
						continue;
					}
				}

				//if (rtClose == oInfo.m_eRuler)
				//{
				//	// �������� �����					
				//	CSegment oInfo2(rtLineTo, 1);
				//	m_arSegments.Add(oInfo2);
				//}

				m_arSegments.Add(oInfo);
			}
		}
		void LoadGuides(CProperty* pProperty)
		{
			NSOfficeDrawing::CBinaryReader oReader(pProperty->m_pOptions, pProperty->m_lValue);
			WORD lCount = (WORD)(pProperty->m_lValue / 4);

			for (WORD lIndex = 0; lIndex < lCount; ++lIndex)
			{
				CGuide oInfo;
				oInfo.Read(oReader);
				m_arGuides.Add(oInfo);
			}

		}
		void LoadAdjusts(LONG lIndex, LONG lValue)
		{
			if (NULL == m_pAdjustValues)
				return;
			
			LONG lCount = (LONG)m_pAdjustValues->GetSize();
			
			while (lCount <= lIndex)
			{
				m_pAdjustValues->Add(0);
				lCount = (LONG)m_pAdjustValues->GetSize();
			}

			(*m_pAdjustValues)[lIndex] = lValue;
		}

		void SetAdjusts(CSimpleArray<LONG>* pList)
		{
			m_pAdjustValues = pList;
		}

		void ToCustomShape(CBaseShape* pShape, NSGuidesVML::CFormulasManager& oManager)
		{
			if ((NULL == pShape) || (!IsCustom()))
				return;

			oManager.RemoveAll();
			// ������� �������� �������
			for (size_t nIndex = 0; nIndex < m_arGuides.GetCount(); ++nIndex)
			{
				NSGuidesVML::CFormula oF;
				m_arGuides[nIndex].SetToFormula(oF);
				oManager.AddFormula(oF);
			}

			oManager.Clear(m_pAdjustValues);

			CString strPath = _T("");

			bool bBreak = false;

			if (0 == m_arSegments.GetCount())
			{
				strPath = GetRulerVML(m_ePath);
				for (size_t nIndex = 0; nIndex < m_arVertices.GetCount(); ++nIndex)
				{
					CString str = _T("");
					str.Format(_T("%d,%d,"), m_arVertices[nIndex].x, m_arVertices[nIndex].y);
					strPath += str;
				}
				strPath.Delete(strPath.GetLength() - 1);
			}
			else
			{
				size_t nStart	= 0;
				size_t nEnd		= 0;
				for (size_t nS = 0; nS < m_arSegments.GetCount(); ++nS)
				{
					if (bBreak)
					{
						if ((rtEnd		!= m_arSegments[nS].m_eRuler) &&
							(rtNoFill	!= m_arSegments[nS].m_eRuler) &&
							(rtNoStroke != m_arSegments[nS].m_eRuler) &&
							(rtClose	!= m_arSegments[nS].m_eRuler))
						{
							strPath += _T("e");
							break;
						}
					}

					if ((rtFillColor == m_arSegments[nS].m_eRuler) || (rtLineColor == m_arSegments[nS].m_eRuler))
					{
						if (nStart <  m_arVertices.GetCount())
						{
							if (rtFillColor == m_arSegments[nS].m_eRuler)
							{
								m_oBrush.m_oColor1 = (DWORD)m_arVertices[nStart].x;
								m_oBrush.m_oColor2 = (DWORD)m_arVertices[nStart].y;
							}
							else
							{
								m_oPen.m_oColor	   = (DWORD)m_arVertices[nStart].x;	
							}
						}
						nEnd = nStart + m_arSegments[nS].m_nCount;
						if (nEnd > m_arVertices.GetCount())
							nEnd = m_arVertices.GetCount();
						nStart = nEnd;

						if (nEnd == m_arVertices.GetCount())
						{
							bBreak = true;
						}
						continue;
					}

					strPath += GetRulerVML(m_arSegments[nS].m_eRuler);
					
					nEnd = nStart + m_arSegments[nS].m_nCount;
					if (nEnd > m_arVertices.GetCount())
						nEnd = m_arVertices.GetCount();

					for (size_t nV = nStart; nV < nEnd; ++nV)
					{
						CString str = _T("");
						str.Format(_T("%d,%d,"), m_arVertices[nV].x, m_arVertices[nV].y);
						strPath += str;
					}

					if (nEnd != nStart)
					{
						strPath.Delete(strPath.GetLength() - 1);
					}
					nStart = nEnd;

					if (nEnd == m_arVertices.GetCount())
					{
						bBreak = true;
					}
				}
			}

			oManager.CalculateResults();

			pShape->LoadPathList(strPath);

			/*CString str = _T("<w:pict xmlns:w=\"http://schemas.openxmlformats.org/wordprocessingml/2006/main\" xmlns:v=\"urn:schemas-microsoft-com:vml\" xmlns:o=\"urn:schemas-microsoft-com:office:office\">\
              <v:shape id=\"Cloud 1\" o:spid=\"_x0000_s1026\" style=\"position:absolute;margin-left:-17.3pt;margin-top:158.4pt;width:466.95pt;height:335.65pt;z-index:251659264;visibility:visible;mso-wrap-style:square;mso-wrap-distance-left:9pt;mso-wrap-distance-top:0;mso-wrap-distance-right:9pt;mso-wrap-distance-bottom:0;mso-position-horizontal:absolute;mso-position-horizontal-relative:text;mso-position-vertical:absolute;mso-position-vertical-relative:text;v-text-anchor:middle\" coordsize=\"43200,43200\" path=\"m3900,14370c3629,11657,4261,8921,5623,6907,7775,3726,11264,3017,14005,5202,15678,909,19914,22,22456,3432,23097,1683,24328,474,25749,200v1564,-302,3126,570,4084,2281c31215,267,33501,-460,35463,690v1495,876,2567,2710,2855,4886c40046,6218,41422,7998,41982,10318v407,1684,349,3513,-164,5142c43079,17694,43520,20590,43016,23322v-670,3632,-2888,6352,-5612,6882c37391,32471,36658,34621,35395,36101v-1919,2249,-4691,2538,-6840,714c27860,39948,25999,42343,23667,43106v-2748,899,-5616,-633,-7187,-3840c12772,42310,7956,40599,5804,35472,3690,35809,1705,34024,1110,31250,679,29243,1060,27077,2113,25551,619,24354,-213,22057,-5,19704,239,16949,1845,14791,3863,14507v12,-46,25,-91,37,-137xem4693,26177nfc3809,26271,2925,25993,2160,25380t4768,9519nfc6573,35092,6200,35220,5820,35280t10658,3810nfc16211,38544,15987,37961,15810,37350m28827,34751nfc28788,35398,28698,36038,28560,36660m34129,22954nfc36133,24282,37398,27058,37380,30090m41798,15354nfc41473,16386,40978,17302,40350,18030m38324,5426nfc38379,5843,38405,6266,38400,6690m29078,3952nfc29267,3369,29516,2826,29820,2340m22141,4720nfc22218,4238,22339,3771,22500,3330m14000,5192nfc14472,5568,14908,6021,15300,6540m4127,15789nfc4024,15325,3948,14851,3900,14370e\" fillcolor=\"#4f81bd\" strokecolor=\"#385d8a\" strokeweight=\"2pt\">\
                <v:path arrowok=\"t\" o:connecttype=\"custom\" o:connectlocs=\"644218,2582990;296508,2504347;951021,3443625;798923,3481220;2261969,3857168;2170271,3685475;3957142,3429021;3920490,3617390;4684958,2264964;5131230,2969101;5737698,1515041;5538928,1779093;5260814,535405;5271247,660129;3991597,389960;4093453,230897;3039341,465741;3088621,328585;1921809,512316;2100263,645328;566522,1557964;535361,1417946\" o:connectangles=\"0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0\"/>\
              </v:shape>\
            </w:pict>");*/

			//pShape->LoadFromXML(str);
		}
	};
}