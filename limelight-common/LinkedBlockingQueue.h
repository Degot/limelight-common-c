#pragma once

#include "platform.h"
#include "PlatformThreads.h"

#define LBQ_SUCCESS 0
#define LBQ_INTERRUPTED 1
#define LBQ_BOUND_EXCEEDED 2
#define LBQ_NO_MEMORY 3

typedef struct _LINKED_BLOCKING_QUEUE_ENTRY {
	struct _LINKED_BLOCKING_QUEUE_ENTRY *flink;
	struct _LINKED_BLOCKING_QUEUE_ENTRY *blink;
	void* data;
} LINKED_BLOCKING_QUEUE_ENTRY, *PLINKED_BLOCKING_QUEUE_ENTRY;

typedef struct _LINKED_BLOCKING_QUEUE {
	PLT_MUTEX mutex;
	PLT_EVENT containsDataEvent;
	int sizeBound;
	int currentSize;
	PLINKED_BLOCKING_QUEUE_ENTRY head;
	PLINKED_BLOCKING_QUEUE_ENTRY tail;
} LINKED_BLOCKING_QUEUE, *PLINKED_BLOCKING_QUEUE;

int LbqInitializeLinkedBlockingQueue(PLINKED_BLOCKING_QUEUE queueHead, int sizeBound);
int LbqOfferQueueItem(PLINKED_BLOCKING_QUEUE queueHead, void* data);
int LbqWaitForQueueElement(PLINKED_BLOCKING_QUEUE queueHead, void** data);
PLINKED_BLOCKING_QUEUE_ENTRY LbqDestroyLinkedBlockingQueue(PLINKED_BLOCKING_QUEUE queueHead);