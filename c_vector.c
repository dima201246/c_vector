#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "headers/c_vector.h"

#define CHAR_DATA_SIZE	1024

char char_data[CHAR_DATA_SIZE] = {};

int vectorInit(struct cVector **c_vector) {
	if (*c_vector != NULL)
	{
		perror("cVector: Please clean vector!");
		return -1;
	}

	*c_vector = NULL;
	*c_vector = (struct cVector *)calloc(1, sizeof(struct cVector));
	(*c_vector)->data = NULL;
	(*c_vector)->size = 0;

	return 0;
}

unsigned int vectorAddString(struct cVector **c_vector, char const *string) {
	return vectorAddAnything(&(*c_vector), string, strlen(string) + 1);
}

unsigned int vectorAddAnything(struct cVector **c_vector, void const *data, unsigned int data_size) {
	unsigned int size = 0;
	struct cVector *c_vector_data = NULL;
	uint8_t *data_point = (uint8_t *)data;
	uint8_t *storage_point = NULL;

	if (!(*c_vector))
	{
		perror("cVector: c_vector == nil!");
		return -1;
	}

	size = (*c_vector)->size + 1;
	c_vector_data = (*c_vector)->data;
	c_vector_data = (struct cVector *)realloc(c_vector_data, size * sizeof(struct cVector));

	if (!c_vector_data)
	{
		return 0;
	}
	else
	{
		c_vector_data[size - 1].data = calloc(data_size, sizeof(uint8_t));
		c_vector_data[size - 1].size = data_size;
		storage_point = (uint8_t *)c_vector_data[size - 1].data;

		for (unsigned int i = 0; i < data_size; i++)
		{
			*storage_point = *data_point++;
			storage_point++;
		}

		(*c_vector)->data = c_vector_data;
		(*c_vector)->size = size;

		return size;
	}

	return 0;
}

unsigned int vectorAddAnythingPosition(struct cVector **c_vector, unsigned int position_number, void const *data, unsigned int data_size) {
	struct cVector *c_vector_data = NULL;
	uint8_t *data_point = (uint8_t *)data;
	uint8_t *storage_point = NULL;

	c_vector_data = &(*c_vector)->data[position_number];

	c_vector_data->data = NULL;
	c_vector_data->data = calloc(data_size, sizeof(uint8_t));
	c_vector_data->size = data_size;
	storage_point = (uint8_t *)c_vector_data->data;

	for (unsigned int i = 0; i < data_size; i++)
	{
		*storage_point = *data_point++;
		storage_point++;
	}

	return vectorGetSize(*c_vector);
}

char const *vectorGetString(struct cVector const *c_vector, unsigned int element_number, char const *fail_return) {
	if (!c_vector)
	{
		perror("cVector: c_vector == nil!");
		return fail_return;
	}

	if (!c_vector->data)
	{
		perror("cVector: c_vector empty!");
		return fail_return;
	}

	if (element_number > (c_vector->size - 1))
	{
		perror("cVector: element number out of size c_vector!");
		return fail_return;
	}

	snprintf(char_data, c_vector->data[element_number].size, "%s", (char *)c_vector->data[element_number].data);
	return (char const *)char_data;
}

unsigned int vectorGetSize(struct cVector const *c_vector) {
	if (!c_vector)
	{
		perror("cVector: c_vector == nil!");
		return 0;
	}

	return c_vector->size;
}

unsigned int vectorDeleteElement(struct cVector **c_vector, unsigned int element_number) {
	void *temp = NULL;

	if (!(*c_vector))
	{
		perror("cVector: c_vector == nil!");
		return 0;
	}

	if (!(*c_vector)->data)
	{
		perror("cVector: c_vector empty!");
		return 0;
	}

	if (element_number > ((*c_vector)->size - 1))
	{
		perror("cVector: element number out of size c_vector!");
		return (*c_vector)->size;
	}

	temp = (*c_vector)->data[element_number].data;
	(*c_vector)->size -= 1;
	
	for (unsigned int i = element_number; i < (*c_vector)->size; i++)
	{
		(*c_vector)->data[i].data = (*c_vector)->data[i + 1].data;
		(*c_vector)->data[i].size = (*c_vector)->data[i + 1].size;
	}
	
	free(temp);
	return (*c_vector)->size;
}

// Копирование элементов из одного вектора в другой
unsigned int vectorCopy(struct cVector const *source_vector, struct cVector **destination_vector) {
	for (unsigned int i = 0; i < source_vector->size; i++)
	{
		vectorAddAnything(&(*destination_vector), source_vector->data[i].data, source_vector->data[i].size);
	}

	return (*destination_vector)->size;
}

// Вставка элемента в вектор с позицией
unsigned int vectorInsertAnything(struct cVector **c_vector, unsigned int position_number, void const *data, unsigned int data_size) {
	if (!(*c_vector))
	{
		perror("cVector: c_vector == nil!");
		return 0;
	}

	if (!(*c_vector)->data)
	{
		return vectorAddAnything(&(*c_vector), data, data_size);
	}

	if (position_number > ((*c_vector)->size - 1))
	{
		perror("cVector: element number out of size c_vector!");
		return 0;
	}

	// Выделение памяти под элемент
	(*c_vector)->size = (*c_vector)->size + 1;
	(*c_vector)->data = (struct cVector *)realloc((*c_vector)->data, (*c_vector)->size * sizeof(struct cVector));

	// Сдвиг элементов вправо
	for (unsigned int i = ((*c_vector)->size - 1); i > position_number; i--)
	{
		(*c_vector)->data[i].data = (*c_vector)->data[i - 1].data;
		(*c_vector)->data[i].size = (*c_vector)->data[i - 1].size;
	}

	// Добавление нового элемента
	vectorAddAnythingPosition(&(*c_vector), position_number, data, data_size);

	return (*c_vector)->size;
}

unsigned int vectorInsertString(struct cVector **c_vector, unsigned int position_number, char const *string) {
	return vectorInsertAnything(&(*c_vector), position_number, string, strlen(string) + 1);
}

// Освобождение памяти
int vectorFree(struct cVector **c_vector) {
	if (!(*c_vector))
	{
		perror("cVector: c_vector == nil!");
		return -1;
	}

	for (unsigned int i = 0; i < (*c_vector)->size; i++)
	{
		free((*c_vector)->data[i].data);
	}
	
	free((*c_vector)->data);
	free(*c_vector);
	return 0;
}

unsigned char vectorStringNotIn(char const *string, struct cVector const *c_vector) {
	return vectorAnythingNotIn(string, strlen(string) + 1, c_vector);
}

unsigned char vectorAnythingNotIn(void const *data, unsigned int data_size, struct cVector const *c_vector) {
	uint8_t *data_point_0 = NULL;
	uint8_t *data_point_1 = NULL;
	unsigned char found_didentical = 0;

	for (unsigned int i = 0; i < vectorGetSize(c_vector); i++)
	{
		if (data_size == c_vector->data[i].size)
		{
			data_point_0 = (uint8_t *)data;
			data_point_1 = (uint8_t *)c_vector->data[i].data;
			found_didentical = 1;

			for (unsigned int j = 0; j < data_size; j++)
			{
				if (*data_point_0 != *data_point_1)
				{
					found_didentical = 0;

					break;
				}

				data_point_0++;
				data_point_1++;
			}

			if (found_didentical)
			{
				return 0;
			}
		}
	}

	return 1;
}
