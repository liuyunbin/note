#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 5

typedef struct {
    int a[BUFFER_SIZE];
    pthread_mutex_t lock;
    int write;
    int read;
    pthread_cond_t notfull;
    pthread_cond_t notempty;
} Node;

void init(Node* node) {
    pthread_mutex_init(&node->lock, NULL);
    pthread_cond_init(&node->notfull, NULL);
    pthread_cond_init(&node->notempty, NULL);
    node->read = node->write = 0;
}

void put(Node* node, int data) {
    pthread_mutex_lock(&node->lock);
    if ((node->write + 1) % BUFFER_SIZE == node->read)
        pthread_cond_wait(&node->notfull, &node->lock);
    node->a[node->write] = data;
    node->write = (node->write + 1) % BUFFER_SIZE;
    pthread_cond_signal(&node->notempty);
    pthread_mutex_unlock(&node->lock);
}

int get(Node* node) {
    int data;
    pthread_mutex_lock(&node->lock);
    if (node->write == node->read)
        pthread_cond_wait(&node->notempty, &node->lock);
    data = node->a[node->read];
    node->read = (node->read + 1) % BUFFER_SIZE;
    pthread_cond_signal(&node->notfull);
    pthread_mutex_unlock(&node->lock);

    return data;
}

void* producer(void* node) {
    int i;

    for (i = 0; i < 20; ++i) {
        printf("%d----->\n", i);
        put(node, i);
    }

    return NULL;
}

void* consumer(void* node) {
    int data;
    Node* b;

    b = (Node*)node;
    while (b->write != b->read) {
        data = get(node);
        printf("---->%d\n", data);
    }

    return NULL;
}

int main(void) {
    Node node;
    pthread_t id1, id2;

    init(&node);

    pthread_create(&id1, NULL, producer, (void*)(&node));
    pthread_create(&id2, NULL, consumer, (void*)(&node));

    pthread_join(id1, NULL);
    pthread_join(id2, NULL);

    return 0;
}
