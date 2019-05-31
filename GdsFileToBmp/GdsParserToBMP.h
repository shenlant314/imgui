#pragma once

#include "gdsFileParser.h"
typedef struct _GePointStru
{
	int m_nX;
	int m_nY;
	_GePointStru()
	{
		m_nX = 0;
		m_nY = 0;
	}
} GePointStru;
typedef std::vector<GePointStru> GePointVector;

typedef struct _GDS_Element
{
	// Element���ͣ�
	// BOUNDARY �߽��ߣ�������һ��������Σ�
	// PATH ·��������һ�����ߣ�
	// SREF �ṹ���ã�structure reference��������һ���ӵ�Ԫ��
	// AREF �������ã�array reference��������һ��������е��ӵ�Ԫ��
	// TEXT �ı���text��������Ϊ��¼��Ϣ��
	// NODE �ڵ㣨node��������һ������·����
	// BOX ���ӣ�box��������һ������ͼ�Ρ�
	CString m_strElementType; 
	// ͼ��
	int m_nLayer;
	// ��������
	int m_nDataType;

	// ·�����ͣ���elementʱpath������Ч����
	int m_nPathType;
	int m_nWidth;

	// �ṹ���õĽṹ������elementʱSREF������Ч����
	CString m_strSrefName;

	// �������õĽṹ������elementʱAREF������Ч����
	CString m_strArefName;
	// ���е��к��У���elementʱAREF������Ч����
	int m_nColumns;
	int m_nRows;
	std::vector<GePointVector> m_vecPointAry; // ����չ���󱣴��λ��

	//�����ַ���,��ΪTEXTʱ����
	CString m_strTextString;
	int m_nTextType;

	// �����⼸������֪���Ǹ����
	double m_dMag;
	double m_dAngle;

	// ����
	GePointVector m_gePtVec;

	_GDS_Element()
	{
		m_nLayer = 0;
		m_nDataType = 0;

		m_nPathType = 0;
		m_nWidth = 0;
		m_nTextType = 0;

		m_dMag = 0.0;
		m_dAngle = 0.0;
	}

} GDS_Element;
typedef std::vector<GDS_Element> GDS_ElementVector;

typedef struct _GDS_Structure
{
	CString m_strName;					// �ṹ��
	GDS_ElementVector m_vecElem;		// ������Ԫ���б�
	
} GDS_Structure;
typedef std::map<CString,GDS_Structure> GDS_StructureMap; // <�ṹ��,�ṹ����>

class GdsParserToBMP: public GDSParser::gdsFileParser
{
public:
	GdsParserToBMP(CProgressCtrl* pCtrlProgress);
	~GdsParserToBMP(void);

	// ����BMP
	bool GenerateBMP(int nWidth, int nHeight, const CString& strFilename);

	void PrintExtentPoint();

	void SetBMPDPI(int nDpi);

	int parse(const CString& strfilePath);

protected:
	// ����Boundary����
	std::vector<GePointVector> m_vecPointVec;


	// XYֵ��������С
	int m_nMinX;
	int m_nMinY;
	int m_nMaxX;
	int m_nMaxY;
	bool m_bFirst;

	int m_nDpi;

	bool m_bIsBoundary;

	CString m_strBoundaryType;

	CProgressCtrl* m_pCtrlProgress;

	// ��Boundary����ʸ����Ϊ���ص���
	bool TransPointToPixel(BYTE * pData,int nWidth, int nHeight);

	// ����ʱ�����txt�ı�
	CStdioFile m_outTxtFile;
//////////////////////////////////////////////////////////////////////////
protected:
	// ����Ľ����ṹ����
	GDS_StructureMap m_mapStuParam;
	GDS_Structure m_stuCurrentRead;
	GDS_Element   m_elemCurrentRead;
protected:
	virtual void onParsedGDSVersion(unsigned short version);
	virtual void onParsedModTime(short year, short month, short day,short hour, short minute, short sec);
	virtual void onParsedAccessTime(short year, short month, short day,
		short hour, short minute, short sec);
	virtual void onParsedUnits(double userUnits, double databaseUnits);

	virtual void onParsedLibName(const char *libName);
	virtual void onParsedEndLib();

	virtual void onParsedStrName(const char *strName);
	virtual void onParsedEndStructure();

	virtual void onParsedBoundaryStart();
	virtual void onParsedPathStart();
	virtual void onParsedBoxStart();
	virtual void onParsedEndElement();

	virtual void onParsedColumnsRows(unsigned short columns,
		unsigned short rows);
	virtual void onParsedPathType(unsigned short pathType);
	virtual void onParsedStrans(short strans);
	virtual void onParsedPresentation(short font, short valign,
		short halign);
	virtual void onParsedNodeStart();
	virtual void onParsedTextStart();
	virtual void onParsedSrefStart();
	virtual void onParsedArefStart();
	virtual void onParsedSname(const char *sname);
	virtual void onParsedString(const char *str);
	virtual void onParsedPropValue(const char *propValue);
	virtual void onParsedXY(int count, std::vector<int>& x, std::vector<int>& y);
	virtual void onParsedLayer(unsigned short layer);
	virtual void onParsedWidth(int width);
	virtual void onParsedDataType(unsigned short dataType);
	virtual void onParsedTextType(unsigned short textType);
	virtual void onParsedAngle(double angle);
	virtual void onParsedMag(double mag);
	virtual void onParsedBeginExtension(unsigned short bext);
	virtual void onParsedEndExtension(unsigned short eext);
	virtual void onParsedPropertyNumber(unsigned short propNum);
	virtual void onParsedNodeType(unsigned short nodeType);
	virtual void onParsedBoxType(unsigned short boxType);
};
