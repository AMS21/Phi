/*!
 * \file CurrentFunction.hpp
 * \brief Exports an object like macro to get the name of the current function.
**/
#ifndef INCG_PHI_CORE_COMPILER_SUPPORT_CURRENT_FUNCTION_HPP
#define INCG_PHI_CORE_COMPILER_SUPPORT_CURRENT_FUNCTION_HPP

#include "phi/compiler_support/compiler.hpp"

/*!
 * \def PHI_CURRENT_FUNCTION
 * \brief Expands to a C-String literal that represents the current function.
 * \note Uses the 'prettiest' function macro that the compiler being used
 *       provides.
 * \warning Depending on the compiler used, this macro will expand to a
 *          different C-String literal!
 * \warning The result of the macro expansion can not be string concatenated
 *          by the preprocessor with other C-String literals.
**/

#if PHI_COMPILER_IS(MSVC)

#    define PHI_CURRENT_FUNCTION() __FUNCSIG__

#elif PHI_COMPILER_IS(GCC) || PHI_COMPILER_IS(MINGW) || PHI_COMPILER_IS(CLANG)

#    define PHI_CURRENT_FUNCTION() __PRETTY_FUNCTION__

#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) ||                                  \
        (defined(__IBMPHI__) && (__IBMPHI__ >= 500))

#    define PHI_CURRENT_FUNCTION() __FUNCTION__

#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)

#    define PHI_CURRENT_FUNCTION() __FUNC__

#else

#    define PHI_CURRENT_FUNCTION() __func__ /* use __func__ from C99 as fallback */

#endif

#endif // INCG_PHI_CORE_COMPILER_SUPPORT_CURRENT_FUNCTION_HPP
