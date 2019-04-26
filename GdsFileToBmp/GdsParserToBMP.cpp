#include "stdafx.h"
#include "GdsParserToBMP.h"
#include<windef.h>
#include <wingdi.h>
#include "stdio.h"
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <math.h>
using namespace std;

#define SET_2W setfill('0') << setw(2)

GdsParserToBMP::GdsParserToBMP(CProgressCtrl* pCtrlProgress)
{
	m_nMinX = 0;
	m_nMinY = 0;
	m_nMaxX = 0;
	m_nMaxY = 0;
	m_bFirst = true;
	m_pCtrlProgress = pCtrlProgress;
}

GdsParserToBMP::~GdsParserToBMP(void)
{
}
/*
bool GdsParserToBMP::TransPointToPixel()
{
	const int height = 2540;
	const int width = 2540;
	const int nSize = height * width * 3;

	CString strPromt = _T("");
	CString strTmp;
	// 缩放比例
	int m_nXsacle = (m_nMaxX-m_nMinX) /(width - 1);
	int m_nYsacle = (m_nMaxY-m_nMinY) /(height - 1);
	int nScale = m_nXsacle;
	if (m_nYsacle > nScale)
	{
		nScale = m_nYsacle;
	}
	strTmp.Format(_T("Min(%d,%d),Max(%d,%d), Scale(%d,%d)\n"), m_nMinX, m_nMinY, m_nMaxX, m_nMaxY, m_nXsacle, m_nYsacle);
	strPromt += strTmp;
	std::vector<GePointVector>::iterator itVecAry = m_vecPointVec.begin();
	int nIndex = 0;
	int nCurPicNo = 0;
	for ( ; itVecAry != m_vecPointVec.end(); ++itVecAry)
	{
		GePointVector::iterator itVec = itVecAry->begin();
		GePointStru lastPt;
		bool bFirstPos = true; 
		for ( ; itVec != itVecAry->end(); ++itVec)
		{
			GePointStru tmpPt;
			tmpPt.m_nX = (itVec->m_nX - m_nMinX) / nScale;
			tmpPt.m_nY = (itVec->m_nY - m_nMinY) / nScale;
			nIndex = (tmpPt.m_nY ) * width * 3 + (tmpPt.m_nX )* 3;
			if (bFirstPos)
			{
				lastPt.m_nX = tmpPt.m_nX;
				lastPt.m_nY = tmpPt.m_nY;
				bFirstPos = false;
			}
			else
			{
				if (nIndex < nSize)
				{
					double dDist = sqrt((double)(tmpPt.m_nX- lastPt.m_nX)*(tmpPt.m_nX- lastPt.m_nX) +(double)(tmpPt.m_nY - lastPt.m_nY)*(tmpPt.m_nY - lastPt.m_nY));
					int nDist = (int)dDist;
					for (int i = 0; i < nDist; ++i)
					{
						// 离散点
						int tmpSegX = (i*(tmpPt.m_nX - lastPt.m_nX))/nDist + lastPt.m_nX;// 用i作为离散距离，可能会重复
						int tmpSegY = (i*(tmpPt.m_nY - lastPt.m_nY))/nDist + lastPt.m_nY;// 用i作为离散距离，可能会重复
						int tmpIndex = tmpSegY * width * 3 + tmpSegX* 3;

						bits[tmpIndex + 0] = 0; // Blue
						bits[tmpIndex + 1] = 0;   // Green
						bits[tmpIndex + 2] = 255;   // Red
					}
					bits[nIndex + 0] = 0; // Blue
					bits[nIndex + 1] = 0;   // Green
					bits[nIndex + 2] = 255;   // Red

					strTmp.Format(_T("(%d,%d)"), tmpPt.m_nX, tmpPt.m_nY);
					strPromt += strTmp;
				}
				else
				{
					strTmp.Format(_T("***(%d,%d)**"), tmpPt.m_nX, tmpPt.m_nY);
					strPromt += strTmp;
				}

				lastPt.m_nX = tmpPt.m_nX;
				lastPt.m_nY = tmpPt.m_nY;
			}
		}
		strPromt += _T("\n-----------\n");
	}

	
	return true;
}*/

bool GdsParserToBMP::TransPointToPixel()
{
	const int height = 2540;
	const int width = 2540;
	const int nSize = height * width * 3;

	CString strPromt = _T("");
	CString strTmp;

	strTmp.Format(_T("Min(%d,%d),Max(%d,%d), Scale(%d,%d)\n"), m_nMinX, m_nMinY, m_nMaxX, m_nMaxY, m_nXsacle, m_nYsacle);
	strPromt += strTmp;
	std::vector<GePointVector>::iterator itVecAry = m_vecPointVec.begin();
	int nIndex = 0;
	int nCurPicNo = 0;
	for ( ; itVecAry != m_vecPointVec.end(); ++itVecAry)
	{
		GePointVector::iterator itVec = itVecAry->begin();
		GePointStru lastPt;
		bool bFirstPos = true; 
		for ( ; itVec != itVecAry->end(); ++itVec)
		{
			GePointStru tmpPt;
			tmpPt.m_nX = (itVec->m_nX - m_nMinX) / nScale;
			tmpPt.m_nY = (itVec->m_nY - m_nMinY) / nScale;
			nIndex = (tmpPt.m_nY ) * width * 3 + (tmpPt.m_nX )* 3;
			if (bFirstPos)
			{
				lastPt.m_nX = tmpPt.m_nX;
				lastPt.m_nY = tmpPt.m_nY;
				bFirstPos = false;
			}
			else
			{
				if (nIndex < nSize)
				{
					double dDist = sqrt((double)(tmpPt.m_nX- lastPt.m_nX)*(tmpPt.m_nX- lastPt.m_nX) +(double)(tmpPt.m_nY - lastPt.m_nY)*(tmpPt.m_nY - lastPt.m_nY));
					int nDist = (int)dDist;
					for (int i = 0; i < nDist; ++i)
					{
						// 离散点
						int tmpSegX = (i*(tmpPt.m_nX - lastPt.m_nX))/nDist + lastPt.m_nX;// 用i作为离散距离，可能会重复
						int tmpSegY = (i*(tmpPt.m_nY - lastPt.m_nY))/nDist + lastPt.m_nY;// 用i作为离散距离，可能会重复
						int tmpIndex = tmpSegY * width * 3 + tmpSegX* 3;

						bits[tmpIndex + 0] = 0; // Blue
						bits[tmpIndex + 1] = 0;   // Green
						bits[tmpIndex + 2] = 255;   // Red
					}
					bits[nIndex + 0] = 0; // Blue
					bits[nIndex + 1] = 0;   // Green
					bits[nIndex + 2] = 255;   // Red

					strTmp.Format(_T("(%d,%d)"), tmpPt.m_nX, tmpPt.m_nY);
					strPromt += strTmp;
				}
				else
				{
					strTmp.Format(_T("***(%d,%d)**"), tmpPt.m_nX, tmpPt.m_nY);
					strPromt += strTmp;
				}

				lastPt.m_nX = tmpPt.m_nX;
				lastPt.m_nY = tmpPt.m_nY;
			}
		}
		strPromt += _T("\n-----------\n");
	}


	return true;
}
bool GdsParserToBMP::GenerateBMP( BYTE * pData, int nWidth, int nHeight,  const CString& strFilename )
{
	// BMP尺寸
	const int nSize = nHeight * nWidth * 3;

	// BMP文件头
	BITMAPFILEHEADER fileHeader;

	fileHeader.bfType = 0x4D42;
	fileHeader.bfReserved1 = 0;
	fileHeader.bfReserved2 = 0;
	fileHeader.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + nSize;
	fileHeader.bfReserved1 = 0; // reserved
	fileHeader.bfReserved2 = 0; // reserved
	fileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	// Bitmap 信息头
	BITMAPINFOHEADER bitmapHeader;
	bitmapHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitmapHeader.biHeight = nHeight;
	bitmapHeader.biWidth = nWidth;
	bitmapHeader.biPlanes = 1;
	bitmapHeader.biBitCount = 24;
	bitmapHeader.biSizeImage = nSize;
	bitmapHeader.biCompression = 0; //BI_RGB
	bitmapHeader.biXPelsPerMeter = 0;
	bitmapHeader.biYPelsPerMeter = 0;
	bitmapHeader.biClrUsed = 0;
	bitmapHeader.biClrImportant = 0;  
	// 信息内存池
	BYTE *bits = (BYTE *)malloc(nSize);
	// 清空值
	memset(bits, 0xFF, nSize);

	// 写入文件
	FILE *output = fopen("D:\\output.bmp", "wb");
	if (output == NULL)
	{
		AfxMessageBox(_T("Cannot open file!\n"));
	}
	else
	{
		//		AfxMessageBox(strPromt);
		fwrite(&fileHeader, 1, sizeof(BITMAPFILEHEADER), output);
		fwrite(&bitmapHeader,1,  sizeof(BITMAPINFOHEADER), output);
		fwrite(bits, 1, nSize, output);
		fclose(output);
	}

}

void GdsParserToBMP::onParsedGDSVersion(unsigned short version) {
	cout << "GDSII Version: " << version << endl;
};
void GdsParserToBMP::onParsedModTime(short year, short month, short day,
							 short hour, short minute, short sec) {
								 cout << "Modified Time: " << endl;

								 if(year==0 && month==0) {
									 cout << "\tNot recorded." << endl;
								 } else {
									 cout << "\t" << year << "-" << SET_2W << month <<  "-" << SET_2W <<
										 day << " " << SET_2W << hour << ":" << SET_2W << minute <<
										 ":" << SET_2W << sec << endl;
								 }
};
void GdsParserToBMP::onParsedAccessTime(short year, short month, short day,
								short hour, short minute, short sec) {
									cout << "Accessed Time: " << endl;

									if(year==0 && month==0) {
										cout << "\tNot recorded." << endl;
									} else {
										cout << "\t" << year << "-" << SET_2W << month <<  "-" << SET_2W <<
											day << " " << SET_2W << hour << ":" << SET_2W << minute <<
											":" << SET_2W << sec << endl;
									}
};
void GdsParserToBMP::onParsedLibName(const char *libName) {
	cout << "LibName: " << libName << endl;
	m_strBoundaryType = _T("LibName");
};
void GdsParserToBMP::onParsedUnits(double userUnits, double dbUnits) {
	cout << "UserUnits: " << setprecision(9) << fixed << userUnits << endl;
	cout << "DBUnits: " << setprecision(9) << fixed << dbUnits << endl;
};
void GdsParserToBMP::onParsedStrName(const char *strName) {
	cout << "StrName: " << strName << endl;
	m_strBoundaryType = _T("StrName");
};
void GdsParserToBMP::onParsedBoundaryStart() {
	cout << "Boundry start" << endl;
	m_bIsBoundary = true;
	m_strBoundaryType = _T("Boundry");
};
void GdsParserToBMP::onParsedPathStart() {
	cout << "Path start" << endl;
	m_bIsBoundary = true;
	m_strBoundaryType = _T("Path");
};
void GdsParserToBMP::onParsedBoxStart() {
	cout << "Box start" << endl;
	m_bIsBoundary = true;
	m_strBoundaryType = _T("Box");
};
void GdsParserToBMP::onParsedEndElement() {
	cout << "Element end" << endl;
};
void GdsParserToBMP::onParsedEndStructure() {
	cout << "Structure end" << endl;
};
void GdsParserToBMP::onParsedEndLib() {
	cout << "Lib end" << endl;
};
void GdsParserToBMP::onParsedColumnsRows(unsigned short columns,
								 unsigned short rows) {
									 cout << "Columns: " << columns << " Rows: " << rows << endl;
};
void GdsParserToBMP::onParsedPathType(unsigned short pathType) {
	cout << "PathType: " << pathType << endl;
};
void GdsParserToBMP::onParsedStrans(short strans) {
	cout << "Strans: " << strans << endl;
};
void GdsParserToBMP::onParsedPresentation(short font, short valign,
								  short halign) {
									  cout << "Font: " << font << endl;
									  cout << "Valign: " << valign << endl;
									  cout << "Halign: " << halign << endl;
};
void GdsParserToBMP::onParsedNodeStart() {
	cout << "Node start" << endl;
	m_bIsBoundary = false;
	m_strBoundaryType = _T("Node");
};
void GdsParserToBMP::onParsedTextStart() {
	cout << "Text start" << endl;
	m_bIsBoundary = false;
	m_strBoundaryType = _T("Text");
};
void GdsParserToBMP::onParsedSrefStart() {
	cout << "Sref start" << endl;
	m_bIsBoundary = false;
	m_strBoundaryType = _T("Sref");
};
void GdsParserToBMP::onParsedArefStart() {
	cout << "Aref start" << endl;
	m_bIsBoundary = false;
	m_strBoundaryType = _T("Aref");
};
void GdsParserToBMP::onParsedSname(const char *sname) {
	cout << "Sname: " << sname << endl;
};
void GdsParserToBMP::onParsedString(const char *str) {
	cout << "String: " << str << endl;
};
void GdsParserToBMP::onParsedPropValue(const char *propValue) {
	cout << "Prop Value: " << propValue << endl;
};
void GdsParserToBMP::onParsedXY(int count, std::vector<int>& x, std::vector<int>& y) {
	cout << "XY: " << count << endl;

	GePointVector vecPoint;
	for(int i=0; i<count; ++i) 
	{
		cout << "(" << x[i] << "," << y[i] << ")";
		GePointStru tmpStu;
		tmpStu.m_nX = x[i];
		tmpStu.m_nY = y[i];
		vecPoint.push_back(tmpStu);
		if (m_bIsBoundary)
		{
			if (m_bFirst)
			{
				m_nMinX = m_nMaxX = x[i];
				m_nMinY = m_nMaxY = y[i];
				m_bFirst = false;
			}
			else 
			{
				if (x[i] < m_nMinX)
				{
					m_nMinX = x[i];
				}

				if (x[i] > m_nMaxX)
				{
					m_nMaxX = x[i];
				}
				if (y[i] < m_nMinY)
				{
					m_nMinY = y[i];
				}
				if (y[i] > m_nMaxY)
				{
					m_nMaxY = y[i];
				}
			}
		}
// 		if (tmpStu.m_nX == -17479 || tmpStu.m_nX == 169995200 || tmpStu.m_nY == -5249013 || tmpStu.m_nY == 170042400)
// 		{
// 			AfxMessageBox(m_strBoundaryType);
// 		}
	}
	if (m_bIsBoundary)
	{
		m_vecPointVec.push_back(vecPoint);
		m_bIsBoundary = false;
	}

	cout << endl;
};
void GdsParserToBMP::onParsedLayer(unsigned short layer) 
{
	cout << "Layer: " << layer << endl;
};
void GdsParserToBMP::onParsedWidth(int width) {
	cout << "Width: " << width << endl;
};
void GdsParserToBMP::onParsedDataType(unsigned short dataType) {
	cout << "Data Type: " << dataType << endl;
};
void GdsParserToBMP::onParsedTextType(unsigned short textType) {
	cout << "Text Type: " << textType << endl;
};
void GdsParserToBMP::onParsedAngle(double angle) {
	cout << "Angle: " << angle << endl;
};
void GdsParserToBMP::onParsedMag(double mag) {
	cout << "Mag: " << mag << endl;
};
void GdsParserToBMP::onParsedBeginExtension(unsigned short bext) {
	cout << "Begin Extension: " << bext << endl;
	m_bIsBoundary = false;
};
void GdsParserToBMP::onParsedEndExtension(unsigned short eext) {
	cout << "End Extension: " << eext << endl;
};
void GdsParserToBMP::onParsedPropertyNumber(unsigned short propNum) {
	cout << "Property Number: " << propNum << endl;
};
void GdsParserToBMP::onParsedNodeType(unsigned short nodeType) {
	cout << "Node Type: " << nodeType << endl;
};
void GdsParserToBMP::onParsedBoxType(unsigned short boxType) {
	cout << "Box Type: " << boxType << endl;
};

void GdsParserToBMP::PrintExtentPoint()
{
	cout << "MinPoint(" <<m_nMinX << "," << m_nMinY << ")"<<endl;
	cout << "MAxPoint(" <<m_nMaxX << "," << m_nMaxY << ")"<<endl;
}

void GdsParserToBMP::SetBMPDPI( int nDpi )
{
	m_nDpi = nDpi;
}
