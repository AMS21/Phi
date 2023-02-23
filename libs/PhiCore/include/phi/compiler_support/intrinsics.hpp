#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "intrinsics/abort.hpp"
#include "intrinsics/address_of.hpp"
#include "intrinsics/array_extent.hpp"
#include "intrinsics/array_rank.hpp"
#include "intrinsics/dynamic_object_size.hpp"
#include "intrinsics/fabs.hpp"
#include "intrinsics/fabsf.hpp"
#include "intrinsics/fabsl.hpp"
#include "intrinsics/floor.hpp"
#include "intrinsics/floorf.hpp"
#include "intrinsics/floorl.hpp"
#include "intrinsics/has_trivial_destructor.hpp"
#include "intrinsics/has_unique_object_representations.hpp"
#include "intrinsics/has_virtual_destructor.hpp"
#include "intrinsics/is_aggregate.hpp"
#include "intrinsics/is_arithmetic.hpp"
#include "intrinsics/is_array.hpp"
#include "intrinsics/is_assignable.hpp"
#include "intrinsics/is_base_of.hpp"
#include "intrinsics/is_bounded_array.hpp"
#include "intrinsics/is_class.hpp"
#include "intrinsics/is_compound.hpp"
#include "intrinsics/is_const.hpp"
#include "intrinsics/is_constant_evaluated.hpp"
#include "intrinsics/is_constructible.hpp"
#include "intrinsics/is_convertible.hpp"
#include "intrinsics/is_copy_assignable.hpp"
#include "intrinsics/is_copy_constructible.hpp"
#include "intrinsics/is_corresponding_member.hpp"
#include "intrinsics/is_destructible.hpp"
#include "intrinsics/is_empty.hpp"
#include "intrinsics/is_enum.hpp"
#include "intrinsics/is_final.hpp"
#include "intrinsics/is_floating_point.hpp"
#include "intrinsics/is_function.hpp"
#include "intrinsics/is_fundamental.hpp"
#include "intrinsics/is_infinity.hpp"
#include "intrinsics/is_integral.hpp"
#include "intrinsics/is_layout_compatible.hpp"
#include "intrinsics/is_literal_type.hpp"
#include "intrinsics/is_lvalue_expr.hpp"
#include "intrinsics/is_lvalue_reference.hpp"
#include "intrinsics/is_member_function_pointer.hpp"
#include "intrinsics/is_member_object_pointer.hpp"
#include "intrinsics/is_member_pointer.hpp"
#include "intrinsics/is_nothrow_assignable.hpp"
#include "intrinsics/is_nothrow_constructible.hpp"
#include "intrinsics/is_nothrow_copy_assignable.hpp"
#include "intrinsics/is_nothrow_copy_constructible.hpp"
#include "intrinsics/is_nothrow_default_constructible.hpp"
#include "intrinsics/is_nothrow_move_assignable.hpp"
#include "intrinsics/is_nothrow_move_constructible.hpp"
#include "intrinsics/is_object.hpp"
#include "intrinsics/is_pod.hpp"
#include "intrinsics/is_pointer.hpp"
#include "intrinsics/is_pointer_interconvertible_base_of.hpp"
#include "intrinsics/is_pointer_interconvertible_with_class.hpp"
#include "intrinsics/is_polymorphic.hpp"
#include "intrinsics/is_reference.hpp"
#include "intrinsics/is_rvalue_expr.hpp"
#include "intrinsics/is_rvalue_reference.hpp"
#include "intrinsics/is_same.hpp"
#include "intrinsics/is_scalar.hpp"
#include "intrinsics/is_signed.hpp"
#include "intrinsics/is_standard_layout.hpp"
#include "intrinsics/is_trivial.hpp"
#include "intrinsics/is_trivially_assignable.hpp"
#include "intrinsics/is_trivially_constructible.hpp"
#include "intrinsics/is_trivially_copy_assignable.hpp"
#include "intrinsics/is_trivially_copy_constructible.hpp"
#include "intrinsics/is_trivially_copyable.hpp"
#include "intrinsics/is_trivially_default_constructible.hpp"
#include "intrinsics/is_trivially_destructible.hpp"
#include "intrinsics/is_trivially_move_assignable.hpp"
#include "intrinsics/is_trivially_move_constructible.hpp"
#include "intrinsics/is_union.hpp"
#include "intrinsics/is_unsigned.hpp"
#include "intrinsics/is_void.hpp"
#include "intrinsics/is_volatile.hpp"
#include "intrinsics/object_size.hpp"
#include "intrinsics/offsetof.hpp"
#include "intrinsics/remove_const.hpp"
#include "intrinsics/remove_cv.hpp"
#include "intrinsics/remove_volatile.hpp"
#include "intrinsics/trap.hpp"
#include "intrinsics/underlying_type.hpp"

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_HPP
