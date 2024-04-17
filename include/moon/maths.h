/*
** EPITECH PROJECT, 2024
** csfml-engine
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
/// \brief Pi constant.
///
///////////////////////////////////////////////////////////////////////////////
    #define M_PI 3.14159265358979323846

///////////////////////////////////////////////////////////////////////////////
/// \brief Transforms radiant into degrees
///
///////////////////////////////////////////////////////////////////////////////
    #define RAD2DEG(rad) ((rad) * (180 / M_PI))

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
int min(uint_t n, int x, ...);

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
float minf(uint_t n, float x, ...);

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
double mind(uint_t n, double x, ...);

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
int max(uint_t n, int x, ...);

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
float maxf(uint_t n, float x, ...);

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
double maxd(uint_t n, double x, ...);

///////////////////////////////////////////////////////////////////////////////
/// \brief Calculate distance between two points
///
/// \param pts1         The first point
/// \param pts2         The second point
///
/// \return The distance between the points
///
///////////////////////////////////////////////////////////////////////////////
int distance2i(v2i_t pts1, v2i_t pts2);

///////////////////////////////////////////////////////////////////////////////
/// \brief Calculate distance between two points
///
/// \param pts1         The first point
/// \param pts2         The second point
///
/// \return The distance between the points
///
///////////////////////////////////////////////////////////////////////////////
float distance2f(v2f_t pts1, v2f_t pts2);

///////////////////////////////////////////////////////////////////////////////
/// \brief Calculate distance between two points
///
/// \param pts1         The first point
/// \param pts2         The second point
///
/// \return The distance between the points
///
///////////////////////////////////////////////////////////////////////////////
int distance2u(v2u_t pts1, v2u_t pts2);

///////////////////////////////////////////////////////////////////////////////
/// \brief Calculate distance between two points
///
/// \param pts1         The first point
/// \param pts2         The second point
///
/// \return The distance between the points
///
///////////////////////////////////////////////////////////////////////////////
float distance3f(v3f_t pts1, v3f_t pts2);

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
bool_t intersect2f(v2f_t c1, float r1, v2f_t c2, float r2);

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
bool_t intersect3f(v3f_t c1, float r1, v3f_t c2, float r2);

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
bool_t intersect2i(v2i_t c1, int r1, v2i_t c2, int r2);

///////////////////////////////////////////////////////////////////////////////
/// \brief Check for intersection between two rectangle
///
/// \param r1           The first rectangle
/// \param r2           The second rectangle
///
/// \return Boolean, true if there's an intersection, false otherwise
///
///////////////////////////////////////////////////////////////////////////////
bool_t intersectri(recti_t r1, recti_t r2);

///////////////////////////////////////////////////////////////////////////////
/// \brief Check for intersection between two rectangle
///
/// \param r1           The first rectangle
/// \param r2           The second rectangle
///
/// \return Boolean, true if there's an intersection, false otherwise
///
///////////////////////////////////////////////////////////////////////////////
bool_t intersectrf(rectf_t r1, rectf_t r2);

///////////////////////////////////////////////////////////////////////////////
/// \brief Compare two vector together
///
/// \param a            First vector
/// \param b            Second vector
///
/// \return True if the vector are equal, false otherwise
///
///////////////////////////////////////////////////////////////////////////////
bool_t equal3f(v3f_t a, v3f_t b);

///////////////////////////////////////////////////////////////////////////////
/// \brief Compare two vector together
///
/// \param a            First vector
/// \param b            Second vector
///
/// \return True if the vector are equal, false otherwise
///
///////////////////////////////////////////////////////////////////////////////
bool_t equal2f(v2f_t a, v2f_t b);

///////////////////////////////////////////////////////////////////////////////
/// \brief Compare two vector together
///
/// \param a            First vector
/// \param b            Second vector
///
/// \return True if the vector are equal, false otherwise
///
///////////////////////////////////////////////////////////////////////////////
bool_t equal2i(v2i_t a, v2i_t b);

///////////////////////////////////////////////////////////////////////////////
/// \brief Compare two vector together
///
/// \param a            First vector
/// \param b            Second vector
///
/// \return True if the vector are equal, false otherwise
///
///////////////////////////////////////////////////////////////////////////////
bool_t equal2u(v2u_t a, v2u_t b);

///////////////////////////////////////////////////////////////////////////////
/// \brief Add two vector together
///
/// \param a            First vector
/// \param b            Second vector
///
/// \return The addition of the two vector
///
///////////////////////////////////////////////////////////////////////////////
v2f_t add2f(v2f_t a, v2f_t b);

///////////////////////////////////////////////////////////////////////////////
/// \brief Add two vector together
///
/// \param a            First vector
/// \param b            Second vector
///
/// \return The addition of the two vector
///
///////////////////////////////////////////////////////////////////////////////
v2i_t add2i(v2i_t a, v2i_t b);

///////////////////////////////////////////////////////////////////////////////
/// \brief Add two vector together
///
/// \param a            First vector
/// \param b            Second vector
///
/// \return The addition of the two vector
///
///////////////////////////////////////////////////////////////////////////////
v2u_t add2u(v2u_t a, v2u_t b);

///////////////////////////////////////////////////////////////////////////////
/// \brief Add two vector together
///
/// \param a            First vector
/// \param b            Second vector
///
/// \return The addition of the two vector
///
///////////////////////////////////////////////////////////////////////////////
v3f_t add3f(v3f_t a, v3f_t b);

///////////////////////////////////////////////////////////////////////////////
/// \brief Subtract two vector together
///
/// \param a            First vector
/// \param b            Second vector
///
/// \return The subtraction of the two vector
///
///////////////////////////////////////////////////////////////////////////////
v2f_t subtract2f(v2f_t a, v2f_t b);

///////////////////////////////////////////////////////////////////////////////
/// \brief Subtract two vector together
///
/// \param a            First vector
/// \param b            Second vector
///
/// \return The subtraction of the two vector
///
///////////////////////////////////////////////////////////////////////////////
v2i_t subtract2i(v2i_t a, v2i_t b);

///////////////////////////////////////////////////////////////////////////////
/// \brief Subtract two vector together
///
/// \param a            First vector
/// \param b            Second vector
///
/// \return The subtraction of the two vector
///
///////////////////////////////////////////////////////////////////////////////
v2u_t subtract2u(v2u_t a, v2u_t b);

///////////////////////////////////////////////////////////////////////////////
/// \brief Subtract two vector together
///
/// \param a            First vector
/// \param b            Second vector
///
/// \return The subtraction of the two vector
///
///////////////////////////////////////////////////////////////////////////////
v3f_t subtract3f(v3f_t a, v3f_t b);

///////////////////////////////////////////////////////////////////////////////
/// \brief Multiply two vector together
///
/// \param a            First vector
/// \param b            Second vector
///
/// \return The multiplication of the two vector
///
///////////////////////////////////////////////////////////////////////////////
v2f_t multiply2f(v2f_t a, v2f_t b);

///////////////////////////////////////////////////////////////////////////////
/// \brief Multiply two vector together
///
/// \param a            First vector
/// \param b            Second vector
///
/// \return The multiplication of the two vector
///
///////////////////////////////////////////////////////////////////////////////
v2i_t multiply2i(v2i_t a, v2i_t b);

///////////////////////////////////////////////////////////////////////////////
/// \brief Multiply two vector together
///
/// \param a            First vector
/// \param b            Second vector
///
/// \return The multiplication of the two vector
///
///////////////////////////////////////////////////////////////////////////////
v2u_t multiply2u(v2u_t a, v2u_t b);

///////////////////////////////////////////////////////////////////////////////
/// \brief Multiply two vector together
///
/// \param a            First vector
/// \param b            Second vector
///
/// \return The multiplication of the two vector
///
///////////////////////////////////////////////////////////////////////////////
v3f_t multiply3f(v3f_t a, v3f_t b);

///////////////////////////////////////////////////////////////////////////////
/// \brief Divide two vector together
///
/// \param a            First vector
/// \param b            Second vector
///
/// \return The division of the two vector
///
///////////////////////////////////////////////////////////////////////////////
v2f_t divide2f(v2f_t a, v2f_t b);

///////////////////////////////////////////////////////////////////////////////
/// \brief Divide two vector together
///
/// \param a            First vector
/// \param b            Second vector
///
/// \return The division of the two vector
///
///////////////////////////////////////////////////////////////////////////////
v2i_t divide2i(v2i_t a, v2i_t b);

///////////////////////////////////////////////////////////////////////////////
/// \brief Divide two vector together
///
/// \param a            First vector
/// \param b            Second vector
///
/// \return The division of the two vector
///
///////////////////////////////////////////////////////////////////////////////
v2u_t divide2u(v2u_t a, v2u_t b);

///////////////////////////////////////////////////////////////////////////////
/// \brief Divide two vector together
///
/// \param a            First vector
/// \param b            Second vector
///
/// \return The division of the two vector
///
///////////////////////////////////////////////////////////////////////////////
v3f_t divide3f(v3f_t a, v3f_t b);

///////////////////////////////////////////////////////////////////////////////
/// \brief Calculates the dot product of two vectors.
///
/// \param a            The first vector.
/// \param b            The second vector.
///
/// \return The dot product of vectors a and b.
///
///////////////////////////////////////////////////////////////////////////////
float dot2f(v2f_t a, v2f_t b);

///////////////////////////////////////////////////////////////////////////////
/// \brief Calculates the dot product of two vectors.
///
/// \param a            The first vector.
/// \param b            The second vector.
///
/// \return The dot product of vectors a and b.
///
///////////////////////////////////////////////////////////////////////////////
uint_t dot2u(v2u_t a, v2u_t b);

///////////////////////////////////////////////////////////////////////////////
/// \brief Calculates the dot product of two vectors.
///
/// \param a            The first vector.
/// \param b            The second vector.
///
/// \return The dot product of vectors a and b.
///
///////////////////////////////////////////////////////////////////////////////
int dot2i(v2i_t a, v2i_t b);

///////////////////////////////////////////////////////////////////////////////
/// \brief Calculates the dot product of two vectors.
///
/// \param a            The first vector.
/// \param b            The second vector.
///
/// \return The dot product of vectors a and b.
///
///////////////////////////////////////////////////////////////////////////////
float dot3f(v3f_t a, v3f_t b);

///////////////////////////////////////////////////////////////////////////////
/// \brief Linearly interpolates between two vectors.
///
/// \param a            The starting vector.
/// \param b            The ending vector.
/// \param t            Interpolation value [0, 1] for calculating the value.
///
/// \return The linear interpolation based on t for vectors a and b.
///
///////////////////////////////////////////////////////////////////////////////
v2f_t lerp2f(v2f_t a, v2f_t b, float t);

///////////////////////////////////////////////////////////////////////////////
/// \brief Linearly interpolates between two vectors.
///
/// \param a            The starting vector.
/// \param b            The ending vector.
/// \param t            Interpolation value [0, 1] for calculating the value.
///
/// \return The linear interpolation based on t for vectors a and b.
///
///////////////////////////////////////////////////////////////////////////////
v2i_t lerp2i(v2i_t a, v2i_t b, float t);

///////////////////////////////////////////////////////////////////////////////
/// \brief Linearly interpolates between two vectors.
///
/// \param a            The starting vector.
/// \param b            The ending vector.
/// \param t            Interpolation value [0, 1] for calculating the value.
///
/// \return The linear interpolation based on t for vectors a and b.
///
///////////////////////////////////////////////////////////////////////////////
v2u_t lerp2u(v2u_t a, v2u_t b, float t);

///////////////////////////////////////////////////////////////////////////////
/// \brief Linearly interpolates between two vectors.
///
/// \param a            The starting vector.
/// \param b            The ending vector.
/// \param t            Interpolation value [0, 1] for calculating the value.
///
/// \return The linear interpolation based on t for vectors a and b.
///
///////////////////////////////////////////////////////////////////////////////
v3f_t lerp3f(v3f_t a, v3f_t b, float t);

///////////////////////////////////////////////////////////////////////////////
/// \brief Calculates the angle (in radians) between two vectors.
///
/// \param a            The first vector.
/// \param b            The second vector.
///
/// \return The angle between vectors a and b in radians.
///
///////////////////////////////////////////////////////////////////////////////
float angle2f(v2f_t a, v2f_t b);

///////////////////////////////////////////////////////////////////////////////
/// \brief Calculates the angle (in radians) between two vectors.
///
/// \param a            The first vector.
/// \param b            The second vector.
///
/// \return The angle between vectors a and b in radians.
///
///////////////////////////////////////////////////////////////////////////////
float angle2i(v2i_t a, v2i_t b);

///////////////////////////////////////////////////////////////////////////////
/// \brief Calculates the angle (in radians) between two vectors.
///
/// \param a            The first vector.
/// \param b            The second vector.
///
/// \return The angle between vectors a and b in radians.
///
///////////////////////////////////////////////////////////////////////////////
float angle2u(v2u_t a, v2u_t b);

///////////////////////////////////////////////////////////////////////////////
/// \brief Calculates the angle (in radians) between two vectors.
///
/// \param a            The first vector.
/// \param b            The second vector.
///
/// \return The angle between vectors a and b in radians.
///
///////////////////////////////////////////////////////////////////////////////
float angle3f(v3f_t a, v3f_t b);

///////////////////////////////////////////////////////////////////////////////
/// \brief Calculates the distance between two points.
///
/// \param a            The first point.
/// \param b            The second point.
///
/// \return The distance between points a and b.
///
///////////////////////////////////////////////////////////////////////////////
float dist2f(v2f_t a, v2f_t b);

///////////////////////////////////////////////////////////////////////////////
/// \brief Calculates the distance between two points.
///
/// \param a            The first point.
/// \param b            The second point.
///
/// \return The distance between points a and b.
///
///////////////////////////////////////////////////////////////////////////////
int dist2i(v2i_t a, v2i_t b);

///////////////////////////////////////////////////////////////////////////////
/// \brief Calculates the distance between two points.
///
/// \param a            The first point.
/// \param b            The second point.
///
/// \return The distance between points a and b.
///
///////////////////////////////////////////////////////////////////////////////
int dist2u(v2u_t a, v2u_t b);

///////////////////////////////////////////////////////////////////////////////
/// \brief Calculates the distance between two points.
///
/// \param a            The first point.
/// \param b            The second point.
///
/// \return The distance between points a and b.
///
///////////////////////////////////////////////////////////////////////////////
float dist3f(v3f_t a, v3f_t b);

///////////////////////////////////////////////////////////////////////////////
/// \brief Calculate the endpoint of a vector from an origin.
///
/// \param origin       The starting point of the vector.
/// \param direction    The direction vector of the vector.
/// \param distance     The distance from the origin to the endpoint.
///
/// \return The endpoint of the vector.
///
///////////////////////////////////////////////////////////////////////////////
v2f_t endpoint2f(v2f_t origin, v2f_t direction, float distance);

///////////////////////////////////////////////////////////////////////////////
/// \brief Calculate the endpoint of a vector from an origin.
///
/// \param origin       The starting point of the vector.
/// \param direction    The direction vector of the vector.
/// \param distance     The distance from the origin to the endpoint.
///
/// \return The endpoint of the vector.
///
///////////////////////////////////////////////////////////////////////////////
v2i_t endpoint2i(v2i_t origin, v2i_t direction, float distance);

///////////////////////////////////////////////////////////////////////////////
/// \brief Calculate the endpoint of a vector from an origin.
///
/// \param origin       The starting point of the vector.
/// \param direction    The direction vector of the vector.
/// \param distance     The distance from the origin to the endpoint.
///
/// \return The endpoint of the vector.
///
///////////////////////////////////////////////////////////////////////////////
v2u_t endpoint2u(v2u_t origin, v2u_t direction, float distance);

///////////////////////////////////////////////////////////////////////////////
/// \brief Calculate the endpoint of a vector from an origin.
///
/// \param origin       The starting point of the vector.
/// \param direction    The direction vector of the vector.
/// \param distance     The distance from the origin to the endpoint.
///
/// \return The endpoint of the vector.
///
///////////////////////////////////////////////////////////////////////////////
v3f_t endpoint3f(v3f_t origin, v3f_t direction, float distance);

///////////////////////////////////////////////////////////////////////////////
/// \brief Normalize the value of a vector
///
/// \param vec          The vector to be normalized
///
/// \return The normalized vector
///
///////////////////////////////////////////////////////////////////////////////
v2f_t normalize2f(v2f_t vec);

///////////////////////////////////////////////////////////////////////////////
/// \brief Normalize the value of a vector
///
/// \param vec          The vector to be normalized
///
/// \return The normalized vector
///
///////////////////////////////////////////////////////////////////////////////
v2i_t normalize2i(v2i_t vec);

///////////////////////////////////////////////////////////////////////////////
/// \brief Normalize the value of a vector
///
/// \param vec          The vector to be normalized
///
/// \return The normalized vector
///
///////////////////////////////////////////////////////////////////////////////
v2u_t normalize2u(v2u_t vec);

///////////////////////////////////////////////////////////////////////////////
/// \brief Normalize the value of a vector
///
/// \param vec          The vector to be normalized
///
/// \return The normalized vector
///
///////////////////////////////////////////////////////////////////////////////
v3f_t normalize3f(v3f_t vec);


///////////////////////////////////////////////////////////////////////////////
/// \brief Moves a vector towards a target vector by a specified maximum
/// distance.
///
/// \param current          The current vector to be moved.
/// \param target           The target vector towards which the current vector
///                         is moved.
/// \param maxDistanceDelta The maximum distance change allowed for the
///                         movement.
///
/// \return The moved vector, which may be equal to the target vector or a
///          vector that has been moved towards the target vector based on
///         maxDistanceDelta.
///
///////////////////////////////////////////////////////////////////////////////
v2f_t movetowards2f(v2f_t current, v2f_t target, float maxDistanceDelta);

///////////////////////////////////////////////////////////////////////////////
/// \brief Moves a vector towards a target vector by a specified maximum
/// distance.
///
/// \param current          The current vector to be moved.
/// \param target           The target vector towards which the current vector
///                         is moved.
/// \param maxDistanceDelta The maximum distance change allowed for the
///                         movement.
///
/// \return The moved vector, which may be equal to the target vector or a
///          vector that has been moved towards the target vector based on
///         maxDistanceDelta.
///
///////////////////////////////////////////////////////////////////////////////
v2u_t movetowards2u(v2u_t current, v2u_t target, float maxDistanceDelta);

///////////////////////////////////////////////////////////////////////////////
/// \brief Moves a vector towards a target vector by a specified maximum
/// distance.
///
/// \param current          The current vector to be moved.
/// \param target           The target vector towards which the current vector
///                         is moved.
/// \param maxDistanceDelta The maximum distance change allowed for the
///                         movement.
///
/// \return The moved vector, which may be equal to the target vector or a
///          vector that has been moved towards the target vector based on
///         maxDistanceDelta.
///
///////////////////////////////////////////////////////////////////////////////
v2i_t movetowards2i(v2i_t current, v2i_t target, float maxDistanceDelta);

#endif /* !MATHS_H_ */
