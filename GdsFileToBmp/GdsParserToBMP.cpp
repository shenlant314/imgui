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

// const int MAX_LENGTH=1024;
// CString GetModelPath()
// {
// 	// 获得当前路径
// 	CString strPath=_T("");
// 	TCHAR fullPath[MAX_LENGTH];
// 	GetModuleFileName( _hdllInstance, fullPath, MAX_PATH );
// 	strPath.Format(_T("%s"), fullPath);
// 	strPath = strPath.Left(strPath.ReverseFind('\\'));
// 	return strPath;
// }

GdsParserToBMP::GdsParserToBMP(CProgressCtrl* pCtrlProgress)
{
	m_nMinX = 0;
	m_nMinY = 0;
	m_nMaxX = 0;
	m_nMaxY = 0;
	m_bFirst = true;
	m_pCtrlProgress = pCtrlProgress;

	CString sFileName= _T("D:\\OutDatalog.txt");
	CFileStatus status;
	if(m_outTxtFile.Open(sFileName,CFile::modeCreate | CFile::modeWrite | CFile::typeText))
	{
		m_outTxtFile.SeekToEnd();// 跳转到结尾，再写
	}
}

GdsParserToBMP::~GdsParserToBMP(void)
{
	m_outTxtFile.Close();
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

// 						bits[tmpIndex + 0] = 0; // Blue
// 						bits[tmpIndex + 1] = 0;   // Green
// 						bits[tmpIndex + 2] = 255;   // Red
					}
// 					bits[nIndex + 0] = 0; // Blue
// 					bits[nIndex + 1] = 0;   // Green
// 					bits[nIndex + 2] = 255;   // Red

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
	AfxMessageBox(strPromt);
	
	return true;
}*/

bool GdsParserToBMP::TransPointToPixel()
{
	const int height = 2540;
	const int width = 2540;
	const int nSize = height * width * 3;

	CString strPromt = _T("");
	CString strTmp;

	strTmp.Format(_T("Min(%d,%d),Max(%d,%d)\n"), m_nMinX, m_nMinY, m_nMaxX, m_nMaxY);
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
			tmpPt.m_nX = (itVec->m_nX - m_nMinX) ;
			tmpPt.m_nY = (itVec->m_nY - m_nMinY) ;
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

// 						bits[tmpIndex + 0] = 0; // Blue
// 						bits[tmpIndex + 1] = 0;   // Green
// 						bits[tmpIndex + 2] = 255;   // Red
					}
// 					bits[nIndex + 0] = 0; // Blue
// 					bits[nIndex + 1] = 0;   // Green
// 					bits[nIndex + 2] = 255;   // Red

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

	AfxMessageBox(strPromt);
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
	FILE *output = fopen("D:\\output.bmp", "wb"); // 
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
	return true;
}

void GdsParserToBMP::onParsedGDSVersion(unsigned short version) 
{
	cout << "GDSII Version: " << version << endl;
	USES_CONVERSION;
	CString strLine;
	strLine.Format(_T("\nGDSII Version: %d"),version);
	m_outTxtFile.Write(T2CA(strLine), strlen(T2CA(strLine)));
};
void GdsParserToBMP::onParsedModTime(short year, short month, short day,
									 short hour, short minute, short sec) 
{
	cout << "Modified Time: " << endl;

	if(year==0 && month==0) 
	{
		cout << "\tNot recorded." << endl;
	} 
	else 
	{
		cout << "\t" << year << "-" << SET_2W << month <<  "-" << SET_2W <<
			day << " " << SET_2W << hour << ":" << SET_2W << minute <<
			":" << SET_2W << sec << endl;
	}

	USES_CONVERSION;
	CString strLine;
	strLine.Format(_T("\nModified Time: %d-%d-%d-%d-%d-%d"),year, month,day, hour,minute,sec);
	m_outTxtFile.Write(T2CA(strLine), strlen(T2CA(strLine)));
};
void GdsParserToBMP::onParsedAccessTime(short year, short month, short day,
										short hour, short minute, short sec) 
{
	cout << "Accessed Time: " << endl;

	if(year==0 && month==0) 
	{
		cout << "\tNot recorded." << endl;
	} 
	else 
	{
		cout << "\t" << year << "-" << SET_2W << month <<  "-" << SET_2W <<
			day << " " << SET_2W << hour << ":" << SET_2W << minute <<
			":" << SET_2W << sec << endl;
	}
	USES_CONVERSION;
	CString strLine;
	strLine.Format(_T("\nAccessed Time: %d-%d-%d-%d-%d-%d"),year, month,day, hour,minute,sec);
	m_outTxtFile.Write(T2CA(strLine), strlen(T2CA(strLine)));
};
void GdsParserToBMP::onParsedLibName(const char *libName) 
{
	cout << "LibName: " << libName << endl;
	m_strBoundaryType = _T("LibName");

	USES_CONVERSION;
	CString strLine;
	strLine.Format(_T("\nLibName:  %s"),CString(libName));
	m_outTxtFile.Write(T2CA(strLine), strlen(T2CA(strLine)));
};
void GdsParserToBMP::onParsedUnits(double userUnits, double dbUnits) {
	cout << "UserUnits: " << setprecision(9) << fixed << userUnits << endl;
	cout << "DBUnits: " << setprecision(9) << fixed << dbUnits << endl;
	USES_CONVERSION;
	CString strLine;
	strLine.Format(_T("\nUserUnits:  %.9f DBUnits:%.9f"),userUnits, dbUnits);
	m_outTxtFile.Write(T2CA(strLine), strlen(T2CA(strLine)));
};
void GdsParserToBMP::onParsedStrName(const char *strName) {
	cout << "StrName: " << strName << endl;
	m_strBoundaryType = _T("StrName");

	USES_CONVERSION;
	CString strLine;
	strLine.Format(_T("\nStrName:  %s"),CString(strName));
	m_outTxtFile.Write(T2CA(strLine), strlen(T2CA(strLine)));
};
void GdsParserToBMP::onParsedBoundaryStart() {
	cout << "Boundry start" << endl;
	m_bIsBoundary = true;
	m_strBoundaryType = _T("Boundry");

	USES_CONVERSION;
	CString strLine;
	strLine.Format(_T("\nBoundry start"));
	m_outTxtFile.Write(T2CA(strLine), strlen(T2CA(strLine)));
};
void GdsParserToBMP::onParsedPathStart() {
	cout << "Path start" << endl;
	m_bIsBoundary = true;
	m_strBoundaryType = _T("Path");
	USES_CONVERSION;
	CString strLine;
	strLine.Format(_T("\nPath start"));
	m_outTxtFile.Write(T2CA(strLine), strlen(T2CA(strLine)));
};
void GdsParserToBMP::onParsedBoxStart() {
	cout << "Box start" << endl;
	m_bIsBoundary = true;
	m_strBoundaryType = _T("Box");

	USES_CONVERSION;
	CString strLine;
	strLine.Format(_T("\nBox start"));
	m_outTxtFile.Write(T2CA(strLine), strlen(T2CA(strLine)));
};
void GdsParserToBMP::onParsedEndElement() {
	cout << "Element end" << endl;
	USES_CONVERSION;
	CString strLine;
	strLine.Format(_T("\nElement end"));
	m_outTxtFile.Write(T2CA(strLine), strlen(T2CA(strLine)));
};
void GdsParserToBMP::onParsedEndStructure() {
	cout << "Structure end" << endl;
	USES_CONVERSION;
	CString strLine;
	strLine.Format(_T("\nStructure end"));
	m_outTxtFile.Write(T2CA(strLine), strlen(T2CA(strLine)));
};
void GdsParserToBMP::onParsedEndLib() {
	cout << "Lib end" << endl;
	USES_CONVERSION;
	CString strLine;
	strLine.Format(_T("\nLib end"));
	m_outTxtFile.Write(T2CA(strLine), strlen(T2CA(strLine)));
};
void GdsParserToBMP::onParsedColumnsRows(unsigned short columns, unsigned short rows) 
{
	cout << "Columns: " << columns << " Rows: " << rows << endl;

	USES_CONVERSION;
	CString strLine;
	strLine.Format(_T("\nColumns:%d Rows:%d"), columns, rows);
	m_outTxtFile.Write(T2CA(strLine), strlen(T2CA(strLine)));
};
void GdsParserToBMP::onParsedPathType(unsigned short pathType) {

	cout << "PathType: " << pathType << endl;
	USES_CONVERSION;
	CString strLine;
	strLine.Format(_T("\nPathType:"));
	m_outTxtFile.Write(T2CA(strLine), strlen(T2CA(strLine)));
};
void GdsParserToBMP::onParsedStrans(short strans) {
	cout << "Strans: " << strans << endl;

	USES_CONVERSION;
	CString strLine;
	strLine.Format(_T("\nStrans:"));
	m_outTxtFile.Write(T2CA(strLine), strlen(T2CA(strLine)));
};
void GdsParserToBMP::onParsedPresentation(short font, short valign, short halign) 
{
	cout << "Font: " << font << endl;
	cout << "Valign: " << valign << endl;
	cout << "Halign: " << halign << endl;

	USES_CONVERSION;
	CString strLine;
	strLine.Format(_T("\nFont: %d Valign:%d Halign:%d"), font, valign, halign);
	m_outTxtFile.Write(T2CA(strLine), strlen(T2CA(strLine)));
};
void GdsParserToBMP::onParsedNodeStart() 
{
	cout << "Node start" << endl;
	m_bIsBoundary = false;
	m_strBoundaryType = _T("Node");

	USES_CONVERSION;
	CString strLine;
	strLine.Format(_T("\nNode start"));
	m_outTxtFile.Write(T2CA(strLine), strlen(T2CA(strLine)));
};
void GdsParserToBMP::onParsedTextStart() {
	cout << "Text start" << endl;
	m_bIsBoundary = false;
	m_strBoundaryType = _T("Text");

	USES_CONVERSION;
	CString strLine;
	strLine.Format(_T("\nText start"));
	m_outTxtFile.Write(T2CA(strLine), strlen(T2CA(strLine)));
};
void GdsParserToBMP::onParsedSrefStart() 
{
	cout << "Sref start" << endl;
	m_bIsBoundary = false;
	m_strBoundaryType = _T("Sref");

	USES_CONVERSION;
	CString strLine;
	strLine.Format(_T("\nSref start"));
	m_outTxtFile.Write(T2CA(strLine), strlen(T2CA(strLine)));
};
void GdsParserToBMP::onParsedArefStart() {
	cout << "Aref start" << endl;
	m_bIsBoundary = false;
	m_strBoundaryType = _T("Aref");

	USES_CONVERSION;
	CString strLine;
	strLine.Format(_T("\nAref start"));
	m_outTxtFile.Write(T2CA(strLine), strlen(T2CA(strLine)));
};
void GdsParserToBMP::onParsedSname(const char *sname) {
	cout << "Sname: " << sname << endl;

	USES_CONVERSION;
	CString strLine;
	strLine.Format(_T("\nSname:%s"), CString(sname));
	m_outTxtFile.Write(T2CA(strLine), strlen(T2CA(strLine)));
};
void GdsParserToBMP::onParsedString(const char *str) {
	cout << "String: " << str << endl;

	USES_CONVERSION;
	CString strLine;
	strLine.Format(_T("\nString:%s"), CString(str));
	m_outTxtFile.Write(T2CA(strLine), strlen(T2CA(strLine)));
};
void GdsParserToBMP::onParsedPropValue(const char *propValue) 
{
	cout << "Prop Value: " << propValue << endl;

	USES_CONVERSION;
	CString strLine;
	strLine.Format(_T("\nProp Value:%s"), CString(propValue));
	m_outTxtFile.Write(T2CA(strLine), strlen(T2CA(strLine)));
};
void GdsParserToBMP::onParsedXY(int count, std::vector<int>& x, std::vector<int>& y) {
	cout << "XY: " << count << endl;

	USES_CONVERSION;
	CString strLine;
	strLine.Format(_T("\nXY::(%d)"), count);

	GePointVector vecPoint;
	for(int i=0; i<count; ++i) 
	{
		cout << "(" << x[i] << "," << y[i] << ")";
		CString strTmp;
		strTmp.Format(_T("(%d,%d)"), x[i], y[i]);
		strLine += strTmp;
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
	m_outTxtFile.Write(T2CA(strLine), strlen(T2CA(strLine)));
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

	USES_CONVERSION;
	CString strLine;
	strLine.Format(_T("\nLayer:%d"), layer);
	m_outTxtFile.Write(T2CA(strLine), strlen(T2CA(strLine)));
};
void GdsParserToBMP::onParsedWidth(int width) {
	cout << "Width: " << width << endl;
	USES_CONVERSION;
	CString strLine;
	strLine.Format(_T("\nWidth:%d"), width);
	m_outTxtFile.Write(T2CA(strLine), strlen(T2CA(strLine)));
};
void GdsParserToBMP::onParsedDataType(unsigned short dataType) {
	cout << "Data Type: " << dataType << endl;
	USES_CONVERSION;
	CString strLine;
	strLine.Format(_T("\nData Type:%d"), dataType);
	m_outTxtFile.Write(T2CA(strLine), strlen(T2CA(strLine)));
};
void GdsParserToBMP::onParsedTextType(unsigned short textType) {
	cout << "Text Type: " << textType << endl;
	USES_CONVERSION;
	CString strLine;
	strLine.Format(_T("\nText Type:%d"), textType);
	m_outTxtFile.Write(T2CA(strLine), strlen(T2CA(strLine)));
};
void GdsParserToBMP::onParsedAngle(double angle) {
	cout << "Angle: " << angle << endl;
	USES_CONVERSION;
	CString strLine;
	strLine.Format(_T("\nAngle:%.6f"), angle);
	m_outTxtFile.Write(T2CA(strLine), strlen(T2CA(strLine)));
};
void GdsParserToBMP::onParsedMag(double mag) {
	cout << "Mag: " << mag << endl;
	USES_CONVERSION;
	CString strLine;
	strLine.Format(_T("\nMag:%.6f"), mag);
	m_outTxtFile.Write(T2CA(strLine), strlen(T2CA(strLine)));
};
void GdsParserToBMP::onParsedBeginExtension(unsigned short bext) {
	cout << "Begin Extension: " << bext << endl;
	m_bIsBoundary = false;
	USES_CONVERSION;
	CString strLine;
	strLine.Format(_T("\nBegin Extension:%d"), bext);
	m_outTxtFile.Write(T2CA(strLine), strlen(T2CA(strLine)));
};
void GdsParserToBMP::onParsedEndExtension(unsigned short eext) {
	cout << "End Extension: " << eext << endl;
	USES_CONVERSION;
	CString strLine;
	strLine.Format(_T("\nEnd Extension:%d"), eext);
	m_outTxtFile.Write(T2CA(strLine), strlen(T2CA(strLine)));
};
void GdsParserToBMP::onParsedPropertyNumber(unsigned short propNum) {
	cout << "Property Number: " << propNum << endl;
	USES_CONVERSION;
	CString strLine;
	strLine.Format(_T("\nProperty Number:%d"), propNum);
	m_outTxtFile.Write(T2CA(strLine), strlen(T2CA(strLine)));
};
void GdsParserToBMP::onParsedNodeType(unsigned short nodeType) {
	cout << "Node Type: " << nodeType << endl;
	USES_CONVERSION;
	CString strLine;
	strLine.Format(_T("\nNode Type:%d"), nodeType);
	m_outTxtFile.Write(T2CA(strLine), strlen(T2CA(strLine)));
};
void GdsParserToBMP::onParsedBoxType(unsigned short boxType) {
	cout << "Box Type: " << boxType << endl;
	USES_CONVERSION;
	CString strLine;
	strLine.Format(_T("\nBox Type:%d"), boxType);
	m_outTxtFile.Write(T2CA(strLine), strlen(T2CA(strLine)));
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
