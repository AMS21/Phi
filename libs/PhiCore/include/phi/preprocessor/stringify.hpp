/*!
 * \file Stringify.hpp
 * \brief Exports a macro that can be used to turn any sequence of tokens
 *        into a C-string literal at preprocessing time.
**/
#ifndef INCG_PHI_CORE_PREPROCESSOR_STRINGIFY_HPP
#define INCG_PHI_CORE_PREPROCESSOR_STRINGIFY_HPP

/*!
 * \def PHI_DETAIL_STRINGIFY(tokens)
 * \brief Implementation macro for PHI_STRINGIFY
 * \warning Do not use.
 * \see PHI_STRINGIFY
**/
#define PHI_DETAIL_STRINGIFY(tokens) #tokens

/*!
 * \def PHI_STRINGIFY(tokens)
 * \brief Turns a contiguous sequence of tokens passed in into a
 *        C-String literal.
 * \example PHI_STRINGIFY(helloworld) results in:
 *          "helloworld"
**/
#define PHI_STRINGIFY(tokens) PHI_DETAIL_STRINGIFY(tokens)

#endif // INCG_PHI_CORE_PREPROCESSOR_STRINGIFY_HPP
