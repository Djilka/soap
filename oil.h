#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef unsigned int TIdOil;
typedef unsigned char TInternal;

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
	float min;
	float max;
} Interval;

extern int oil_count;
extern Oil *oil;

static
Interval internal[t_max] = {
	{35.0, 45.0},
	{15.0, 20.0},
	{50.0, 70.0},
	{15.0, 30.0},
	{15.0, 35.0},
	{0.0,  60.0}};