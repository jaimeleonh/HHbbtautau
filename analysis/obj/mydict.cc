// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dOdOdIobjdImydict

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
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
#include "../interface/analysisCode.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static TClass *analysisCode_Dictionary();
   static void analysisCode_TClassManip(TClass*);
   static void *new_analysisCode(void *p = 0);
   static void *newArray_analysisCode(Long_t size, void *p);
   static void delete_analysisCode(void *p);
   static void deleteArray_analysisCode(void *p);
   static void destruct_analysisCode(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::analysisCode*)
   {
      ::analysisCode *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::analysisCode));
      static ::ROOT::TGenericClassInfo 
         instance("analysisCode", "analysisCode.h", 40,
                  typeid(::analysisCode), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &analysisCode_Dictionary, isa_proxy, 0,
                  sizeof(::analysisCode) );
      instance.SetNew(&new_analysisCode);
      instance.SetNewArray(&newArray_analysisCode);
      instance.SetDelete(&delete_analysisCode);
      instance.SetDeleteArray(&deleteArray_analysisCode);
      instance.SetDestructor(&destruct_analysisCode);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::analysisCode*)
   {
      return GenerateInitInstanceLocal((::analysisCode*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::analysisCode*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *analysisCode_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::analysisCode*)0x0)->GetClass();
      analysisCode_TClassManip(theClass);
   return theClass;
   }

   static void analysisCode_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_analysisCode(void *p) {
      return  p ? new(p) ::analysisCode : new ::analysisCode;
   }
   static void *newArray_analysisCode(Long_t nElements, void *p) {
      return p ? new(p) ::analysisCode[nElements] : new ::analysisCode[nElements];
   }
   // Wrapper around operator delete
   static void delete_analysisCode(void *p) {
      delete ((::analysisCode*)p);
   }
   static void deleteArray_analysisCode(void *p) {
      delete [] ((::analysisCode*)p);
   }
   static void destruct_analysisCode(void *p) {
      typedef ::analysisCode current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::analysisCode

namespace {
  void TriggerDictionaryInitialization_mydict_Impl() {
    static const char* headers[] = {
"../interface/analysisCode.h",
0
    };
    static const char* includePaths[] = {
"../interface/",
"/cvmfs/cms.cern.ch/slc7_amd64_gcc820/cms/cmssw-patch/CMSSW_10_6_5_patch1/external/slc7_amd64_gcc820/bin/../../../../../../../slc7_amd64_gcc820/lcg/root/6.14.09-pafccj/include",
"/cvmfs/cms.cern.ch/slc7_amd64_gcc820/external/boost/1.67.0-pafccj/include",
"/cvmfs/cms.cern.ch/slc7_amd64_gcc820/lcg/root/6.14.09-pafccj/include",
"/afs/cern.ch/user/j/jleonhol/HHbbtautau3/CMSSW_10_6_5_patch1/src/HHbbtautau/analysis/src/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "mydict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$../interface/analysisCode.h")))  analysisCode;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "mydict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "../interface/analysisCode.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"analysisCode", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("mydict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_mydict_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_mydict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_mydict() {
  TriggerDictionaryInitialization_mydict_Impl();
}
