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
	// Element类型，
	// BOUNDARY 边界线，定义了一个填充多边形；
	// PATH 路径定义了一根电线；
	// SREF 结构引用（structure reference）调用了一个子单元；
	// AREF 数组引用（array reference）调用了一个数组陈列的子单元；
	// TEXT 文本（text）用来作为记录信息；
	// NODE 节点（node）定义了一个电气路径；
	// BOX 盒子（box）定义了一个矩形图形。
	CString m_strElementType; 
	// 图层
	CString m_strLayer;
	// 数据类型
	int m_nDataType;

	// 路径类型，仅element时path才是有效数据
	int m_nPathType;

	// 结构引用的结构名，仅element时SREF才是有效数据
	CString m_strSrefName;

	// 数组引用的结构名，仅element时AREF才是有效数据
	CString m_strArefName;
	// 陈列的行和列，仅element时AREF才是有效数据
	int m_nColumns;
	int m_nRows;

	// 下面这几个还不知道是干嘛的
	double m_dMag;
	double m_dAngle;

	// 坐标
	GePointVector m_gePtVec;

} GDS_Element;
typedef std::vector<GDS_Element> GDS_ElementVector;

typedef struct _GDS_Structure
{
	

} GDS_Structure;
typedef std::map<CString,GDS_Structure> GDS_StructureMap;

class GdsParserToBMP: public GDSParser::gdsFileParser
{
public:
	GdsParserToBMP(CProgressCtrl* pCtrlProgress);
	~GdsParserToBMP(void);

	// 将Boundary数据矢量化为像素点阵
	bool TransPointToPixel();

	void PrintExtentPoint();

	void SetBMPDPI(int nDpi);

	int parse(const CString& strfilePath);

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

	// 解析时保存的txt文本
	CStdioFile m_outTxtFile;

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
