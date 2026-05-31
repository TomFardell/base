/*------*/
/* Date */
/*---------------------------------------------------------------------------------------------------------------*/
// This module contains logic for dates. Note I am from Europe so I am using DAY-MONTH-YEAR ordering for dates.
//
// A date is just a number of the form YYYYMMDD, i.e. 20040101 represents 01/01/2004. There is also logic to
// calculate the day of the week (i.e. Thursday) for dates. Since dates are just numbers, we can use comparison
// operators on them.
/*---------------------------------------------------------------------------------------------------------------*/
#ifndef DATE_H
#define DATE_H

#include <stdbool.h>

#include "definitions.h"
#include "memory.h"
#include "string.h"

typedef U32 Date;

typedef enum DayOfWeek {
  DAY_MON = 0,
  DAY_TUE = 1,
  DAY_WED = 2,
  DAY_THU = 3,
  DAY_FRI = 4,
  DAY_SAT = 5,
  DAY_SUN = 6,
} DayOfWeek;

typedef U32 Day;

typedef enum Month {
  MONTH_JAN = 1,
  MONTH_FEB = 2,
  MONTH_MAR = 3,
  MONTH_APR = 4,
  MONTH_MAY = 5,
  MONTH_JUN = 6,
  MONTH_JUL = 7,
  MONTH_AUG = 8,
  MONTH_SEP = 9,
  MONTH_OCT = 10,
  MONTH_NOV = 11,
  MONTH_DEC = 12,
} Month;

typedef U32 Year;

typedef enum DateFormat {
  DATE_FORMAT_NUMERICAL_NO_YEAR,           // I.e. 01/01
  DATE_FORMAT_NUMERICAL_SHORT,             // I.e. 01/01/04
  DATE_FORMAT_NUMERICAL_FULL,              // I.e. 01/01/2004
  DATE_FORMAT_ALPHABETICAL_SHORT_NO_YEAR,  // I.e. 01 Jan
  DATE_FORMAT_ALPHABETICAL_FULL_NO_YEAR,   // I.e. 01 January
  DATE_FORMAT_ALPHABETICAL_SHORT,          // I.e. 01 Jan 2004
  DATE_FORMAT_ALPHABETICAL_FULL,           // I.e. 01 January 2004
} DateFormat;

typedef enum DayOfWeekFormat {
  DAY_OF_WEEK_FORMAT_HIDDEN,  // Don't display day of week
  DAY_OF_WEEK_FORMAT_SHORT,   // I.e. Thu
  DAY_OF_WEEK_FORMAT_FULL,    // I.e. Thursday
} DayOfWeekFormat;

const extern Year MIN_YEAR;
const extern Year MAX_YEAR;

// Initialise a date given a day, month and year
Date date_init(Day day, Month month, Year year);

// Given a date, calculate the day of the week
DayOfWeek date_get_day_of_week(Date date);
// Get the short/full lexical representation of a day of the week as a string
String day_of_week_get_string(DayOfWeek day_of_week, bool shortened);
// Get the short/full lexical representation of a day of the week as a cstring
const char *day_of_week_get_cstring(DayOfWeek day_of_week, bool shortened);

// Given a date, get the day
Day date_get_day(Date date);

// Given a date, get the month
Month date_get_month(Date date);
// Get the number of days in a given month. Returns 29 for February
U32 month_get_days_in_month(Month month);
// Get the short/full lexical representation of a month as a string
String month_get_string(Month month, bool shortened);
// Get the short/full lexical representation of a month as a cstring
const char *month_get_cstring(Month month, bool shortened);

// Given a date, get the year
Year date_get_year(Date date);
// Get whether a given year is a leap year
bool year_is_leap_year(Year year);

// Get the string representation of a given date with a specified format
String date_get_string(Arena *arena, Date date, DateFormat date_format, DayOfWeekFormat day_of_week_format);
// Get the cstring representation of a given date with a specified format
const char *date_get_cstring(Arena *arena, Date date, DateFormat date_format, DayOfWeekFormat day_of_week_format);

#endif  // ifndef DATE_H

// vim: filetype=c :
