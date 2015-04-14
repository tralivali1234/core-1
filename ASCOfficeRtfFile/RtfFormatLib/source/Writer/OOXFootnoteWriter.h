#pragma once

#include "OOXWriter.h"

class OOXFootnoteWriter
{
public:
	OOXRelsWriterPtr m_oRelsWriter;
	OOXFootnoteWriter( OOXWriter& oWriter,RtfDocument& oDocument ):m_oWriter(oWriter),m_oDocument(oDocument)
	{
		m_oRelsWriter = OOXRelsWriterPtr( new OOXRelsWriter( _T("footnotes.xml"), oDocument ) );
		oWriter.m_oCustomRelsWriter.push_back( m_oRelsWriter );
	}
	void AddFootnoteBegin( CString sType, int nID, CString sText )
	{
		CString sFootnote;
		sFootnote.Append( _T("<w:footnote") );
		if( false == sType.IsEmpty() )
			sFootnote.AppendFormat( _T(" w:type=\"%ls\""), sType );
		if( PROP_DEF != nID )
			sFootnote.AppendFormat( _T(" w:id=\"%d\""), nID );
		sFootnote.Append( _T(">") );
		sFootnote.Append( sText );
		sFootnote.Append(_T("</w:footnote>"));

		m_sFootnotes.Insert( 0 , sFootnote );
	}
	void AddFootnote( CString sType, int nID, CString sText )
	{
		m_sFootnotes.Append( _T("<w:footnote") );
		if( false == sType.IsEmpty() )
			m_sFootnotes.AppendFormat( _T(" w:type=\"%ls\""), sType );
		if( PROP_DEF != nID )
			m_sFootnotes.AppendFormat( _T(" w:id=\"%d\""), nID );
		m_sFootnotes.Append( _T(">") );
		m_sFootnotes.Append( sText );
		m_sFootnotes.Append(_T("</w:footnote>"));
	}
	bool Save( CString sFolder )
	{
		if(  m_sFootnotes.IsEmpty() ) return false;

		CFile file;
		if (file.CreateFileW(sFolder + FILE_SEPARATOR_STR + _T("footnotes.xml"))) return false;
		
		m_oWriter.m_oDocRels.AddRelationship( _T("http://schemas.openxmlformats.org/officeDocument/2006/relationships/footnotes"), _T("footnotes.xml") );
		m_oWriter.m_oContentTypes.AddContent( _T("application/vnd.openxmlformats-officedocument.wordprocessingml.footnotes+xml"), _T("/word/footnotes.xml") );

		 CString sXml = CreateXml();
		 CStringA sXmlUTF = Convert::UnicodeToUtf8( sXml );
		
		 file.WriteFile(sXmlUTF.GetBuffer(), sXmlUTF.GetLength());
		 file.CloseFile();
		 return true;
	}
private: 
	RtfDocument& m_oDocument;
	OOXWriter& m_oWriter;
	CString m_sFootnotes;
	CString CreateXml()
	{
		CString sResult;
		sResult.Append( _T("<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>") );
		sResult.AppendChar('\n');
		sResult.Append( _T("<w:footnotes xmlns:wpc=\"http://schemas.microsoft.com/office/word/2008/6/28/wordprocessingCanvas\" xmlns:mc=\"http://schemas.openxmlformats.org/markup-compatibility/2006\" xmlns:o=\"urn:schemas-microsoft-com:office:office\" xmlns:r=\"http://schemas.openxmlformats.org/officeDocument/2006/relationships\" xmlns:m=\"http://schemas.openxmlformats.org/officeDocument/2006/math\" xmlns:v=\"urn:schemas-microsoft-com:vml\" xmlns:wp14=\"http://schemas.microsoft.com/office/word/2008/9/16/wordprocessingDrawing\" xmlns:wp=\"http://schemas.openxmlformats.org/drawingml/2006/wordprocessingDrawing\" xmlns:w10=\"urn:schemas-microsoft-com:office:word\" xmlns:w=\"http://schemas.openxmlformats.org/wordprocessingml/2006/main\" xmlns:w14=\"http://schemas.microsoft.com/office/word/2009/2/wordml\" xmlns:wpg=\"http://schemas.microsoft.com/office/word/2008/6/28/wordprocessingGroup\" xmlns:wpi=\"http://schemas.microsoft.com/office/word/2008/6/28/wordprocessingInk\" xmlns:wne=\"http://schemas.microsoft.com/office/word/2006/wordml\" xmlns:wps=\"http://schemas.microsoft.com/office/word/2008/6/28/wordprocessingShape\" >") );
		sResult.Append( m_sFootnotes );
		sResult.Append( _T("</w:footnotes>") );
		return sResult;
	}

};
class OOXEndnoteWriter
{
public: 
	OOXRelsWriterPtr m_oRelsWriter;
	OOXEndnoteWriter( OOXWriter& oWriter,RtfDocument& oDocument ):m_oWriter(oWriter),m_oDocument(oDocument)
	{
		m_oRelsWriter = OOXRelsWriterPtr( new OOXRelsWriter( _T("endnotes.xml"), oDocument ) );
		oWriter.m_oCustomRelsWriter.push_back( m_oRelsWriter );
	}
	void AddEndnoteBegin( CString sType, int nID, CString sText )
	{
		CString sEndnote;
		sEndnote.Append( _T("<w:endnote") );
		if( false == sType.IsEmpty() )
			sEndnote.AppendFormat( _T(" w:type=\"%ls\""), sType );
		if( -2 != nID )
			sEndnote.AppendFormat( _T(" w:id=\"%d\""), nID );
		sEndnote.Append( _T(">") );
		sEndnote.Append( sText );
		sEndnote.Append(_T("</w:endnote>") );

		m_sEndnotes.Insert( 0 , sEndnote );
	}
	void AddEndnote( CString sType, int nID, CString sText )
	{
		m_sEndnotes.Append( _T("<w:endnote") );
		if( false == sType.IsEmpty() )
			m_sEndnotes.AppendFormat( _T(" w:type=\"%ls\""), sType );
		if( -2 != nID )
			m_sEndnotes.AppendFormat( _T(" w:id=\"%d\""), nID );
		m_sEndnotes.Append( _T(">") );
		m_sEndnotes.Append( sText );
		m_sEndnotes.Append(_T("</w:endnote>") );
	}
	bool Save( CString sFolder )
	{
		if( m_sEndnotes.IsEmpty() ) return false;

		CFile file;
		if (file.CreateFileW(sFolder + FILE_SEPARATOR_STR + _T("endnotes.xml"))) return false;

		m_oWriter.m_oDocRels.AddRelationship( _T("http://schemas.openxmlformats.org/officeDocument/2006/relationships/endnotes"), _T("endnotes.xml") );
		m_oWriter.m_oContentTypes.AddContent( _T("application/vnd.openxmlformats-officedocument.wordprocessingml.endnotes+xml"), _T("/word/endnotes.xml") );

		CStringA sXml = CreateXml();

		file.WriteFile(sXml.GetBuffer(), sXml.GetLength());
		file.CloseFile();
		return true;
	}
private: 
	RtfDocument& m_oDocument;
	OOXWriter& m_oWriter;
	CString m_sEndnotes;
	CStringA CreateXml()
	{
		CString sResult;
		sResult.Append( _T("<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>") );
		sResult.AppendChar('\n');
		sResult.Append( _T("<w:endnotes xmlns:wpc=\"http://schemas.microsoft.com/office/word/2008/6/28/wordprocessingCanvas\" xmlns:mc=\"http://schemas.openxmlformats.org/markup-compatibility/2006\" xmlns:o=\"urn:schemas-microsoft-com:office:office\" xmlns:r=\"http://schemas.openxmlformats.org/officeDocument/2006/relationships\" xmlns:m=\"http://schemas.openxmlformats.org/officeDocument/2006/math\" xmlns:v=\"urn:schemas-microsoft-com:vml\" xmlns:wp14=\"http://schemas.microsoft.com/office/word/2008/9/16/wordprocessingDrawing\" xmlns:wp=\"http://schemas.openxmlformats.org/drawingml/2006/wordprocessingDrawing\" xmlns:w10=\"urn:schemas-microsoft-com:office:word\" xmlns:w=\"http://schemas.openxmlformats.org/wordprocessingml/2006/main\" xmlns:w14=\"http://schemas.microsoft.com/office/word/2009/2/wordml\" xmlns:wpg=\"http://schemas.microsoft.com/office/word/2008/6/28/wordprocessingGroup\" xmlns:wpi=\"http://schemas.microsoft.com/office/word/2008/6/28/wordprocessingInk\" xmlns:wne=\"http://schemas.microsoft.com/office/word/2006/wordml\" xmlns:wps=\"http://schemas.microsoft.com/office/word/2008/6/28/wordprocessingShape\" >") );
		sResult.Append( m_sEndnotes );
		sResult.Append( _T("</w:endnotes>") );
		return  Convert::UnicodeToUtf8( sResult);
	}
};