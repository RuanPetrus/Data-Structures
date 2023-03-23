#include "stdio.h"
#include "stdlib.h"
#include "assert.h"


typedef struct
{
	size_t capacity;
	size_t front;
	size_t back;
	int *elements;
} Queue;

Queue queue_init(size_t capacity)
{
	if (capacity == 0)
		capacity = 1;

	int *data = (int *) malloc(capacity * sizeof(int));
	return (Queue) {
		.capacity = capacity,
		.front = 0,
		.back = 0,
		.elements = data,
	};
}

void queue_push(Queue *queue, int n)
{
	// Checking if is queue should grow
	if (queue->front >= queue->capacity) {
		int used_size = queue->front - queue->back;
		// Normalize
		if (used_size < queue->capacity/2) {
			for(size_t i = queue->back; i < queue->front; i++) {
				queue->elements[i - queue->back] = queue->elements[i];
			}
			queue->front = queue->front - queue->back;
			queue->back = 0;
		} 
		// Realloc Bigger
		else {
			size_t capacity = queue->capacity * 2;
			int *new_data = malloc(capacity * sizeof(int));
			for (size_t i = queue->back; i < queue->front; i++) {
				new_data[i - queue->back] = queue->elements[i];
			}
			free(queue->elements);

			queue->capacity = capacity;
			queue->front = queue->front - queue->back;
			queue->back = 0;
			queue->elements = new_data;
		}
	}
	queue->elements[queue->front++] = n;
}

int queue_peek(const Queue *queue)
{
	assert((int) queue->front - queue->back > 0);
	return queue->elements[queue->back];
}

int queue_pop(Queue *queue)
{
	assert((int32_t) (queue->front - queue->back) > 0);
	// Cheking if the queue should shrink
	if ((queue->front - queue->back) < queue->capacity/4) {
		size_t capacity = queue->capacity/2;
		int *new_data = malloc(capacity * sizeof(int));

		for (size_t i = queue->back; i < queue->front; i++) {
			new_data[i - queue->back] = queue->elements[i];
		}
		free(queue->elements);
		queue->capacity = capacity;
		queue->front = queue->front - queue->back;
		queue->back = 0;
		queue->elements = new_data;

	}

	return queue->elements[queue->back++];
}

size_t queue_size(const Queue *queue)
{
	assert((int) queue->front - queue->back >= 0);
	return queue->front - queue->back;
}


#define N 100000000
int main()
{
	Queue queue = queue_init(0);
	for (int i = 0; i < N; i++){
		queue_push(&queue, i);
	}

	assert(0 == queue_peek(&queue));

	for (int i = 0; i < N; i++){
		int n = queue_pop(&queue);
		assert(i == n);
	}

	assert(0 == queue_size(&queue));
	printf("Queue capacity: %zu\n", queue.capacity);
	free(queue.elements);

	return 0;
}
