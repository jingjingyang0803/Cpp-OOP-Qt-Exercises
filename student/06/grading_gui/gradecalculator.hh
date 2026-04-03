#ifndef GRADECALCULATOR_HH
#define GRADECALCULATOR_HH

#include <string>

using namespace std;

// The constant values below are valid at the beginning of the course.
// At the end of the course, if you use this program to calculate your total
// grade, check the values and update them identical with those in Plussa,
// if needed.

const unsigned int MAX_P_POINTS_PER_PROJECT = 50;
const unsigned int MAX_P_POINTS = 2 * MAX_P_POINTS_PER_PROJECT;
const unsigned int MAX_N_POINTS = 500;
const unsigned int MAX_B_POINTS = 10;

// Prints the values of the constants used in calculations to a string and
// returns the string.
string print_constants();

// Calculates score from weekly exercises.
// Assumes that the given parameter is the sum of N and B points.
unsigned int score_from_weekly_exercises(unsigned int n);

// Calculates score from projects.
unsigned int score_from_projects(unsigned int p1, unsigned int p2);

// Calculates the total grade.
// Assumes that the first parameter is the sum of N and B points.
unsigned int calculate_total_grade(unsigned int n,  // Points from weekly submissions
                                   unsigned int p1, // Points from project 1
                                   unsigned int p2, // Points from project 2
                                   unsigned int e); // Exam grade

#endif // GRADECALCULATOR_HH
