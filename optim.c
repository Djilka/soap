#include "optim.h"

// step of weight
const int init_step = 1;
int step = 1;

// weight
const int max_weight = 400;
int all_weight = 0;
int *ref_weight = NULL;

// iteration
const unsigned long max_iter = 3;
unsigned long iter = 0;

int ref_item[t_max] = {
	// 40, 17, 60, 23, 25, 60
	40, 17, 60, 23, 25, 50
	// 38, 17, 65, 28, 30, 50
};

// delta
int *ref_delta = NULL;

// ------------------ gradient ------------------
int* init_pointer(int count, int val)
{
	int *p = (int*)malloc(sizeof(int)*count);
	if (p)
		for (int i = 0; i < count; i++)
			p[i] = val;
	return p;
}

bool init_data(Oil_Data *data)
{
	data->weight = init_pointer(data->size, max_weight/2);
	data->delta = init_pointer(t_max, max_weight/2);
	
	ref_weight = init_pointer(data->size, 0);
	ref_delta = init_pointer(t_max, 0);
	
	all_weight = (max_weight/2)*data->size;

	return data->weight && data->delta && ref_weight && ref_delta;
}

// ---------------- default -------------------------
bool check_change(Oil_Data *data)
{
	// check max iteration
	bool fl_iter = (max_iter < iter)? false: true;
	// check change gradient
	bool fl_grad = false;
	for (int i = 0; i < data->size; i++) {
		if (data->weight[i] != ref_weight[i]) {
			fl_grad = true;
			break;
		}
	}
	if (!fl_grad) {
		step++;
		if (step == max_weight) {
			step = init_step;
			iter++;
		}
	} else {
		memcpy(ref_weight, data->weight, data->size*sizeof(int));
		iter = 0;
	}
	return fl_iter || fl_grad ;
}

bool gradient_item(Oil_Data *data, int step, int index)
{
	int new_weight = data->weight[index] + step;
	if (new_weight < 0 ||
		new_weight > max_weight)
		return false;

	double last_delta = 0, new_delta = 0; 
	int item = 0;

	for (int i = 0; i < t_max; i++) {
		item = 0;
		for (int j = 0; j < data->size; j++) {
			item += data->weight[j]*data->oil[j].internal[i];
		}
		last_delta += abs(ref_item[i] - item/all_weight);
		item += step*data->oil[index].internal[i];
		new_delta += abs(ref_item[i] - item/(all_weight + step));
	}
	
	return new_delta < last_delta;
}

// ---------------- delta -------------------------
bool check_change_delta(Oil_Data *data)
{
	// check max iteration
	bool fl_iter = (max_iter < iter)? false: true;
	// check change gradient
	bool fl_grad = false;
	for (int i = 0; i < t_max ; i++) {
		if (data->delta[i] != ref_delta[i]) {
			fl_grad = true;
			break;
		}
	}
	if (!fl_grad) {
		step++;
		if (step == max_weight) {
			step = init_step;
			iter++;
		}
	} else {
		memcpy(ref_delta, data->delta, t_max*sizeof(int));
		iter = 0;
	}
	return fl_iter || fl_grad ;
}

bool gradient_item_delta(Oil_Data *data, int step, int index)
{
	int new_weight = data->weight[index] + step;
	if (new_weight < 0 ||
		new_weight > max_weight)
		return false;
	
	int tmp[t_max];
	int item = 0;

	for (int i = 0; i < t_max; i++) {
		item = 0;
		for (int j = 0; j < data->size; j++) {
			item += data->weight[j]*data->oil[j].internal[i];
		}
		item += step*data->oil[index].internal[i];
		tmp[i] = abs(ref_item[i] - item/(all_weight + step));
		if (data->delta[i] < tmp[i])
			return false;
	}
	
	memcpy(data->delta, tmp, sizeof(int)*t_max);
	return true;
}

void gradient(Oil_Data *data)
{
	enum Direction {
		d_front = 0,
		d_back,
		d_max,
	};
	signed char direction[d_max] = {1, -1};
	bool fl = false;

	// init
	if (!init_data(data))
		goto end;

	// default
	while (check_change(data)) {
		for (int i = 0; i < data->size; i++) {
			for (int i_step = d_front; i_step < d_max; i_step++) {
				fl = false;
				while (gradient_item(data, step*direction[i_step], i)) {
					fl = true;
					data->weight[i] += step*direction[i_step];
					all_weight += step*direction[i_step];
				}
				if (fl)
					break;
			}
		}
	}

	print_recipe(data);
	iter = 0;
	step = init_step;
	printf("new check\n");
	// 26 2 69 72 81 10 100 74
	// 26 2 69 72 81 100 74
	
	// Авокадо масло	55.71 г.	8%
	// Кокосовое масло	109.43 г.	16%
	// Оливковое масло	176.08 г.	26%
	// Пальмовое масло	127.33 г.	19%
	// Пальмоядровое масло	64.16 г.	9%
	// Рапсовое масло	78.59 г.	12%
	// Ши масло	67.65 г.	10%
	// Щелочь NaOH	99.01 г.	
	// Вода	224.05 г.	
	// Итоговый вес мыла:	
	// 1002
	//  г.	


	// delta
	while (check_change_delta(data)) {
		for (int i = 0; i < data->size; i++) {
			for (int i_step = d_front; i_step < d_max; i_step++) {
				fl = false;
				while (gradient_item_delta(data, step*direction[i_step], i)) {
					fl = true;
					data->weight[i] += step*direction[i_step];
					all_weight += step*direction[i_step];
				}
				if (fl)
					break;
			}
		}
	}

	print_recipe(data);

end:
	if (ref_weight)
		free(ref_weight);
	if (ref_delta)
		free(ref_delta);
}

// ------------------ simple ------------------
void alg_item_for(int index, Oil_Data *data)
{
	if (index >= data->size)
		return;
	
	for (int i = 0; i < max_weight; i += step) {

		if (index <= 1)
			printf("index = %d; mass = %d\n", index, i);
		if (index == data->size) {
			if (check_nomal(data))
				print_recipe(data);
		} else
			alg_item_for(index+1, data);
	}
}

void simple_alg(Oil_Data *data)
{
	memset(data->weight, 0, data->size);
	alg_item_for(0, data);
}

void optim(Oil_Data *data)
{
	// simple_alg(data);
	gradient(data);
}