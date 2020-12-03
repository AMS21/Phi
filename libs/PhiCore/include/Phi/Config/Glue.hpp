/*!
 * \file Glue.hpp
 * \brief Exports a macro that can be used to glue two sequences of tokens
 *        together in order to form a single sequence of tokens at
 *        preprocessing time.
**/
#ifndef INCG_PHI_CONFIG_GLUE_HPP
#define INCG_PHI_CONFIG_GLUE_HPP

/*!
 * \def DETAIL_PHI_GLUE(a, b)
 * \brief Implementation macro for PHI_GLUE
 * \warning Do not use.
 * \see PHI_GLUE
**/
#define DETAIL_PHI_GLUE(a, b) a##b

/*!
 * \def PHI_GLUE(a, b)
 * \brief Token pastes two contiguous sequences of tokens together as one.
 * \example PHI_GLUE(hello, world) results in:
 *          helloworld
**/
#define PHI_GLUE(a, b) DETAIL_PHI_GLUE(a, b)

/*!
 * \def PHI_GLUE3(a, b, c)
 * \brief Token pastes three contiguous sequences of tokens together as one.
**/
#define PHI_GLUE3(a, b, c) PHI_GLUE(PHI_GLUE(a, b), c)

/*!
 * \def PHI_GLUE4(a, b, c, d)
 * \brief Token pastes four contiguous sequences of tokens together as one.
**/
#define PHI_GLUE4(a, b, c, d) PHI_GLUE(PHI_GLUE3(a, b, c), d)

/*!
 * \def PHI_GLUE5(a, b, c, d, e)
 * \brief Token pastes five contiguous sequences of tokens together as one.
**/
#define PHI_GLUE5(a, b, c, d, e) PHI_GLUE(PHI_GLUE4(a, b, c, d), e)

/*!
 * \def PHI_GLUE6(a, b, c, d, e, f)
 * \brief Token pastes six contiguous sequences of tokens together as one.
**/
#define PHI_GLUE6(a, b, c, d, e, f) PHI_GLUE(PHI_GLUE5(a, b, c, d, e), f)

/*!
 * \def PHI_GLUE7(a, b, c, d, e, f, g)
 * \brief Token pastes seven contiguous sequences of tokens together as one.
**/
#define PHI_GLUE7(a, b, c, d, e, f, g) PHI_GLUE(PHI_GLUE6(a, b, c, d, e, f), g)

/*!
 * \def PHI_GLUE8(a, b, c, d, e, f, g, h)
 * \brief Token pastes eight contiguous sequences of tokens together as one.
**/
#define PHI_GLUE8(a, b, c, d, e, f, g, h) PHI_GLUE(PHI_GLUE7(a, b, c, d, e, f, g), h)

/*!
 * \def PHI_GLUE9(a, b, c, d, e, f, g, h, i)
 * \brief Token pastes nine contiguous sequences of tokens together as one.
**/
#define PHI_GLUE9(a, b, c, d, e, f, g, h, i) PHI_GLUE(PHI_GLUE8(a, b, c, d, e, f, g, h), i)

#endif // INCG_PHI_CONFIG_GLUE_HPP
