/*!
 * \file BeginEndMacro.hpp
 * \brief Exports macros that simplify the definition of convenient to use
 *        function like macros.
**/
#ifndef INCG_PHI_CONFIG_FUNCTION_LIKE_MACRO_HPP
#define INCG_PHI_CONFIG_FUNCTION_LIKE_MACRO_HPP

// clang-format off

/*!
 * \def PHI_BEGIN_MACRO
 * \brief To be used to begin definitions of macros that shall be forced to
 *        require a semicolon when used.
 * \see PHI_END_MACRO
**/
#define PHI_BEGIN_MACRO() do {

/*!
 * \def PHI_END_MACRO
 * \brief To be used to end definitions of macros that shall be forced to
 *        require a semicolon when used.
 * \see PHI_BEGIN_MACRO
**/
#define PHI_END_MACRO() } while ((void) 0, 0) /* avoid warnings */

// clang-format on

/*!
 * \def PHI_EMPTY_MACRO
 * \brief To be used to define a macro which does nothing/is empty and
 *        that shall be force to require a semicolon when used.
 * \see PHI_BEGIN_MACRO, PHI_END_MACRO
**/
#define PHI_EMPTY_MACRO() ((void)0)

#endif // INCG_PHIBASE_FUNCTION_LIKE_MACRO_HPP
