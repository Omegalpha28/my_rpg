/*
** EPITECH PROJECT, 2024
** moon-engine
** File description:
** maths
*/

#ifndef MATHS_H_
    #define MATHS_H_

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
    #include "moon.h"

///////////////////////////////////////////////////////////////////////////////
/// \brief Clamps a value to a specified range.
///
/// \param value        The value to be clamped
/// \param min          The minimum value in the range
/// \param max          The maximum value in the range
///
/// \return The clamped value.
///
///////////////////////////////////////////////////////////////////////////////
int clamp(int value, int min, int max);

///////////////////////////////////////////////////////////////////////////////
/// \brief Clamps a value to a specified range.
///
/// \param value        The value to be clamped
/// \param min          The minimum value in the range
/// \param max          The maximum value in the range
///
/// \return The clamped value.
///
///////////////////////////////////////////////////////////////////////////////
float clampf(float value, float min, float max);

///////////////////////////////////////////////////////////////////////////////
/// \brief Clamps a value to a specified range.
///
/// \param value        The value to be clamped
/// \param min          The minimum value in the range
/// \param max          The maximum value in the range
///
/// \return The clamped value.
///
///////////////////////////////////////////////////////////////////////////////
double clampd(double value, double min, double max);

///////////////////////////////////////////////////////////////////////////////
/// \brief Linear interpolation between two value
///
/// \param start        The starting value
/// \param end          The ending value
/// \param t            Interpolation value [0, 1] for calculating the value
///
/// \return The linear interpolation based on t for the start and end value.
///
///////////////////////////////////////////////////////////////////////////////
int lerp(int start, int end, float t);

///////////////////////////////////////////////////////////////////////////////
/// \brief Linear interpolation between two value
///
/// \param start        The starting value
/// \param end          The ending value
/// \param t            Interpolation value [0, 1] for calculating the value
///
/// \return The linear interpolation based on t for the start and end value.
///
///////////////////////////////////////////////////////////////////////////////
float lerpf(float start, float end, float t);

///////////////////////////////////////////////////////////////////////////////
/// \brief Linear interpolation between two value
///
/// \param start        The starting value
/// \param end          The ending value
/// \param t            Interpolation value [0, 1] for calculating the value
///
/// \return The linear interpolation based on t for the start and end value.
///
///////////////////////////////////////////////////////////////////////////////
double lerpd(double start, double end, float t);

///////////////////////////////////////////////////////////////////////////////
/// \brief Finds the minimum value among a variable number of integers.
///
/// \param n            The number of integers to compare
/// \param x            The first integer
/// \param ...          Subsequent integers to compare
///
/// \return The minimum value among the provided integers
///
///////////////////////////////////////////////////////////////////////////////
int min(uint n, int x, ...);

///////////////////////////////////////////////////////////////////////////////
/// \brief Finds the minimum value among a variable number of floats.
///
/// \param n            The number of floats to compare
/// \param x            The first float
/// \param ...          Subsequent floats to compare
///
/// \return The minimum value among the provided floats
///
///////////////////////////////////////////////////////////////////////////////
float minf(uint n, float x, ...);

///////////////////////////////////////////////////////////////////////////////
/// \brief Finds the minimum value among a variable number of doubles.
///
/// \param n            The number of doubles to compare
/// \param x            The first double
/// \param ...          Subsequent doubles to compare
///
/// \return The minimum value among the provided doubles
///
///////////////////////////////////////////////////////////////////////////////
double mind(uint n, double x, ...);

///////////////////////////////////////////////////////////////////////////////
/// \brief Finds the maximum value among a variable number of integers.
///
/// \param n            The number of integers to compare
/// \param x            The first integer
/// \param ...          Subsequent integers to compare
///
/// \return The maximum value among the provided integers
///
///////////////////////////////////////////////////////////////////////////////
int max(uint n, int x, ...);

///////////////////////////////////////////////////////////////////////////////
/// \brief Finds the maximum value among a variable number of floats.
///
/// \param n            The number of floats to compare
/// \param x            The first float
/// \param ...          Subsequent floats to compare
///
/// \return The maximum value among the provided floats
///
///////////////////////////////////////////////////////////////////////////////
float maxf(uint n, float x, ...);

///////////////////////////////////////////////////////////////////////////////
/// \brief Finds the maximum value among a variable number of doubles.
///
/// \param n            The number of doubles to compare
/// \param x            The first double
/// \param ...          Subsequent doubles to compare
///
/// \return The maximum value among the provided doubles
///
///////////////////////////////////////////////////////////////////////////////
double maxd(uint n, double x, ...);

///////////////////////////////////////////////////////////////////////////////
/// \brief Calculate distance between two points
///
/// \param pts1         The first point
/// \param pts2         The second point
///
/// \return The distance between the points
///
///////////////////////////////////////////////////////////////////////////////
int distance2i(v2i pts1, v2i pts2);

///////////////////////////////////////////////////////////////////////////////
/// \brief Calculate distance between two points
///
/// \param pts1         The first point
/// \param pts2         The second point
///
/// \return The distance between the points
///
///////////////////////////////////////////////////////////////////////////////
float distance2f(v2f pts1, v2f pts2);

///////////////////////////////////////////////////////////////////////////////
/// \brief Calculate distance between two points
///
/// \param pts1         The first point
/// \param pts2         The second point
///
/// \return The distance between the points
///
///////////////////////////////////////////////////////////////////////////////
int distance2u(v2u pts1, v2u pts2);

///////////////////////////////////////////////////////////////////////////////
/// \brief Calculate distance between two points
///
/// \param pts1         The first point
/// \param pts2         The second point
///
/// \return The distance between the points
///
///////////////////////////////////////////////////////////////////////////////
float distance3f(v3f pts1, v3f pts2);

///////////////////////////////////////////////////////////////////////////////
/// \brief Check for intersection between two circles
///
/// \param c1           The center of the first circle
/// \param r1           The radius of the first circle
/// \param c2           The center of the second circle
/// \param r2           The radius of the second circle
///
/// \return Boolean, true if there's an intersection, false otherwise
///
///////////////////////////////////////////////////////////////////////////////
bool intersect2f(v2f c1, float r1, v2f c2, float r2);

///////////////////////////////////////////////////////////////////////////////
/// \brief Check for intersection between two spheres
///
/// \param c1           The center of the first sphere
/// \param r1           The radius of the first sphere
/// \param c2           The center of the second sphere
/// \param r2           The radius of the second sphere
///
/// \return Boolean, true if there's an intersection, false otherwise
///
///////////////////////////////////////////////////////////////////////////////
bool intersect3f(v3f c1, float r1, v3f c2, float r2);

///////////////////////////////////////////////////////////////////////////////
/// \brief Check for intersection between two circles
///
/// \param c1           The center of the first circle
/// \param r1           The radius of the first circle
/// \param c2           The center of the second circle
/// \param r2           The radius of the second circle
///
/// \return Boolean, true if there's an intersection, false otherwise
///
///////////////////////////////////////////////////////////////////////////////
bool intersect2i(v2i c1, int r1, v2i c2, int r2);

///////////////////////////////////////////////////////////////////////////////
/// \brief Check for intersection between two rectangle
///
/// \param r1           The first rectangle
/// \param r2           The second rectangle
///
/// \return Boolean, true if there's an intersection, false otherwise
///
///////////////////////////////////////////////////////////////////////////////
bool intersectri(recti r1, recti r2);

///////////////////////////////////////////////////////////////////////////////
/// \brief Check for intersection between two rectangle
///
/// \param r1           The first rectangle
/// \param r2           The second rectangle
///
/// \return Boolean, true if there's an intersection, false otherwise
///
///////////////////////////////////////////////////////////////////////////////
bool intersectrf(rectf r1, rectf r2);

#endif /* !MATHS_H_ */
