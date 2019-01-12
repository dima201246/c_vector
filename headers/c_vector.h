#ifndef C_VECTOR_H
#define C_VECTOR_H

	struct cVector {
		unsigned int size;
		struct cVector *data;
	};

	int vectorInit(struct cVector **c_vector);
	unsigned int vectorAddString(struct cVector **c_vector, char const *string);
	unsigned int vectorAddAnything(struct cVector **c_vector, void const *data, unsigned int data_size);
	unsigned int vectorDeleteElement(struct cVector **c_vector, unsigned int element_number);
	unsigned int vectorCopy(struct cVector const *source_vector, struct cVector **destination_vector);
	unsigned int vectorInsertAnything(struct cVector **c_vector, unsigned int position_number, void const *data, unsigned int data_size);
	unsigned int vectorInsertString(struct cVector **c_vector, unsigned int position_number, char const *string);
	int vectorFree(struct cVector **c_vector);

	unsigned char vectorStringNotIn(char const *string, struct cVector const *c_vector);
	unsigned char vectorAnythingNotIn(void const *data, unsigned int data_size, struct cVector const *c_vector);

	char const *vectorGetString(struct cVector const *c_vector, unsigned int element_number, char const *fail_return);
	unsigned int vectorGetSize(struct cVector const *c_vector);
#endif
