// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME srcdIquickFit_Dict

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "inc/ExtendedMinimizer.h"
#include "inc/ExtendedModel.h"
#include "inc/FlexibleInterpVarExt.h"
#include "inc/FlexibleInterpVarMkII.h"
#include "inc/HggMG5aMCNLOLineShapePdf.h"
#include "inc/HggTwoSidedCBPdf.h"
#include "inc/LEPEntry.h"
#include "inc/RooFormulaVarExt.h"
#include "inc/statistics.h"

// Header files passed via #pragma extra_include

namespace CommonFunc {
   namespace ROOT {
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance();
      static TClass *CommonFunc_Dictionary();

      // Function generating the singleton type initializer
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance()
      {
         static ::ROOT::TGenericClassInfo 
            instance("CommonFunc", 0 /*version*/, "CommonFunc.h", 10,
                     ::ROOT::DefineBehavior((void*)0,(void*)0),
                     &CommonFunc_Dictionary, 0);
         return &instance;
      }
      // Insure that the inline function is _not_ optimized away by the compiler
      ::ROOT::TGenericClassInfo *(*_R__UNIQUE_(InitFunctionKeeper))() = &GenerateInitInstance;  
      // Static variable to force the class initialization
      static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstance(); R__UseDummy(_R__UNIQUE_(Init));

      // Dictionary for non-ClassDef classes
      static TClass *CommonFunc_Dictionary() {
         return GenerateInitInstance()->GetClass();
      }

   }
}

namespace ROOT {
   static void delete_ExtendedMinimizer(void *p);
   static void deleteArray_ExtendedMinimizer(void *p);
   static void destruct_ExtendedMinimizer(void *p);
   static void streamer_ExtendedMinimizer(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::ExtendedMinimizer*)
   {
      ::ExtendedMinimizer *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::ExtendedMinimizer >(0);
      static ::ROOT::TGenericClassInfo 
         instance("ExtendedMinimizer", ::ExtendedMinimizer::Class_Version(), "ExtendedMinimizer.h", 52,
                  typeid(::ExtendedMinimizer), DefineBehavior(ptr, ptr),
                  &::ExtendedMinimizer::Dictionary, isa_proxy, 16,
                  sizeof(::ExtendedMinimizer) );
      instance.SetDelete(&delete_ExtendedMinimizer);
      instance.SetDeleteArray(&deleteArray_ExtendedMinimizer);
      instance.SetDestructor(&destruct_ExtendedMinimizer);
      instance.SetStreamerFunc(&streamer_ExtendedMinimizer);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::ExtendedMinimizer*)
   {
      return GenerateInitInstanceLocal((::ExtendedMinimizer*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::ExtendedMinimizer*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_ExtendedModel(void *p);
   static void deleteArray_ExtendedModel(void *p);
   static void destruct_ExtendedModel(void *p);
   static void streamer_ExtendedModel(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::ExtendedModel*)
   {
      ::ExtendedModel *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::ExtendedModel >(0);
      static ::ROOT::TGenericClassInfo 
         instance("ExtendedModel", ::ExtendedModel::Class_Version(), "ExtendedModel.h", 43,
                  typeid(::ExtendedModel), DefineBehavior(ptr, ptr),
                  &::ExtendedModel::Dictionary, isa_proxy, 16,
                  sizeof(::ExtendedModel) );
      instance.SetDelete(&delete_ExtendedModel);
      instance.SetDeleteArray(&deleteArray_ExtendedModel);
      instance.SetDestructor(&destruct_ExtendedModel);
      instance.SetStreamerFunc(&streamer_ExtendedModel);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::ExtendedModel*)
   {
      return GenerateInitInstanceLocal((::ExtendedModel*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::ExtendedModel*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_RooFormulaVarExt(void *p = 0);
   static void *newArray_RooFormulaVarExt(Long_t size, void *p);
   static void delete_RooFormulaVarExt(void *p);
   static void deleteArray_RooFormulaVarExt(void *p);
   static void destruct_RooFormulaVarExt(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RooFormulaVarExt*)
   {
      ::RooFormulaVarExt *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RooFormulaVarExt >(0);
      static ::ROOT::TGenericClassInfo 
         instance("RooFormulaVarExt", ::RooFormulaVarExt::Class_Version(), "RooFormulaVarExt.h", 28,
                  typeid(::RooFormulaVarExt), DefineBehavior(ptr, ptr),
                  &::RooFormulaVarExt::Dictionary, isa_proxy, 4,
                  sizeof(::RooFormulaVarExt) );
      instance.SetNew(&new_RooFormulaVarExt);
      instance.SetNewArray(&newArray_RooFormulaVarExt);
      instance.SetDelete(&delete_RooFormulaVarExt);
      instance.SetDeleteArray(&deleteArray_RooFormulaVarExt);
      instance.SetDestructor(&destruct_RooFormulaVarExt);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RooFormulaVarExt*)
   {
      return GenerateInitInstanceLocal((::RooFormulaVarExt*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::RooFormulaVarExt*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_RooStatscLcLHistFactorycLcLFlexibleInterpVarExt(void *p = 0);
   static void *newArray_RooStatscLcLHistFactorycLcLFlexibleInterpVarExt(Long_t size, void *p);
   static void delete_RooStatscLcLHistFactorycLcLFlexibleInterpVarExt(void *p);
   static void deleteArray_RooStatscLcLHistFactorycLcLFlexibleInterpVarExt(void *p);
   static void destruct_RooStatscLcLHistFactorycLcLFlexibleInterpVarExt(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RooStats::HistFactory::FlexibleInterpVarExt*)
   {
      ::RooStats::HistFactory::FlexibleInterpVarExt *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RooStats::HistFactory::FlexibleInterpVarExt >(0);
      static ::ROOT::TGenericClassInfo 
         instance("RooStats::HistFactory::FlexibleInterpVarExt", ::RooStats::HistFactory::FlexibleInterpVarExt::Class_Version(), "FlexibleInterpVarExt.h", 32,
                  typeid(::RooStats::HistFactory::FlexibleInterpVarExt), DefineBehavior(ptr, ptr),
                  &::RooStats::HistFactory::FlexibleInterpVarExt::Dictionary, isa_proxy, 4,
                  sizeof(::RooStats::HistFactory::FlexibleInterpVarExt) );
      instance.SetNew(&new_RooStatscLcLHistFactorycLcLFlexibleInterpVarExt);
      instance.SetNewArray(&newArray_RooStatscLcLHistFactorycLcLFlexibleInterpVarExt);
      instance.SetDelete(&delete_RooStatscLcLHistFactorycLcLFlexibleInterpVarExt);
      instance.SetDeleteArray(&deleteArray_RooStatscLcLHistFactorycLcLFlexibleInterpVarExt);
      instance.SetDestructor(&destruct_RooStatscLcLHistFactorycLcLFlexibleInterpVarExt);

      ::ROOT::AddClassAlternate("RooStats::HistFactory::FlexibleInterpVarExt","FlexibleInterpVarExt");
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RooStats::HistFactory::FlexibleInterpVarExt*)
   {
      return GenerateInitInstanceLocal((::RooStats::HistFactory::FlexibleInterpVarExt*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::RooStats::HistFactory::FlexibleInterpVarExt*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FlexibleInterpVarMkII(void *p = 0);
   static void *newArray_FlexibleInterpVarMkII(Long_t size, void *p);
   static void delete_FlexibleInterpVarMkII(void *p);
   static void deleteArray_FlexibleInterpVarMkII(void *p);
   static void destruct_FlexibleInterpVarMkII(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FlexibleInterpVarMkII*)
   {
      ::FlexibleInterpVarMkII *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FlexibleInterpVarMkII >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FlexibleInterpVarMkII", ::FlexibleInterpVarMkII::Class_Version(), "FlexibleInterpVarMkII.h", 26,
                  typeid(::FlexibleInterpVarMkII), DefineBehavior(ptr, ptr),
                  &::FlexibleInterpVarMkII::Dictionary, isa_proxy, 4,
                  sizeof(::FlexibleInterpVarMkII) );
      instance.SetNew(&new_FlexibleInterpVarMkII);
      instance.SetNewArray(&newArray_FlexibleInterpVarMkII);
      instance.SetDelete(&delete_FlexibleInterpVarMkII);
      instance.SetDeleteArray(&deleteArray_FlexibleInterpVarMkII);
      instance.SetDestructor(&destruct_FlexibleInterpVarMkII);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FlexibleInterpVarMkII*)
   {
      return GenerateInitInstanceLocal((::FlexibleInterpVarMkII*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FlexibleInterpVarMkII*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_HggTwoSidedCBPdf(void *p = 0);
   static void *newArray_HggTwoSidedCBPdf(Long_t size, void *p);
   static void delete_HggTwoSidedCBPdf(void *p);
   static void deleteArray_HggTwoSidedCBPdf(void *p);
   static void destruct_HggTwoSidedCBPdf(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::HggTwoSidedCBPdf*)
   {
      ::HggTwoSidedCBPdf *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::HggTwoSidedCBPdf >(0);
      static ::ROOT::TGenericClassInfo 
         instance("HggTwoSidedCBPdf", ::HggTwoSidedCBPdf::Class_Version(), "HggTwoSidedCBPdf.h", 17,
                  typeid(::HggTwoSidedCBPdf), DefineBehavior(ptr, ptr),
                  &::HggTwoSidedCBPdf::Dictionary, isa_proxy, 4,
                  sizeof(::HggTwoSidedCBPdf) );
      instance.SetNew(&new_HggTwoSidedCBPdf);
      instance.SetNewArray(&newArray_HggTwoSidedCBPdf);
      instance.SetDelete(&delete_HggTwoSidedCBPdf);
      instance.SetDeleteArray(&deleteArray_HggTwoSidedCBPdf);
      instance.SetDestructor(&destruct_HggTwoSidedCBPdf);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::HggTwoSidedCBPdf*)
   {
      return GenerateInitInstanceLocal((::HggTwoSidedCBPdf*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::HggTwoSidedCBPdf*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_HggMG5aMCNLOLineShapePdf(void *p = 0);
   static void *newArray_HggMG5aMCNLOLineShapePdf(Long_t size, void *p);
   static void delete_HggMG5aMCNLOLineShapePdf(void *p);
   static void deleteArray_HggMG5aMCNLOLineShapePdf(void *p);
   static void destruct_HggMG5aMCNLOLineShapePdf(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::HggMG5aMCNLOLineShapePdf*)
   {
      ::HggMG5aMCNLOLineShapePdf *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::HggMG5aMCNLOLineShapePdf >(0);
      static ::ROOT::TGenericClassInfo 
         instance("HggMG5aMCNLOLineShapePdf", ::HggMG5aMCNLOLineShapePdf::Class_Version(), "HggMG5aMCNLOLineShapePdf.h", 24,
                  typeid(::HggMG5aMCNLOLineShapePdf), DefineBehavior(ptr, ptr),
                  &::HggMG5aMCNLOLineShapePdf::Dictionary, isa_proxy, 4,
                  sizeof(::HggMG5aMCNLOLineShapePdf) );
      instance.SetNew(&new_HggMG5aMCNLOLineShapePdf);
      instance.SetNewArray(&newArray_HggMG5aMCNLOLineShapePdf);
      instance.SetDelete(&delete_HggMG5aMCNLOLineShapePdf);
      instance.SetDeleteArray(&deleteArray_HggMG5aMCNLOLineShapePdf);
      instance.SetDestructor(&destruct_HggMG5aMCNLOLineShapePdf);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::HggMG5aMCNLOLineShapePdf*)
   {
      return GenerateInitInstanceLocal((::HggMG5aMCNLOLineShapePdf*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::HggMG5aMCNLOLineShapePdf*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_LEPError(void *p);
   static void deleteArray_LEPError(void *p);
   static void destruct_LEPError(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LEPError*)
   {
      ::LEPError *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LEPError >(0);
      static ::ROOT::TGenericClassInfo 
         instance("LEPError", ::LEPError::Class_Version(), "LEPEntry.h", 28,
                  typeid(::LEPError), DefineBehavior(ptr, ptr),
                  &::LEPError::Dictionary, isa_proxy, 4,
                  sizeof(::LEPError) );
      instance.SetDelete(&delete_LEPError);
      instance.SetDeleteArray(&deleteArray_LEPError);
      instance.SetDestructor(&destruct_LEPError);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LEPError*)
   {
      return GenerateInitInstanceLocal((::LEPError*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::LEPError*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_LEPEntry(void *p = 0);
   static void *newArray_LEPEntry(Long_t size, void *p);
   static void delete_LEPEntry(void *p);
   static void deleteArray_LEPEntry(void *p);
   static void destruct_LEPEntry(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LEPEntry*)
   {
      ::LEPEntry *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LEPEntry >(0);
      static ::ROOT::TGenericClassInfo 
         instance("LEPEntry", ::LEPEntry::Class_Version(), "LEPEntry.h", 68,
                  typeid(::LEPEntry), DefineBehavior(ptr, ptr),
                  &::LEPEntry::Dictionary, isa_proxy, 4,
                  sizeof(::LEPEntry) );
      instance.SetNew(&new_LEPEntry);
      instance.SetNewArray(&newArray_LEPEntry);
      instance.SetDelete(&delete_LEPEntry);
      instance.SetDeleteArray(&deleteArray_LEPEntry);
      instance.SetDestructor(&destruct_LEPEntry);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LEPEntry*)
   {
      return GenerateInitInstanceLocal((::LEPEntry*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::LEPEntry*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_statistics(void *p = 0);
   static void *newArray_statistics(Long_t size, void *p);
   static void delete_statistics(void *p);
   static void deleteArray_statistics(void *p);
   static void destruct_statistics(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::statistics*)
   {
      ::statistics *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::statistics >(0);
      static ::ROOT::TGenericClassInfo 
         instance("statistics", ::statistics::Class_Version(), "statistics.h", 27,
                  typeid(::statistics), DefineBehavior(ptr, ptr),
                  &::statistics::Dictionary, isa_proxy, 4,
                  sizeof(::statistics) );
      instance.SetNew(&new_statistics);
      instance.SetNewArray(&newArray_statistics);
      instance.SetDelete(&delete_statistics);
      instance.SetDeleteArray(&deleteArray_statistics);
      instance.SetDestructor(&destruct_statistics);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::statistics*)
   {
      return GenerateInitInstanceLocal((::statistics*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::statistics*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static TClass *_List_iteratorlERooAbsDatamUgR_Dictionary();
   static void _List_iteratorlERooAbsDatamUgR_TClassManip(TClass*);
   static void *new__List_iteratorlERooAbsDatamUgR(void *p = 0);
   static void *newArray__List_iteratorlERooAbsDatamUgR(Long_t size, void *p);
   static void delete__List_iteratorlERooAbsDatamUgR(void *p);
   static void deleteArray__List_iteratorlERooAbsDatamUgR(void *p);
   static void destruct__List_iteratorlERooAbsDatamUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::_List_iterator<RooAbsData*>*)
   {
      ::_List_iterator<RooAbsData*> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::_List_iterator<RooAbsData*>));
      static ::ROOT::TGenericClassInfo 
         instance("_List_iterator<RooAbsData*>", "list", 125,
                  typeid(::_List_iterator<RooAbsData*>), DefineBehavior(ptr, ptr),
                  &_List_iteratorlERooAbsDatamUgR_Dictionary, isa_proxy, 0,
                  sizeof(::_List_iterator<RooAbsData*>) );
      instance.SetNew(&new__List_iteratorlERooAbsDatamUgR);
      instance.SetNewArray(&newArray__List_iteratorlERooAbsDatamUgR);
      instance.SetDelete(&delete__List_iteratorlERooAbsDatamUgR);
      instance.SetDeleteArray(&deleteArray__List_iteratorlERooAbsDatamUgR);
      instance.SetDestructor(&destruct__List_iteratorlERooAbsDatamUgR);

      ::ROOT::AddClassAlternate("_List_iterator<RooAbsData*>","list<RooAbsData*>::iterator");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::_List_iterator<RooAbsData*>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *_List_iteratorlERooAbsDatamUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::_List_iterator<RooAbsData*>*)0x0)->GetClass();
      _List_iteratorlERooAbsDatamUgR_TClassManip(theClass);
   return theClass;
   }

   static void _List_iteratorlERooAbsDatamUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr ExtendedMinimizer::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *ExtendedMinimizer::Class_Name()
{
   return "ExtendedMinimizer";
}

//______________________________________________________________________________
const char *ExtendedMinimizer::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::ExtendedMinimizer*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int ExtendedMinimizer::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::ExtendedMinimizer*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *ExtendedMinimizer::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::ExtendedMinimizer*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *ExtendedMinimizer::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::ExtendedMinimizer*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr ExtendedModel::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *ExtendedModel::Class_Name()
{
   return "ExtendedModel";
}

//______________________________________________________________________________
const char *ExtendedModel::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::ExtendedModel*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int ExtendedModel::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::ExtendedModel*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *ExtendedModel::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::ExtendedModel*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *ExtendedModel::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::ExtendedModel*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr RooFormulaVarExt::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *RooFormulaVarExt::Class_Name()
{
   return "RooFormulaVarExt";
}

//______________________________________________________________________________
const char *RooFormulaVarExt::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooFormulaVarExt*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int RooFormulaVarExt::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooFormulaVarExt*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *RooFormulaVarExt::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooFormulaVarExt*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *RooFormulaVarExt::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooFormulaVarExt*)0x0)->GetClass(); }
   return fgIsA;
}

namespace RooStats {
   namespace HistFactory {
//______________________________________________________________________________
atomic_TClass_ptr FlexibleInterpVarExt::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FlexibleInterpVarExt::Class_Name()
{
   return "RooStats::HistFactory::FlexibleInterpVarExt";
}

//______________________________________________________________________________
const char *FlexibleInterpVarExt::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooStats::HistFactory::FlexibleInterpVarExt*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FlexibleInterpVarExt::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooStats::HistFactory::FlexibleInterpVarExt*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FlexibleInterpVarExt::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooStats::HistFactory::FlexibleInterpVarExt*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FlexibleInterpVarExt::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooStats::HistFactory::FlexibleInterpVarExt*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace RooStats::HistFactory
} // namespace RooStats::HistFactory
//______________________________________________________________________________
atomic_TClass_ptr FlexibleInterpVarMkII::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FlexibleInterpVarMkII::Class_Name()
{
   return "FlexibleInterpVarMkII";
}

//______________________________________________________________________________
const char *FlexibleInterpVarMkII::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FlexibleInterpVarMkII*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FlexibleInterpVarMkII::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FlexibleInterpVarMkII*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FlexibleInterpVarMkII::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FlexibleInterpVarMkII*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FlexibleInterpVarMkII::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FlexibleInterpVarMkII*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr HggTwoSidedCBPdf::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *HggTwoSidedCBPdf::Class_Name()
{
   return "HggTwoSidedCBPdf";
}

//______________________________________________________________________________
const char *HggTwoSidedCBPdf::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::HggTwoSidedCBPdf*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int HggTwoSidedCBPdf::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::HggTwoSidedCBPdf*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *HggTwoSidedCBPdf::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::HggTwoSidedCBPdf*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *HggTwoSidedCBPdf::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::HggTwoSidedCBPdf*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr HggMG5aMCNLOLineShapePdf::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *HggMG5aMCNLOLineShapePdf::Class_Name()
{
   return "HggMG5aMCNLOLineShapePdf";
}

//______________________________________________________________________________
const char *HggMG5aMCNLOLineShapePdf::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::HggMG5aMCNLOLineShapePdf*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int HggMG5aMCNLOLineShapePdf::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::HggMG5aMCNLOLineShapePdf*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *HggMG5aMCNLOLineShapePdf::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::HggMG5aMCNLOLineShapePdf*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *HggMG5aMCNLOLineShapePdf::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::HggMG5aMCNLOLineShapePdf*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LEPError::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *LEPError::Class_Name()
{
   return "LEPError";
}

//______________________________________________________________________________
const char *LEPError::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LEPError*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int LEPError::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LEPError*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LEPError::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LEPError*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LEPError::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LEPError*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LEPEntry::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *LEPEntry::Class_Name()
{
   return "LEPEntry";
}

//______________________________________________________________________________
const char *LEPEntry::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LEPEntry*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int LEPEntry::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LEPEntry*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LEPEntry::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LEPEntry*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LEPEntry::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LEPEntry*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr statistics::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *statistics::Class_Name()
{
   return "statistics";
}

//______________________________________________________________________________
const char *statistics::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::statistics*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int statistics::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::statistics*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *statistics::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::statistics*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *statistics::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::statistics*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void ExtendedMinimizer::Streamer(TBuffer &R__b)
{
   // Stream an object of class ExtendedMinimizer.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TNamed::Streamer(R__b);
      R__b >> fFile;
      R__b >> fPdf;
      R__b >> fData;
      R__b >> fNll;
      R__b >> fMinimizer;
      R__b >> fFitResult;
      fHesseMatrix.Streamer(R__b);
      R__b >> fEigenValues;
      R__b >> fEigenVectors;
      fFitCmdList.Streamer(R__b);
      fScanCmdList.Streamer(R__b);
      fNllCmdList.Streamer(R__b);
      R__b >> fOptConst;
      R__b >> fVerbose;
      R__b >> fSave;
      R__b >> fTimer;
      R__b >> fPrintLevel;
      R__b >> fDefaultStrategy;
      R__b >> fHesse;
      R__b >> fMinos;
      R__b >> fScan;
      R__b >> fNumee;
      R__b >> fDoEEWall;
      R__b >> fRetry;
      R__b >> fEigen;
      R__b >> fReuseMinimizer;
      R__b >> fReuseNLL;
      R__b >> fEps;
      R__b >> fNsigma;
      R__b >> fPrecision;
      R__b >> fMinosSet;
      R__b >> fCondSet;
      R__b >> fScanSet;
      { TString R__str; R__str.Streamer(R__b); fMinimizerType = R__str.Data(); }
      { TString R__str; R__str.Streamer(R__b); fMinimizerAlgo = R__str.Data(); }
      R__b >> fMinNll;
      R__b.CheckByteCount(R__s, R__c, ExtendedMinimizer::IsA());
   } else {
      R__c = R__b.WriteVersion(ExtendedMinimizer::IsA(), kTRUE);
      TNamed::Streamer(R__b);
      R__b << fFile;
      R__b << fPdf;
      R__b << fData;
      R__b << fNll;
      R__b << fMinimizer;
      R__b << fFitResult;
      fHesseMatrix.Streamer(R__b);
      R__b << fEigenValues;
      R__b << fEigenVectors;
      fFitCmdList.Streamer(R__b);
      fScanCmdList.Streamer(R__b);
      fNllCmdList.Streamer(R__b);
      R__b << fOptConst;
      R__b << fVerbose;
      R__b << fSave;
      R__b << fTimer;
      R__b << fPrintLevel;
      R__b << fDefaultStrategy;
      R__b << fHesse;
      R__b << fMinos;
      R__b << fScan;
      R__b << fNumee;
      R__b << fDoEEWall;
      R__b << fRetry;
      R__b << fEigen;
      R__b << fReuseMinimizer;
      R__b << fReuseNLL;
      R__b << fEps;
      R__b << fNsigma;
      R__b << fPrecision;
      R__b << fMinosSet;
      R__b << fCondSet;
      R__b << fScanSet;
      { TString R__str = fMinimizerType.c_str(); R__str.Streamer(R__b);}
      { TString R__str = fMinimizerAlgo.c_str(); R__str.Streamer(R__b);}
      R__b << fMinNll;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_ExtendedMinimizer(void *p) {
      delete ((::ExtendedMinimizer*)p);
   }
   static void deleteArray_ExtendedMinimizer(void *p) {
      delete [] ((::ExtendedMinimizer*)p);
   }
   static void destruct_ExtendedMinimizer(void *p) {
      typedef ::ExtendedMinimizer current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_ExtendedMinimizer(TBuffer &buf, void *obj) {
      ((::ExtendedMinimizer*)obj)->::ExtendedMinimizer::Streamer(buf);
   }
} // end of namespace ROOT for class ::ExtendedMinimizer

//______________________________________________________________________________
void ExtendedModel::Streamer(TBuffer &R__b)
{
   // Stream an object of class ExtendedModel.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TNamed::Streamer(R__b);
      { TString R__str; R__str.Streamer(R__b); fFileName = R__str.Data(); }
      { TString R__str; R__str.Streamer(R__b); fWsName = R__str.Data(); }
      { TString R__str; R__str.Streamer(R__b); fModelConfigName = R__str.Data(); }
      { TString R__str; R__str.Streamer(R__b); fDataName = R__str.Data(); }
      { TString R__str; R__str.Streamer(R__b); fSnapshotName = R__str.Data(); }
      R__b >> fBinnedLikelihood;
      { TString R__str; R__str.Streamer(R__b); fTagAsMeasurement = R__str.Data(); }
      R__b >> fFixCache;
      R__b >> fFixMulti;
      R__b >> fInterpolationCode;
      R__b >> fFile;
      R__b >> fWorkspace;
      R__b >> fModelConfig;
      R__b >> fPdf;
      R__b >> fData;
      R__b >> fNuis;
      R__b >> fGlobs;
      R__b >> fPOIs;
      R__b >> fObs;
      R__b.CheckByteCount(R__s, R__c, ExtendedModel::IsA());
   } else {
      R__c = R__b.WriteVersion(ExtendedModel::IsA(), kTRUE);
      TNamed::Streamer(R__b);
      { TString R__str = fFileName.c_str(); R__str.Streamer(R__b);}
      { TString R__str = fWsName.c_str(); R__str.Streamer(R__b);}
      { TString R__str = fModelConfigName.c_str(); R__str.Streamer(R__b);}
      { TString R__str = fDataName.c_str(); R__str.Streamer(R__b);}
      { TString R__str = fSnapshotName.c_str(); R__str.Streamer(R__b);}
      R__b << fBinnedLikelihood;
      { TString R__str = fTagAsMeasurement.c_str(); R__str.Streamer(R__b);}
      R__b << fFixCache;
      R__b << fFixMulti;
      R__b << fInterpolationCode;
      R__b << fFile;
      R__b << fWorkspace;
      R__b << fModelConfig;
      R__b << fPdf;
      R__b << fData;
      R__b << fNuis;
      R__b << fGlobs;
      R__b << fPOIs;
      R__b << fObs;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_ExtendedModel(void *p) {
      delete ((::ExtendedModel*)p);
   }
   static void deleteArray_ExtendedModel(void *p) {
      delete [] ((::ExtendedModel*)p);
   }
   static void destruct_ExtendedModel(void *p) {
      typedef ::ExtendedModel current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_ExtendedModel(TBuffer &buf, void *obj) {
      ((::ExtendedModel*)obj)->::ExtendedModel::Streamer(buf);
   }
} // end of namespace ROOT for class ::ExtendedModel

//______________________________________________________________________________
void RooFormulaVarExt::Streamer(TBuffer &R__b)
{
   // Stream an object of class RooFormulaVarExt.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(RooFormulaVarExt::Class(),this);
   } else {
      R__b.WriteClassBuffer(RooFormulaVarExt::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_RooFormulaVarExt(void *p) {
      return  p ? new(p) ::RooFormulaVarExt : new ::RooFormulaVarExt;
   }
   static void *newArray_RooFormulaVarExt(Long_t nElements, void *p) {
      return p ? new(p) ::RooFormulaVarExt[nElements] : new ::RooFormulaVarExt[nElements];
   }
   // Wrapper around operator delete
   static void delete_RooFormulaVarExt(void *p) {
      delete ((::RooFormulaVarExt*)p);
   }
   static void deleteArray_RooFormulaVarExt(void *p) {
      delete [] ((::RooFormulaVarExt*)p);
   }
   static void destruct_RooFormulaVarExt(void *p) {
      typedef ::RooFormulaVarExt current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::RooFormulaVarExt

namespace RooStats {
   namespace HistFactory {
//______________________________________________________________________________
void FlexibleInterpVarExt::Streamer(TBuffer &R__b)
{
   // Stream an object of class RooStats::HistFactory::FlexibleInterpVarExt.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(RooStats::HistFactory::FlexibleInterpVarExt::Class(),this);
   } else {
      R__b.WriteClassBuffer(RooStats::HistFactory::FlexibleInterpVarExt::Class(),this);
   }
}

} // namespace RooStats::HistFactory
} // namespace RooStats::HistFactory
namespace ROOT {
   // Wrappers around operator new
   static void *new_RooStatscLcLHistFactorycLcLFlexibleInterpVarExt(void *p) {
      return  p ? new(p) ::RooStats::HistFactory::FlexibleInterpVarExt : new ::RooStats::HistFactory::FlexibleInterpVarExt;
   }
   static void *newArray_RooStatscLcLHistFactorycLcLFlexibleInterpVarExt(Long_t nElements, void *p) {
      return p ? new(p) ::RooStats::HistFactory::FlexibleInterpVarExt[nElements] : new ::RooStats::HistFactory::FlexibleInterpVarExt[nElements];
   }
   // Wrapper around operator delete
   static void delete_RooStatscLcLHistFactorycLcLFlexibleInterpVarExt(void *p) {
      delete ((::RooStats::HistFactory::FlexibleInterpVarExt*)p);
   }
   static void deleteArray_RooStatscLcLHistFactorycLcLFlexibleInterpVarExt(void *p) {
      delete [] ((::RooStats::HistFactory::FlexibleInterpVarExt*)p);
   }
   static void destruct_RooStatscLcLHistFactorycLcLFlexibleInterpVarExt(void *p) {
      typedef ::RooStats::HistFactory::FlexibleInterpVarExt current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::RooStats::HistFactory::FlexibleInterpVarExt

//______________________________________________________________________________
void FlexibleInterpVarMkII::Streamer(TBuffer &R__b)
{
   // Stream an object of class FlexibleInterpVarMkII.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FlexibleInterpVarMkII::Class(),this);
   } else {
      R__b.WriteClassBuffer(FlexibleInterpVarMkII::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FlexibleInterpVarMkII(void *p) {
      return  p ? new(p) ::FlexibleInterpVarMkII : new ::FlexibleInterpVarMkII;
   }
   static void *newArray_FlexibleInterpVarMkII(Long_t nElements, void *p) {
      return p ? new(p) ::FlexibleInterpVarMkII[nElements] : new ::FlexibleInterpVarMkII[nElements];
   }
   // Wrapper around operator delete
   static void delete_FlexibleInterpVarMkII(void *p) {
      delete ((::FlexibleInterpVarMkII*)p);
   }
   static void deleteArray_FlexibleInterpVarMkII(void *p) {
      delete [] ((::FlexibleInterpVarMkII*)p);
   }
   static void destruct_FlexibleInterpVarMkII(void *p) {
      typedef ::FlexibleInterpVarMkII current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FlexibleInterpVarMkII

//______________________________________________________________________________
void HggTwoSidedCBPdf::Streamer(TBuffer &R__b)
{
   // Stream an object of class HggTwoSidedCBPdf.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(HggTwoSidedCBPdf::Class(),this);
   } else {
      R__b.WriteClassBuffer(HggTwoSidedCBPdf::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_HggTwoSidedCBPdf(void *p) {
      return  p ? new(p) ::HggTwoSidedCBPdf : new ::HggTwoSidedCBPdf;
   }
   static void *newArray_HggTwoSidedCBPdf(Long_t nElements, void *p) {
      return p ? new(p) ::HggTwoSidedCBPdf[nElements] : new ::HggTwoSidedCBPdf[nElements];
   }
   // Wrapper around operator delete
   static void delete_HggTwoSidedCBPdf(void *p) {
      delete ((::HggTwoSidedCBPdf*)p);
   }
   static void deleteArray_HggTwoSidedCBPdf(void *p) {
      delete [] ((::HggTwoSidedCBPdf*)p);
   }
   static void destruct_HggTwoSidedCBPdf(void *p) {
      typedef ::HggTwoSidedCBPdf current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::HggTwoSidedCBPdf

//______________________________________________________________________________
void HggMG5aMCNLOLineShapePdf::Streamer(TBuffer &R__b)
{
   // Stream an object of class HggMG5aMCNLOLineShapePdf.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(HggMG5aMCNLOLineShapePdf::Class(),this);
   } else {
      R__b.WriteClassBuffer(HggMG5aMCNLOLineShapePdf::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_HggMG5aMCNLOLineShapePdf(void *p) {
      return  p ? new(p) ::HggMG5aMCNLOLineShapePdf : new ::HggMG5aMCNLOLineShapePdf;
   }
   static void *newArray_HggMG5aMCNLOLineShapePdf(Long_t nElements, void *p) {
      return p ? new(p) ::HggMG5aMCNLOLineShapePdf[nElements] : new ::HggMG5aMCNLOLineShapePdf[nElements];
   }
   // Wrapper around operator delete
   static void delete_HggMG5aMCNLOLineShapePdf(void *p) {
      delete ((::HggMG5aMCNLOLineShapePdf*)p);
   }
   static void deleteArray_HggMG5aMCNLOLineShapePdf(void *p) {
      delete [] ((::HggMG5aMCNLOLineShapePdf*)p);
   }
   static void destruct_HggMG5aMCNLOLineShapePdf(void *p) {
      typedef ::HggMG5aMCNLOLineShapePdf current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::HggMG5aMCNLOLineShapePdf

//______________________________________________________________________________
void LEPError::Streamer(TBuffer &R__b)
{
   // Stream an object of class LEPError.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LEPError::Class(),this);
   } else {
      R__b.WriteClassBuffer(LEPError::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LEPError(void *p) {
      delete ((::LEPError*)p);
   }
   static void deleteArray_LEPError(void *p) {
      delete [] ((::LEPError*)p);
   }
   static void destruct_LEPError(void *p) {
      typedef ::LEPError current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::LEPError

//______________________________________________________________________________
void LEPEntry::Streamer(TBuffer &R__b)
{
   // Stream an object of class LEPEntry.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LEPEntry::Class(),this);
   } else {
      R__b.WriteClassBuffer(LEPEntry::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_LEPEntry(void *p) {
      return  p ? new(p) ::LEPEntry : new ::LEPEntry;
   }
   static void *newArray_LEPEntry(Long_t nElements, void *p) {
      return p ? new(p) ::LEPEntry[nElements] : new ::LEPEntry[nElements];
   }
   // Wrapper around operator delete
   static void delete_LEPEntry(void *p) {
      delete ((::LEPEntry*)p);
   }
   static void deleteArray_LEPEntry(void *p) {
      delete [] ((::LEPEntry*)p);
   }
   static void destruct_LEPEntry(void *p) {
      typedef ::LEPEntry current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::LEPEntry

//______________________________________________________________________________
void statistics::Streamer(TBuffer &R__b)
{
   // Stream an object of class statistics.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(statistics::Class(),this);
   } else {
      R__b.WriteClassBuffer(statistics::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_statistics(void *p) {
      return  p ? new(p) ::statistics : new ::statistics;
   }
   static void *newArray_statistics(Long_t nElements, void *p) {
      return p ? new(p) ::statistics[nElements] : new ::statistics[nElements];
   }
   // Wrapper around operator delete
   static void delete_statistics(void *p) {
      delete ((::statistics*)p);
   }
   static void deleteArray_statistics(void *p) {
      delete [] ((::statistics*)p);
   }
   static void destruct_statistics(void *p) {
      typedef ::statistics current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::statistics

namespace ROOT {
   // Wrappers around operator new
   static void *new__List_iteratorlERooAbsDatamUgR(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) ::_List_iterator<RooAbsData*> : new ::_List_iterator<RooAbsData*>;
   }
   static void *newArray__List_iteratorlERooAbsDatamUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) ::_List_iterator<RooAbsData*>[nElements] : new ::_List_iterator<RooAbsData*>[nElements];
   }
   // Wrapper around operator delete
   static void delete__List_iteratorlERooAbsDatamUgR(void *p) {
      delete ((::_List_iterator<RooAbsData*>*)p);
   }
   static void deleteArray__List_iteratorlERooAbsDatamUgR(void *p) {
      delete [] ((::_List_iterator<RooAbsData*>*)p);
   }
   static void destruct__List_iteratorlERooAbsDatamUgR(void *p) {
      typedef ::_List_iterator<RooAbsData*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::_List_iterator<RooAbsData*>

namespace ROOT {
   static TClass *vectorlEintgR_Dictionary();
   static void vectorlEintgR_TClassManip(TClass*);
   static void *new_vectorlEintgR(void *p = 0);
   static void *newArray_vectorlEintgR(Long_t size, void *p);
   static void delete_vectorlEintgR(void *p);
   static void deleteArray_vectorlEintgR(void *p);
   static void destruct_vectorlEintgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<int>*)
   {
      vector<int> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<int>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<int>", -2, "vector", 214,
                  typeid(vector<int>), DefineBehavior(ptr, ptr),
                  &vectorlEintgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<int>) );
      instance.SetNew(&new_vectorlEintgR);
      instance.SetNewArray(&newArray_vectorlEintgR);
      instance.SetDelete(&delete_vectorlEintgR);
      instance.SetDeleteArray(&deleteArray_vectorlEintgR);
      instance.SetDestructor(&destruct_vectorlEintgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<int> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<int>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEintgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<int>*)0x0)->GetClass();
      vectorlEintgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEintgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEintgR(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<int> : new vector<int>;
   }
   static void *newArray_vectorlEintgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<int>[nElements] : new vector<int>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEintgR(void *p) {
      delete ((vector<int>*)p);
   }
   static void deleteArray_vectorlEintgR(void *p) {
      delete [] ((vector<int>*)p);
   }
   static void destruct_vectorlEintgR(void *p) {
      typedef vector<int> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<int>

namespace {
  void TriggerDictionaryInitialization_quickFit_Dict_Impl() {
    static const char* headers[] = {
"inc/ExtendedMinimizer.h",
"inc/ExtendedModel.h",
"inc/FlexibleInterpVarExt.h",
"inc/FlexibleInterpVarMkII.h",
"inc/HggMG5aMCNLOLineShapePdf.h",
"inc/HggTwoSidedCBPdf.h",
"inc/LEPEntry.h",
"inc/RooFormulaVarExt.h",
"inc/statistics.h",
0
    };
    static const char* includePaths[] = {
"/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/x86_64/boost/boost-1.60.0-python2.7-x86_64-slc6-gcc49/boost-1.60.0-python2.7-x86_64-slc6-gcc49/include/",
"/afs/ihep.ac.cn/users/z/zhangkl/cepcFit",
"inc",
"/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/x86_64/root/6.04.16-HiggsComb-x86_64-slc6-gcc49-opt/include",
"/afs/ihep.ac.cn/users/z/zhangkl/cepcFit/",
0
    };
    static const char* fwdDeclCode = 
R"DICTFWDDCLS(
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$inc/ExtendedMinimizer.h")))  ExtendedMinimizer;
class __attribute__((annotate("$clingAutoload$inc/ExtendedModel.h")))  ExtendedModel;
class __attribute__((annotate(R"ATTRDUMP(Real-valued function of other RooAbsArgs calculated by a TFormula expression)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/quickFit_LinkDef.h")))  RooFormulaVarExt;
namespace RooStats{namespace HistFactory{class __attribute__((annotate(R"ATTRDUMP(flexible interpolation)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/quickFit_LinkDef.h")))  FlexibleInterpVarExt;}}
class __attribute__((annotate(R"ATTRDUMP(flexible interpolation)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/quickFit_LinkDef.h")))  FlexibleInterpVarMkII;
class __attribute__((annotate(R"ATTRDUMP(Crystal Ball lineshape PDF)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(Crystal Ball lineshape PDF)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/quickFit_LinkDef.h")))  HggTwoSidedCBPdf;
class __attribute__((annotate(R"ATTRDUMP(Crystal Ball lineshape PDF)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(Crystal Ball lineshape PDF)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/quickFit_LinkDef.h")))  HggMG5aMCNLOLineShapePdf;
class __attribute__((annotate("$clingAutoload$inc/quickFit_LinkDef.h")))  LEPError;
class __attribute__((annotate("$clingAutoload$inc/quickFit_LinkDef.h")))  LEPEntry;
class __attribute__((annotate("$clingAutoload$inc/quickFit_LinkDef.h")))  statistics;
class __attribute__((annotate("$clingAutoload$inc/quickFit_LinkDef.h")))  RooAbsData;
namespace std{template <typename _Tp> struct __attribute__((annotate("$clingAutoload$inc/quickFit_LinkDef.h")))  _List_iterator;
}
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "inc/ExtendedMinimizer.h"
#include "inc/ExtendedModel.h"
#include "inc/FlexibleInterpVarExt.h"
#include "inc/FlexibleInterpVarMkII.h"
#include "inc/HggMG5aMCNLOLineShapePdf.h"
#include "inc/HggTwoSidedCBPdf.h"
#include "inc/LEPEntry.h"
#include "inc/RooFormulaVarExt.h"
#include "inc/statistics.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"ExtendedMinimizer", payloadCode, "@",
"ExtendedModel", payloadCode, "@",
"FlexibleInterpVarExt", payloadCode, "@",
"FlexibleInterpVarMkII", payloadCode, "@",
"HggMG5aMCNLOLineShapePdf", payloadCode, "@",
"HggTwoSidedCBPdf", payloadCode, "@",
"LEPEntry", payloadCode, "@",
"LEPError", payloadCode, "@",
"RooFormulaVarExt", payloadCode, "@",
"RooStats::HistFactory::FlexibleInterpVarExt", payloadCode, "@",
"statistics", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("quickFit_Dict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_quickFit_Dict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_quickFit_Dict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_quickFit_Dict() {
  TriggerDictionaryInitialization_quickFit_Dict_Impl();
}
