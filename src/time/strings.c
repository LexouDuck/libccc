
#include "libft_time.h"



extern char const* gmt = "GMT";
extern char const* utc = "UTC";



extern char const* const g_time_NAST[5] =
{
	"EST",
	"CST",
	"MST",
	"PST",
	"\0\0\0"
};

extern char const* const g_time_NADT[5] =
{
	"EDT",
	"CDT",
	"MDT",
	"PDT",
	"\0\0\0"
};



extern char const* const AM_PM[2] =
{
	"AM",
	"PM",
};



char const* const	g_time_day[ENUMLENGTH_WEEKDAY] =
{
	"sunday",
	"monday",
	"tuesday",
	"wednesday",
	"thursday",
	"friday",
	"saturday",
};

char const* const	g_time_day_abbreviated[ENUMLENGTH_WEEKDAY] =
{
	"sun",
	"mon",
	"tue",
	"wed",
	"thu",
	"fri",
	"sat",
};


char const* const	g_time_month[ENUMLENGTH_MONTH] =
{
	"january",
	"february",
	"march",
	"april",
	"may",
	"june",
	"july",
	"august",
	"september",
	"october",
	"november",
	"december",
};

char const* const	g_time_month_abbreviated[ENUMLENGTH_MONTH] =
{
	"jan",
	"feb",
	"mar",
	"apr",
	"may",
	"jun",
	"jul",
	"aug",
	"sep",
	"oct",
	"nov",
	"dec",
};
