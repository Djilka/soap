#include <stdbool.h>
#include <stdlib.h>

enum Type_Internal {
	t_min = -1,
	t_hardness = 0,
	t_cleanability,
	t_easing,
	t_foam_vesicular,
	t_foam_cream,
	t_iodine_number,
	t_max,
};

typedef unsigned char TInternal;

typedef struct Oil {
	char *name;
	TInternal internal[t_max];
} Oil;

void print_iol();
void oil_size(int size);
int  oil_get_count();
bool oil_resize(int size);
bool oil_add(char *name, TInternal internal[]);
void oil_remove_item(int index);
void oil_remove(int index);
void oil_clear();
bool oil_set(int index, Oil *tmp);
void oil_auto_init();

// ===========================================
typedef struct Interval {
	unsigned char min;
	unsigned char max;
} Interval;

typedef struct Normal_Oil
{
	Interval internal[t_max];
	unsigned char balance;
	unsigned char delta;
} Normal_Oil;
 
extern int oil_count;
extern Oil *oil;

static const Normal_Oil normal_oil = {
	{{35, 45},
	{15, 20},
	{50, 70},
	{15, 30},
	{15, 35},
	{0,  60}},
	160, 20
};