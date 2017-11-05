#include "grad.h"

set_id init_set(int size)
{
	set_id set = {
		.size = size, 
		.id = malloc(size * sizeof(TIdOil)),
		.d.w = malloc(size * sizeof(TWeight)),
	};
	return set;
}

// repair type
bool copy_set(set_id *set, int *idx)
{
	if (NULL != set->id && NULL != set->d.w) {
		memcpy(set->id, idx, set->size * sizeof(int));
		return true;
	}
	return false;
}

void free_set(set_id *set)
{
	set->size = 0;
	free(set->id);
	free(set->d.w);
	set->id = NULL;
	set->d.w = NULL;
}

int compare(const void *a, const void *b)
{
  return ( *(unsigned int*)a - *(unsigned int*)b );
}

void str2int(int size, char *list[], unsigned int *id)
{
	for (int i = 0; i < size; i++) 
		id[i] = atoi(list[i]);
}

int remove_lake(int size, unsigned int *id)
{
	int len_id = size;
	int max_id = oil_get_count();

	for (int i = len_id - 1; i >= 0 && id[i] >= max_id; i--) {
		len_id--;
	}

	int i = 0;
	while (++i < len_id) {
		if (id[i-1] == id[i]) {
			len_id--;
			memcpy(&id[i], &id[i+1], len_id);
		}
	}

	return len_id;
}

bool corrected(set_id *set, int size, char *list[])
{
	unsigned int id[size];
	str2int(size, list, id);

	qsort(id, size, sizeof(int), compare);

	int len_id = remove_lake(size, id);

	if (len_id > 1) {
		(*set) = init_set(len_id);
		return copy_set(set, id);
	}

	return false;
}

void item_set_optim()
{
	
}

void change_set(set_id set, int index)
{

}

void range_set(set_id *set)
{
	// for (int i = 0; i < set->size; i++) {

	// }
	grad(set);
}

void auto_range(int size, char *list[])
{
	set_id set;
	if (!corrected(&set, size, list))
		return;

	range_set(&set);
	free_set(&set);
}