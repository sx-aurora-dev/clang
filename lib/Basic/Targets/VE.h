//===--- VE.h - Declare VE target feature support ---------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file declares VE TargetInfo objects.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_LIB_BASIC_TARGETS_VE_H
#define LLVM_CLANG_LIB_BASIC_TARGETS_VE_H

#include "clang/Basic/TargetInfo.h"
#include "clang/Basic/TargetOptions.h"
#include "llvm/ADT/Triple.h"
#include "llvm/Support/Compiler.h"

namespace clang {
namespace targets {

class LLVM_LIBRARY_VISIBILITY VETargetInfo : public TargetInfo {
  static const Builtin::Info BuiltinInfo[];

public:
  VETargetInfo(const llvm::Triple &Triple, const TargetOptions &)
      : TargetInfo(Triple) {
    NoAsmVariants = true;
    LongDoubleWidth = 128;
    LongDoubleAlign = 128;
    LongDoubleFormat = &llvm::APFloat::IEEEquad();
    DoubleAlign = LongLongAlign = 64;
    SuitableAlign = 64;
    LongWidth = LongAlign = PointerWidth = PointerAlign = 64;
    SizeType = UnsignedLong;
    PtrDiffType = SignedLong;
    IntPtrType = SignedLong;
    IntMaxType = SignedLong;
    Int64Type = SignedLong;
    RegParmMax = 8;
    MaxAtomicPromoteWidth = MaxAtomicInlineWidth = 64;

    WCharType = UnsignedInt;
    WIntType = UnsignedInt;
    UseZeroLengthBitfieldAlignment = true;
    resetDataLayout("e-m:e-i64:64-n32:64-S64-v64:64:64-v128:64:64-v256:64:64-v512:64:64-v1024:64:64-v2014:64:64-v4096:64:64-v8192:64:64-v16384:64:64");
  }

  void getTargetDefines(const LangOptions &Opts,
                        MacroBuilder &Builder) const override;

  bool hasSjLjLowering() const override { return true; }

  ArrayRef<Builtin::Info> getTargetBuiltins() const override;

  BuiltinVaListKind getBuiltinVaListKind() const override {
    return TargetInfo::VoidPtrBuiltinVaList;
  }

  CallingConvCheckResult checkCallingConvention(CallingConv CC) const override {
    switch (CC) {
    default:
      return CCCR_Warning;
    case CC_C:
    case CC_X86RegCall:
      return CCCR_OK;
    }
  }

  const char *getClobbers() const override { return ""; }

  ArrayRef<const char *> getGCCRegNames() const override {
    static const char *const GCCRegNames[] = {
      // Regular registers
        "sx0",  "sx1",  "sx2",  "sx3",  "sx4",  "sx5",  "sx6",  "sx7",
        "sx8",  "sx9", "sx10", "sx11", "sx12", "sx13", "sx14", "sx15",
       "sx16", "sx17", "sx18", "sx19", "sx20", "sx21", "sx22", "sx23",
       "sx24", "sx25", "sx26", "sx27", "sx28", "sx29", "sx30", "sx31",
       "sx32", "sx33", "sx34", "sx35", "sx36", "sx37", "sx38", "sx39",
       "sx40", "sx41", "sx42", "sx43", "sx44", "sx45", "sx46", "sx47",
       "sx48", "sx49", "sx50", "sx51", "sx52", "sx53", "sx54", "sx55",
       "sx56", "sx57", "sx58", "sx59", "sx60", "sx61", "sx62", "sx63",
      // Vector registers
        "v0",  "v1",  "v2",  "v3",  "v4",  "v5",  "v6",  "v7",
        "v8",  "v9", "v10", "v11", "v12", "v13", "v14", "v15",
       "v16", "v17", "v18", "v19", "v20", "v21", "v22", "v23",
       "v24", "v25", "v26", "v27", "v28", "v29", "v30", "v31",
       "v32", "v33", "v34", "v35", "v36", "v37", "v38", "v39",
       "v40", "v41", "v42", "v43", "v44", "v45", "v46", "v47",
       "v48", "v49", "v50", "v51", "v52", "v53", "v54", "v55",
       "v56", "v57", "v58", "v59", "v60", "v61", "v62", "v63",
      // Special registers
        "vl",  "vixr",  "ucc", "psw", "sar", "pmmr",
        "pmcr0", "pmcr1", "pmcr2", "pmcr3",
        "pmc0", "pmc1", "pmc2", "pmc3", "pmc4", "pmc5", "pmc6", "pmc7",
        "pmc8", "pmc9", "pmc10", "pmc11", "pmc12", "pmc13", "pmc14",
    };
    return llvm::makeArrayRef(GCCRegNames);
  }

  ArrayRef<TargetInfo::GCCRegAlias> getGCCRegAliases() const override {
    static const TargetInfo::GCCRegAlias GCCRegAliases[] = {
       {{"s0"},  "sx0"},  {{"s1"},  "sx1"},
       {{"s2"},  "sx2"},  {{"s3"},  "sx3"},
       {{"s4"},  "sx4"},  {{"s5"},  "sx5"},
       {{"s6"},  "sx6"},  {{"s7"},  "sx7"},
       {{"s8", "sl"},  "sx8"},     {{"s9", "fp"},  "sx9"},
      {{"s10", "lr"}, "sx10"},    {{"s11", "sp"}, "sx11"},
      {{"s12", "outer"}, "sx12"}, {{"s13"}, "sx13"},
      {{"s14", "tp"}, "sx14"},    {{"s15", "got"}, "sx15"},
      {{"s16", "plt"}, "sx16"},   {{"s17", "info"}, "sx17"},
      {{"s18"}, "sx18"}, {{"s19"}, "sx19"},
      {{"s20"}, "sx20"}, {{"s21"}, "sx21"},
      {{"s22"}, "sx22"}, {{"s23"}, "sx23"},
      {{"s24"}, "sx24"}, {{"s25"}, "sx25"},
      {{"s26"}, "sx26"}, {{"s27"}, "sx27"},
      {{"s28"}, "sx28"}, {{"s29"}, "sx29"},
      {{"s30"}, "sx30"}, {{"s31"}, "sx31"},
      {{"s32"}, "sx32"}, {{"s33"}, "sx33"},
      {{"s34"}, "sx34"}, {{"s35"}, "sx35"},
      {{"s36"}, "sx36"}, {{"s37"}, "sx37"},
      {{"s38"}, "sx38"}, {{"s39"}, "sx39"},
      {{"s40"}, "sx40"}, {{"s41"}, "sx41"},
      {{"s42"}, "sx42"}, {{"s43"}, "sx43"},
      {{"s44"}, "sx44"}, {{"s45"}, "sx45"},
      {{"s46"}, "sx46"}, {{"s47"}, "sx47"},
      {{"s48"}, "sx48"}, {{"s49"}, "sx49"},
      {{"s50"}, "sx50"}, {{"s51"}, "sx51"},
      {{"s52"}, "sx52"}, {{"s53"}, "sx53"},
      {{"s54"}, "sx54"}, {{"s55"}, "sx55"},
      {{"s56"}, "sx56"}, {{"s57"}, "sx57"},
      {{"s58"}, "sx58"}, {{"s59"}, "sx59"},
      {{"s60"}, "sx60"}, {{"s61"}, "sx61"},
      {{"s62"}, "sx62"}, {{"s63"}, "sx63"},
      {{"vix"}, "vixr"}, {{"usrcc"}, "ucc"},
    };
    return llvm::makeArrayRef(GCCRegAliases);
  }

  bool validateAsmConstraint(const char *&Name,
                             TargetInfo::ConstraintInfo &Info) const override {
    return false;
  }

  int getEHDataRegisterNumber(unsigned RegNo) const override {
    // S0 = ExceptionPointerRegister, S1 = ExceptionSelectorRegister
    return (RegNo < 2) ? RegNo : -1;
  }

  bool allowsLargerPreferedTypeAlignment() const override { return false; }
};
} // namespace targets
} // namespace clang
#endif // LLVM_CLANG_LIB_BASIC_TARGETS_VE_H
