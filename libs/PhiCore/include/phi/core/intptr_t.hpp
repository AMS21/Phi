#ifndef INCG_PHI_CORE_INTPTR_T_HPP
#define INCG_PHI_CORE_INTPTR_T_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/generated/compiler_support/type_system.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

// [u]intptr_t
#if PHI_TYPE_SYSTEM_SIZEOF_VOIDPTR() == PHI_TYPE_SYSTEM_SIZEOF_CHAR()
using intptr_t  = signed char;
using uintptr_t = unsigned char;
#elif PHI_TYPE_SYSTEM_SIZEOF_VOIDPTR() == PHI_TYPE_SYSTEM_SIZEOF_SHORT()
using intptr_t  = signed short;
using uintptr_t = unsigned short;
#elif PHI_TYPE_SYSTEM_SIZEOF_VOIDPTR() == PHI_TYPE_SYSTEM_SIZEOF_INT()
using intptr_t  = signed int;
using uintptr_t = unsigned int;
#elif PHI_TYPE_SYSTEM_SIZEOF_VOIDPTR() == PHI_TYPE_SYSTEM_SIZEOF_LONG()
using intptr_t  = signed long;
using uintptr_t = unsigned long;
#elif PHI_TYPE_SYSTEM_SIZEOF_VOIDPTR() == PHI_TYPE_SYSTEM_SIZEOF_LONG_LONG()
using intptr_t  = signed long long;
using uintptr_t = unsigned long long;
#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_INTPTR_T_HPP
