/* Add your custom classes in this file */
/* Remember also to modify inc/rooCommon.h */
#include "RooFormulaVarExt.h"
#include "FlexibleInterpVarExt.h"
#include "FlexibleInterpVarMkII.h"
#include "HggTwoSidedCBPdf.h"
#include "HggMG5aMCNLOLineShapePdf.h"
#include "CommonFunc.h"
#include "statistics.h"
#include "LEPEntry.h"

#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

#pragma link C++ nestedclass;

#pragma link C++ class RooFormulaVarExt+;
#pragma link C++ class FlexibleInterpVarExt+;
#pragma link C++ class FlexibleInterpVarMkII+;
#pragma link C++ class HggTwoSidedCBPdf+;
#pragma link C++ class HggMG5aMCNLOLineShapePdf+;
//#pragma link C++ class RooStarMomentMorph+;
#pragma link C++ class LEPError+;
#pragma link C++ class LEPEntry+;
#pragma link C++ class statistics+;

#pragma link C++ class std::list<RooAbsData*>::iterator;

#pragma link C++ namespace CommonFunc;

#endif
