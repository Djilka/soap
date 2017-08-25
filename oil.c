#include <string.h>
#include <stdio.h>

#include "oil.h"

Oil *oil = NULL;
int oil_count = 0;

void print_iol()
{
	int i = 0;
	for (; i + 1 < oil_count; i += 2) {
		printf("%d. %s \t %d. %s \n", i, oil[i].name, 
			i + 1, oil[i + 1].name);
	}
	if (i == oil_count - 1)
		printf("%d. %s\n", i, oil[i].name); 
}

void oil_size(int size)
{
	oil = (Oil*)malloc(size * sizeof(Oil));
	if (oil)
		oil_count = size;
}

int oil_get_count()
{
	return oil_count;
}

bool oil_resize(int size)
{
	void *ptr = NULL;
	if (oil)
		ptr = realloc(oil, size * sizeof(Oil));
	else
		ptr = malloc(size * sizeof(Oil));
	if (ptr) {
		oil = ptr;
		oil_count = size;
		return true;
	}
	return false;
}

bool oil_add(char *name, TInternal internal[])
{
	int len = strlen(name) + 1;
	int index = oil_count;
	if (oil_resize(index+1) && (oil[index].name = malloc(len)) != NULL) {
		// strcpy(oil[index].name, name, len - 1);
		strcpy(oil[index].name, name);
		memcpy(oil[index].internal, internal, sizeof(TInternal)*t_max);
		return true;
	}
	oil_remove(index);
	return false;
}

void oil_remove_item(int index)
{
	if (index < oil_count) {
		if (oil[index].name) {
			free(oil[index].name);
			oil[index].name = NULL;
		}
	}
}

void oil_remove(int index)
{
	if (index < oil_count) {
		oil_remove_item(index);
		if (index != oil_count - 1)
			memcpy(&oil[index], &oil[index+1], oil_count - index - 1);
		oil_resize(oil_count-1);
	}
}

void oil_clear()
{
	for (int i = 0; i < oil_count; i++)
		oil_remove_item(i);

	if (oil && oil_count) {
		free(oil);
		oil = NULL;
		oil_count = 0;
	}
}

bool oil_set(int index, Oil *tmp)
{
	if (oil_count > index) {
		tmp = &oil[index];
		return true;
	}
	return false;

}

void oil_auto_init()
{
	oil_add("Абрикосовых косточек масло", (TInternal[]){ 6, 0, 93, 0, 6, 100 });
	oil_add("Авокадо баттер", (TInternal[]){ 31, 0, 61, 0, 31, 67 });
	oil_add("Авокадо масло", (TInternal[]){ 18, 0, 76, 0, 18, 82 });
	oil_add("Андиробы масло", (TInternal[]){ 36, 0, 60, 0, 36, 68 });
	oil_add("Арахисовое масло", (TInternal[]){ 11, 0, 82, 0, 11, 92 });
	oil_add("Арбузных зерен масло", (TInternal[]){ 21, 0, 79, 0, 21, 119 });
	oil_add("Аргана масло", (TInternal[]){ 15, 1, 81, 1, 14, 95 });
	oil_add("Бабассу масло", (TInternal[]){ 69, 55, 22, 55, 14, 10 });
	oil_add("Баобаба масло", (TInternal[]){ 29, 1, 67, 1, 28, 75 });
	oil_add("Брокколи масло", (TInternal[]){ 3, 0, 35, 0, 3, 96 });
	oil_add("Виноградных косточек масло", (TInternal[]){ 11, 0, 88, 0, 11, 138 });
	oil_add("Вишневых косточек масло", (TInternal[]){ 10, 0, 88, 0, 10, 126 });
	oil_add("Говяжий жир", (TInternal[]){ 58, 8, 40, 8, 50, 45 });
	oil_add("Горчичное масло", (TInternal[]){ 4, 0, 41, 0, 4, 101 });
	oil_add("Гранатовых косточек масло", (TInternal[]){ 6, 0, 92, 0, 6, 22 });
	oil_add("Гусиный жир", (TInternal[]){ 27, 0, 64, 0, 27, 65 });
	oil_add("Жожоба масло", (TInternal[]){ 1, 0, 9, 0, 1, 86 });
	oil_add("Зародышей пшеницы масло", (TInternal[]){ 15, 0, 81, 0, 15, 131 });
	oil_add("Иллип масло", (TInternal[]){ 62, 0, 35, 0, 62, 33 });
	oil_add("Какао баттер", (TInternal[]){ 61, 0, 38, 0, 61, 37 });
	oil_add("Канолы масло", (TInternal[]){ 6, 0, 91, 0, 6, 110 });
	oil_add("Капуасу масло", (TInternal[]){ 42, 0, 44, 0, 42, 38 });
	oil_add("Каранджи масло", (TInternal[]){ 12, 0, 73, 0, 12, 85 });
	oil_add("Касторовое масло", (TInternal[]){ 0, 0, 98, 90, 90, 86 });
	oil_add("Клюквы семян масло", (TInternal[]){ 8, 0, 92, 0, 8, 150 });
	oil_add("Козий жир", (TInternal[]){ 69, 16, 31, 16, 53, 40 });
	oil_add("Кокосовое масло", (TInternal[]){ 79, 67, 10, 67, 12, 10 });
	oil_add("Кокум масло", (TInternal[]){ 60, 0, 37, 0, 60, 35 });
	oil_add("Конопляное масло", (TInternal[]){ 8, 0, 87, 0, 8, 160 });
	oil_add("Костяное масло", (TInternal[]){ 0, 0, 0, 0, 0, 90 });
	oil_add("Кофейных жареных зерен масло", (TInternal[]){ 40, 0, 48, 0, 40, 81 });
	oil_add("Кофейных зеленых зерен масло", (TInternal[]){ 46, 0, 50, 0, 46, 85 });
	oil_add("Кохуновое масло", (TInternal[]){ 75, 64, 21, 64, 11, 30 });
	oil_add("Кроличий жир", (TInternal[]){ 39, 3, 55, 3, 36, 85 });
	oil_add("Кукуй масло", (TInternal[]){ 10, 0, 87, 0, 10, 154 });
	oil_add("Кукурузное масло", (TInternal[]){ 14, 0, 84, 0, 14, 117 });
	oil_add("Кунжутное масло", (TInternal[]){ 14, 0, 83, 0, 14, 112 });
	oil_add("Куриный жир", (TInternal[]){ 33, 1, 59, 1, 32, 69 });
	oil_add("Лавра масло", (TInternal[]){ 40, 24, 56, 24, 16, 75 });
	oil_add("Ланолин", (TInternal[]){ 0, 0, 0, 0, 0, 27 });
	oil_add("Лауриновая кислота", (TInternal[]){ 100, 100, 0, 100, 0, 0 });
	oil_add("Лошадиный жир", (TInternal[]){ 34, 3, 49, 3, 31, 79 });
	oil_add("Льняное масло", (TInternal[]){ 9, 0, 90, 0, 9, 180 });
	oil_add("Люфы семян масло", (TInternal[]){ 27, 0, 77, 0, 27, 108 });
	oil_add("Макадамии баттер", (TInternal[]){ 19, 1, 60, 1, 18, 70 });
	oil_add("Макадамии масло", (TInternal[]){ 12, 0, 61, 0, 12, 75 });
	oil_add("Маковое масло", (TInternal[]){ 14, 0, 88, 0, 14, 135 });
	oil_add("Малиновых семян масло", (TInternal[]){ 2, 0, 97, 0, 2, 192 });
	oil_add("Манго баттер", (TInternal[]){ 52, 0, 46, 0, 52, 45 });
	oil_add("Манго семян масло", (TInternal[]){ 49, 0, 48, 0, 49, 45 });
	oil_add("Маракуйи масло", (TInternal[]){ 13, 0, 86, 0, 13, 136 });
	oil_add("Марулы масло", (TInternal[]){ 18, 0, 79, 0, 18, 73 });
	oil_add("Масло алоэ", (TInternal[]){ 0, 0, 0, 0, 0, 2 });
	oil_add("Масло огуречника", (TInternal[]){ 14, 0, 68, 0, 14, 135 });
	oil_add("Медвежий жир", (TInternal[]){ 12, 2, 79, 2, 10, 92 });
	oil_add("Миндальный баттер", (TInternal[]){ 25, 1, 74, 1, 24, 70 });
	oil_add("Миндаля сладкого масло", (TInternal[]){ 7, 0, 89, 0, 7, 101 });
	oil_add("Миристиновая кислота", (TInternal[]){ 99, 99, 0, 99, 0, 1 });
	oil_add("Мовры масло", (TInternal[]){ 46, 0, 51, 0, 46, 62 });
	oil_add("Молочный жир", (TInternal[]){ 55, 15, 22, 15, 40, 30 });
	oil_add("Моной де Таити масло", (TInternal[]){ 73, 60, 2, 60, 13, 9 });
	oil_add("Моринги масло", (TInternal[]){ 14, 0, 73, 0, 14, 68 });
	oil_add("Мурумуру масло", (TInternal[]){ 82, 73, 18, 73, 9, 10 });
	oil_add("Ним масло", (TInternal[]){ 33, 0, 63, 0, 33, 89 });
	oil_add("Норковый жир", (TInternal[]){ 0, 0, 0, 0, 0, 55 });
	oil_add("Облепиховое масло", (TInternal[]){ 10, 0, 88, 0, 10, 165 });
	oil_add("Овечий жир", (TInternal[]){ 51, 14, 31, 14, 37, 54 });
	oil_add("Овсяное масло", (TInternal[]){ 17, 0, 79, 0, 17, 104 });
	oil_add("Олеиновая кислота", (TInternal[]){ 0, 0, 99, 0, 0, 92 });
	oil_add("Оливковое масло", (TInternal[]){ 17, 0, 82, 0, 17, 85 });
	oil_add("Пальмитиновая кислота", (TInternal[]){ 98, 0, 0, 0, 98, 2 });
	oil_add("Пальмовое красное масло", (TInternal[]){ 50, 1, 49, 1, 49, 53 });
	oil_add("Пальмовое масло", (TInternal[]){ 50, 1, 49, 1, 49, 53 });
	oil_add("Пальмовый стеарин", (TInternal[]){ 67, 2, 33, 2, 65, 48 });
	oil_add("Пальмоядровое масло", (TInternal[]){ 75, 65, 18, 65, 10, 20 });
	oil_add("Папайя масло", (TInternal[]){ 18, 0, 79, 0, 18, 67 });
	oil_add("Периллы масло", (TInternal[]){ 8, 0, 87, 0, 8, 196 });
	oil_add("Персиковое масло", (TInternal[]){ 8, 0, 91, 0, 8, 101 });
	oil_add("Подсолнечное масло", (TInternal[]){ 11, 0, 87, 0, 11, 133 });
	oil_add("Примулы вечерней масло", (TInternal[]){ 7, 0, 91, 0, 7, 160 });
	oil_add("Пчелиный воск", (TInternal[]){ 0, 0, 0, 0, 0, 10 });
	oil_add("Рапсовое масло", (TInternal[]){ 4, 0, 86, 0, 4, 108 });
	oil_add("Расторопши масло", (TInternal[]){ 9, 0, 90, 0, 9, 115 });
	oil_add("Рисовых отрубей масло", (TInternal[]){ 26, 1, 69, 1, 25, 110 });
	oil_add("Сафлоровое масло", (TInternal[]){ 7, 0, 90, 0, 7, 145 });
	oil_add("Свиное сало", (TInternal[]){ 42, 1, 52, 1, 41, 57 });
	oil_add("Сливовых косточек масло", (TInternal[]){ 3, 0, 91, 0, 3, 98 });
	oil_add("Соевое масло", (TInternal[]){ 16, 0, 82, 0, 16, 131 });
	oil_add("Стеариновая кислота", (TInternal[]){ 99, 0, 0, 0, 99, 2 });
	oil_add("Страуса жир", (TInternal[]){ 36, 4, 57, 4, 32, 97 });
	oil_add("Таману масло", (TInternal[]){ 25, 0, 73, 0, 25, 111 });
	oil_add("Топленое масло", (TInternal[]){ 55, 15, 22, 15, 40, 30 });
	oil_add("Тукума масло", (TInternal[]){ 77, 71, 13, 71, 6, 13 });
	oil_add("Тыквенное масло", (TInternal[]){ 19, 0, 83, 0, 19, 128 });
	oil_add("Утиный жир", (TInternal[]){ 36, 1, 58, 1, 35, 72 });
	oil_add("Фисташковое масло", (TInternal[]){ 12, 0, 88, 0, 12, 95 });
	oil_add("Фундука масло", (TInternal[]){ 8, 0, 85, 0, 8, 97 });
	oil_add("Хлопковое масло", (TInternal[]){ 26, 0, 71, 0, 26, 108 });
	oil_add("Черного тмина масло", (TInternal[]){ 16, 0, 83, 0, 16, 133 });
	oil_add("Черной смородины масло", (TInternal[]){ 8, 0, 87, 0, 8, 177 });
	oil_add("Ши масло", (TInternal[]){ 48, 0, 49, 0, 48, 58 });
	oil_add("Ши масло, девственное", (TInternal[]){ 45, 0, 54, 0, 45, 59 });
	oil_add("Шиповника масло", (TInternal[]){ 6, 0, 89, 0, 6, 188 });
	oil_add("Эму жир", (TInternal[]){ 32, 0, 55, 0, 32, 60 });
	oil_add("Янгу масло", (TInternal[]){ 23, 0, 76, 0, 23, 95 });
	oil_add("Ятрофы масло", (TInternal[]){ 16, 0, 78, 0, 16, 102 });
}