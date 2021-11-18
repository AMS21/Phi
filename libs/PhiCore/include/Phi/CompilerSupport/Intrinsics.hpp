#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Intrinsics/AddressOf.hpp"
#include "Intrinsics/ArrayExtent.hpp"
#include "Intrinsics/ArrayRank.hpp"
#include "Intrinsics/Fabs.hpp"
#include "Intrinsics/Fabsf.hpp"
#include "Intrinsics/Fabsl.hpp"
#include "Intrinsics/Floor.hpp"
#include "Intrinsics/Floorf.hpp"
#include "Intrinsics/Floorl.hpp"
#include "Intrinsics/HasTrivialDestructor.hpp"
#include "Intrinsics/HasUniqueObjectRepresentations.hpp"
#include "Intrinsics/HasVirtualDestructor.hpp"
#include "Intrinsics/IsAggregate.hpp"
#include "Intrinsics/IsArithmetic.hpp"
#include "Intrinsics/IsArray.hpp"
#include "Intrinsics/IsAssignable.hpp"
#include "Intrinsics/IsBaseOf.hpp"
#include "Intrinsics/IsClass.hpp"
#include "Intrinsics/IsCompound.hpp"
#include "Intrinsics/IsConst.hpp"
#include "Intrinsics/IsConstantEvaluated.hpp"
#include "Intrinsics/IsConstructible.hpp"
#include "Intrinsics/IsConvertible.hpp"
#include "Intrinsics/IsCopyAssignable.hpp"
#include "Intrinsics/IsCopyConstructible.hpp"
#include "Intrinsics/IsDestructible.hpp"
#include "Intrinsics/IsEmpty.hpp"
#include "Intrinsics/IsEnum.hpp"
#include "Intrinsics/IsFinal.hpp"
#include "Intrinsics/IsFloatingPoint.hpp"
#include "Intrinsics/IsFunction.hpp"
#include "Intrinsics/IsFundamental.hpp"
#include "Intrinsics/IsIntegral.hpp"
#include "Intrinsics/IsLValueExpr.hpp"
#include "Intrinsics/IsLValueRefenrece.hpp"
#include "Intrinsics/IsLiteralType.hpp"
#include "Intrinsics/IsMemberFunctionPointer.hpp"
#include "Intrinsics/IsMemberObjectPointer.hpp"
#include "Intrinsics/IsMemberPointer.hpp"
#include "Intrinsics/IsNothrowAssignable.hpp"
#include "Intrinsics/IsNothrowConstructible.hpp"
#include "Intrinsics/IsNothrowCopyAssignable.hpp"
#include "Intrinsics/IsNothrowCopyConstructible.hpp"
#include "Intrinsics/IsNothrowDefaultConstructible.hpp"
#include "Intrinsics/IsNothrowMoveAssignable.hpp"
#include "Intrinsics/IsNothrowMoveConstructible.hpp"
#include "Intrinsics/IsObject.hpp"
#include "Intrinsics/IsPod.hpp"
#include "Intrinsics/IsPointer.hpp"
#include "Intrinsics/IsPolymorphic.hpp"
#include "Intrinsics/IsRValueExpr.hpp"
#include "Intrinsics/IsRValueReference.hpp"
#include "Intrinsics/IsReference.hpp"
#include "Intrinsics/IsSame.hpp"
#include "Intrinsics/IsScalar.hpp"
#include "Intrinsics/IsSigned.hpp"
#include "Intrinsics/IsStandardLayout.hpp"
#include "Intrinsics/IsTrivial.hpp"
#include "Intrinsics/IsTriviallyAssignable.hpp"
#include "Intrinsics/IsTriviallyConstructible.hpp"
#include "Intrinsics/IsTriviallyCopyAssignable.hpp"
#include "Intrinsics/IsTriviallyCopyConstructible.hpp"
#include "Intrinsics/IsTriviallyCopyable.hpp"
#include "Intrinsics/IsTriviallyDefaultConstructible.hpp"
#include "Intrinsics/IsTriviallyDestructible.hpp"
#include "Intrinsics/IsTriviallyMoveAssignable.hpp"
#include "Intrinsics/IsTriviallyMoveConstructible.hpp"
#include "Intrinsics/IsUnion.hpp"
#include "Intrinsics/IsUnsigned.hpp"
#include "Intrinsics/IsVoid.hpp"
#include "Intrinsics/IsVolatile.hpp"
#include "Intrinsics/RemoveCV.hpp"
#include "Intrinsics/RemoveConst.hpp"
#include "Intrinsics/RemoveVolatile.hpp"
#include "Intrinsics/UnderlyingType.hpp"

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_HPP