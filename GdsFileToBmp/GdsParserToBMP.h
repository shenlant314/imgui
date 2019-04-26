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

class GdsParserToBMP: public GDSParser::gdsFileParser
{
public:
	GdsParserToBMP(CProgressCtrl* pCtrlProgress);
	~GdsParserToBMP(void);

	// 将Boundary数据矢量化为像素点阵
	bool TransPointToPixel();

	void PrintExtentPoint();

	void SetBMPDPI(int nDpi);

protected:
	// 保存Boundary数据
	std::vector<GePointVector> m_vecPointVec;

	// XY值的最大和最小
	int m_nMinX;
	int m_nMinY;
	int m_nMaxX;
	int m_nMaxY;
	bool m_bFirst;

	int m_nDpi;

	bool m_bIsBoundary;

	CString m_strBoundaryType;

	CProgressCtrl* m_pCtrlProgress;

	// 生成BMP
	bool GenerateBMP(BYTE * pData,int nWidth, int nHeight, const CString& strFilename);

protected:
	virtual void onParsedGDSVersion(unsigned short version);
	virtual void onParsedModTime(short year, short month, short day,short hour, short minute, short sec);
	virtual void onParsedAccessTime(short year, short month, short day,
		short hour, short minute, short sec);
	virtual void onParsedLibName(const char *libName);
	virtual void onParsedUnits(double userUnits, double databaseUnits);
	virtual void onParsedStrName(const char *strName);
	virtual void onParsedBoundaryStart();
	virtual void onParsedPathStart();
	virtual void onParsedBoxStart();
	virtual void onParsedEndElement();
	virtual void onParsedEndStructure();
	virtual void onParsedEndLib();
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
