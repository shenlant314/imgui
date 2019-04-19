// GdsFileReadTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "libGDSII.h"
using namespace libGDSII;
int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_CTYPE, "");
	GDSIIData *gdsIIData  = new GDSIIData( string("D:\\code\\tmpcode\\GdsFileReadTest\\Debug\\MHD.gds") );
	if (gdsIIData->ErrMsg)
	{ 
		printf("error: %s (aborting)\n",gdsIIData->ErrMsg->c_str());
		return 0;
	}
	gdsIIData->WriteDescription();                // writes to console
	gdsIIData->WriteDescription("MyOutputFile");

	/***************************************************************/
	/* get all polygons on layer 3 *********************************/
	/***************************************************************/
	PolygonList Layer3Polygons = gdsIIData->GetPolygons(3);

	printf("Found %lu polygons on layer 3: \n",Layer3Polygons.size());
	for(size_t np=0; np<Layer3Polygons.size(); np++)
	{ 
		printf("Polygon #%lu has vertices: ",np);
	
		for(int nv=0; nv<Layer3Polygons[np].size()/2; nv++)
			printf(" {%e,%e} ",Layer3Polygons[np][2*nv+0],Layer3Polygons[2*nv+1]);
	
		printf("\n");
	}
	/***************************************************************/
	/* get all polygons on layer 3 that contain the reference point*/
	/* of the text string "Geometry" (also on layer 3)             */
	/***************************************************************/
	//PolygonList Layer3Polygons = gdsIIData->GetPolygons("Geometry", 3);

	/***************************************************************/
	/* get all polygons on any layer that contain the reference pt */
	/* of the text string "Geometry" on the same layer             */
	/***************************************************************/
	//PolygonList Layer3Polygons = gdsIIData->GetPolygons("Geometry");

	return 0;
}

