#include "date.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdnoreturn.h>

#include "data.h"
#include "definitions.h"
#include "memory.h"
#include "string.h"

const Year MIN_YEAR = 1000;
const Year MAX_YEAR = 2999;

static const U32 YEAR_MULTIPLIER = 10000;
static const U32 MONTH_MULTIPLIER = 100;
static const U32 DAY_MULTIPLIER = 1;
static const U32 days_in_months[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
static const char *day_of_week_names_full[7] = {"Monday", "Tuesday",  "Wednesday", "Thursday",
                                                "Friday", "Saturday", "Sunday"};
static const char *day_of_week_names_short[7] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};
static const char *month_names_full[12] = {"January", "February", "March",     "April",   "May",      "June",
                                           "July",    "August",   "September", "October", "November", "December"};
static const char *month_names_short[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                                            "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

// Takes same args as printf
#define date_abort(...) statement(_date_abort(__FILE__, __LINE__, __func__, __VA_ARGS__))

static noreturn void _date_abort(const char *file, int line, const char *func, ...) {
  va_list args;
  va_start(args, func);

  const char *message = va_arg(args, const char *);

  fprintf(stderr, "\n");
  fprintf(stderr, "> ---| Date error |---\n");
  fprintf(stderr, "> Error in %s->%s (line %d)\n", file, func, line);
  fprintf(stderr, "> ");
  vfprintf(stderr, message, args);
  fprintf(stderr, "\n");
  fprintf(stderr, "Terminating program\n");

  va_end(args);

  exit(EXIT_FAILURE);
}

Date date_init(Day day, Month month, Year year) {
  if (year < MIN_YEAR || MAX_YEAR < year) {
    date_abort("Invalid year %" U32f ", outside range [%" U32f ", %" U32f "]", year, MIN_YEAR, MAX_YEAR);
  }

  if (month < MONTH_JAN || MONTH_DEC < month) {
    date_abort("Invalid month %d, outside range [%d, %d]", (int)month, (int)MONTH_JAN, (int)MONTH_DEC);
  }

  if (day < 1 || month_get_days_in_month(month) < day) {
    date_abort("Invalid day %" U32f ", outside range [%" U32f ", %" U32f "]", day, 1,
               month_get_days_in_month(month));
  }

  if (day == 29 && month == 2 && !year_is_leap_year(year)) {
    date_abort("Feb 29 for non leap year %" U32f, year);
  }

  return day * DAY_MULTIPLIER + month * MONTH_MULTIPLIER + year * YEAR_MULTIPLIER;
}

// Use Mon 01/01/801 as the baseline for calculating days of week
DayOfWeek date_get_day_of_week(Date date) {
  DayOfWeek day_of_week = DAY_MON;

  U32 years = date_get_year(date) - 801;
  day_of_week += years + years / 4 - years / 100 + years / 400;  // Need to use a year with year % 400 == 1 here

  for (Month i_month = MONTH_JAN; i_month < date_get_month(date); ++i_month) {
    day_of_week += days_in_months[i_month - 1] - (i_month == MONTH_FEB && !year_is_leap_year(date_get_year(date)));
  }

  day_of_week += date_get_day(date) - 1;

  return day_of_week % 7;
}

String day_of_week_get_string(DayOfWeek day_of_week, bool shortened) {
  return string_init_cstring(day_of_week_get_cstring(day_of_week, shortened));
}
const char *day_of_week_get_cstring(DayOfWeek day_of_week, bool shortened) {
  const char **lookup_to_use = shortened ? day_of_week_names_short : day_of_week_names_full;

  return lookup_to_use[day_of_week];
}

Day date_get_day(Date date) {
  return (date % MONTH_MULTIPLIER) / DAY_MULTIPLIER;
}

Month date_get_month(Date date) {
  return (date % YEAR_MULTIPLIER) / MONTH_MULTIPLIER;
}

U32 month_get_days_in_month(Month month) {
  return days_in_months[month - 1];
}

String month_get_string(Month month, bool shortened) {
  return string_init_cstring(month_get_cstring(month, shortened));
}

const char *month_get_cstring(Month month, bool shortened) {
  const char **lookup_to_use = shortened ? month_names_short : month_names_full;

  return lookup_to_use[month - 1];
}

Year date_get_year(Date date) {
  return date / YEAR_MULTIPLIER;
}

bool year_is_leap_year(Year year) {
  return ((year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0)));
}

String date_get_string(Arena *arena, Date date, DateFormat date_format, DayOfWeekFormat day_of_week_format) {
  return string_init_cstring(date_get_cstring(arena, date, date_format, day_of_week_format));
}

const char *date_get_cstring(Arena *arena, Date date, DateFormat date_format, DayOfWeekFormat day_of_week_format) {
  Arena sb_arena = arena_init(256);
  LinkNode sb_head;
  linked_list_init(&sb_head);

  if (day_of_week_format != DAY_OF_WEEK_FORMAT_HIDDEN) {
    String day_of_week_string =
        day_of_week_get_string(date_get_day_of_week(date), day_of_week_format == DAY_OF_WEEK_FORMAT_SHORT);
    string_builder_add_string(&sb_arena, &sb_head, day_of_week_string);
    string_builder_add_string(&sb_arena, &sb_head, string_literal(" "));
  }

  String delimeter = (date_format <= DATE_FORMAT_NUMERICAL_FULL) ? string_literal("/") : string_literal(" ");

  String day_string = string_format(&sb_arena, "%02" U32f, date_get_day(date));
  string_builder_add_string(&sb_arena, &sb_head, day_string);
  string_builder_add_string(&sb_arena, &sb_head, delimeter);

  String month_string =
      (date_format <= DATE_FORMAT_NUMERICAL_FULL)
          ? string_format(&sb_arena, "%02d", (int)date_get_month(date))
          : month_get_string(date_get_month(date), date_format == DATE_FORMAT_ALPHABETICAL_SHORT_NO_YEAR ||
                                                       date_format == DATE_FORMAT_ALPHABETICAL_SHORT);
  string_builder_add_string(&sb_arena, &sb_head, month_string);

  if (date_format != DATE_FORMAT_NUMERICAL_NO_YEAR && date_format != DATE_FORMAT_ALPHABETICAL_SHORT_NO_YEAR &&
      date_format != DATE_FORMAT_ALPHABETICAL_FULL_NO_YEAR) {
    string_builder_add_string(&sb_arena, &sb_head, delimeter);
    String year_string = (date_format == DATE_FORMAT_NUMERICAL_SHORT)
                             ? string_format(&sb_arena, "%02" U32f, date_get_year(date) % 100)
                             : string_format(&sb_arena, "%" U32f, date_get_year(date));
    string_builder_add_string(&sb_arena, &sb_head, year_string);
  }

  const char *result = string_builder_get_cstring(arena, &sb_head);

  arena_free(&sb_arena);

  return result;
}
