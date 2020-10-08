/*!
 * \file SourceLine.hpp
 * \brief Exports an object like macro that expands to a C-style string
 *        of the current line number in the source code.
**/
#ifndef INCG_PHI_CONFIG_SOURCE_LINE_HPP
#define INCG_PHI_CONFIG_SOURCE_LINE_HPP

#include "Phi/Config/Stringify.hpp" // PHI_STRINGIFY

/*!
 * \def PHI_SOURCE_LINE
 * \brief The current line in the current source file.
 * \note Note that the line number may have been manipulated using #line.
 *
 * Macro that expands to a C-String literal of the current line in the current
 * source file. Equivalent to the stringification of the standard predefined
 * macro __LINE__
**/
#define PHI_SOURCE_LINE() PHI_STRINGIFY(__LINE__)

#endif // INCG_PHI_CONFIG_SOURCE_LINE_HPP
