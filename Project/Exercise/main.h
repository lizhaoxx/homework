#ifndef __USE_MAIN__
#define __USE_MAIN__
#include <stdbool.h>
// #define CFG_QUEUE_MACRO(__TYPE)                                             \
//     INIT_QUEUE(__TYPE);                                                     \
//     DEQUEUE_TYPE(__TYPE);                                                   \
//     ENQUEUE_TYPE(__TYPE);                                                   \
//     IS_TYPE_QUEUE_EMPTY(__TYPE);
//     
// #define INIT_QUEUE(__TYPE)              INIT_##__TYPE##_QUEUE
// #define DEQUEUE_TYPE(__TYPE)            DEQUEUE_##__TYPE
// #define ENQUEUE_TYPE(__TYPE)            ENQUEUE_##__TYPE
// #define IS_TYPE_QUEUE_EMPTY(__TYPE)     IS_##__TYPE_QUEUE_EMPTY




#define INIT_TYPE_QUEUE(__QUEUE, __BUFFER, __SIZE)                           \
            queue_init((__QUEUE), (__BUFFER), (__SIZE))

#define DEQUEUE_TYPE(__QUEUE, __OBJ)                                        \
            dequeue((__QUEUE),(__OBJ))

#define ENQUEUE_TYPE(__QUEUE, __OBJ)                                        \
            enqueue((__QUEUE), (__OBJ))

#define IS_TYPE_QUEUE_EMPTY(__QUEUE)                                    \
            is_type_queue_empty((__QUEUE))

#define DEFINE_QUEUE_EXTERN(__TYPE)                                         \
typedef struct {                                                            \
    __TYPE *pchBuffer;                                                      \
    uint16_t hwSize;                                                        \
    uint16_t hwHead;                                                        \
    uint16_t hwTail;                                                        \
    uint16_t hwLength;                                                      \
}__TYPE##_queue_t;                                                          \
extern bool queue_init(                                                     \
    __TYPE##_queue_t *ptQueue, __TYPE *pchBuffer, uint16_t hwSize);         \
extern bool enqueue(__TYPE##_queue_t *ptQueue, __TYPE tObj);                \
extern bool dequeue(__TYPE##_queue_t *ptQueue, __TYPE *ptObj);              \
extern bool is_type_queue_empty(__TYPE##_queue_t *ptQueue);

#define DEFINE_QUEUE_ENTITY(__TYPE)                                         \
bool queue_init(                                                            \
    __TYPE##_queue_t *ptQueue, __TYPE *pchBuffer, uint16_t hwSize)          \
{                                                                           \
    if (NULL == ptQueue || NULL == pchBuffer || 0 == hwSize) {              \
        return false;                                                       \
    }                                                                       \
                                                                            \
    ptQueue->pchBuffer = pchBuffer;                                         \
    ptQueue->hwSize = hwSize;                                               \
    ptQueue->hwHead = 0;                                                    \
    ptQueue->hwTail = 0;                                                    \
    ptQueue->hwLength = 0;                                                  \
                                                                            \
    return true;                                                            \
}                                                                           \
                                                                            \
bool enqueue(__TYPE##_queue_t *ptQueue, __TYPE tObj)                        \
{                                                                           \
    bool bRes = false;                                                      \
                                                                            \
    if (NULL == ptQueue) {                                                  \
        return false;                                                       \
    }                                                                       \
                                                                            \
    if ((ptQueue->hwHead == ptQueue->hwTail) && (0 != ptQueue->hwLength)) { \
        return false;                                                       \
    }                                                                       \
                                                                            \
    ptQueue->pchBuffer[ptQueue->hwTail++] = tObj;                           \
    if (ptQueue->hwTail >= ptQueue->hwSize) {                               \
        ptQueue->hwTail = 0;                                                \
    }                                                                       \
    ptQueue->hwLength++;                                                    \
    bRes = true;                                                            \
                                                                            \
    return bRes;                                                            \
}                                                                           \
                                                                            \
bool dequeue(__TYPE##_queue_t *ptQueue, __TYPE *ptObj)                      \
{                                                                           \
    bool bRes = false;                                                      \
                                                                            \
    if ((NULL == ptQueue)||(NULL == ptObj)) {                               \
        return false;                                                       \
    }                                                                       \
                                                                            \
    if ((ptQueue->hwHead == ptQueue->hwTail) && (!ptQueue->hwLength)) {     \
        return false;                                                       \
    }                                                                       \
    *ptObj = ptQueue->pchBuffer[ptQueue->hwHead];                           \
    ptQueue->hwHead++;                                                      \
    if (ptQueue->hwHead >= ptQueue->hwSize) {                               \
        ptQueue->hwHead = 0;                                                \
    }                                                                       \
    ptQueue->hwLength--;                                                    \
    bRes = true;                                                            \
                                                                            \
    return bRes;                                                            \
}                                                                           \
                                                                            \
bool is_type_queue_empty(__TYPE##_queue_t *ptQueue)                         \
{                                                                           \
    if (NULL == ptQueue) {                                                  \
        return false;                                                       \
    }                                                                       \
                                                                            \
    if ((ptQueue->hwHead == ptQueue->hwTail) && (!ptQueue->hwLength)) {     \
        return true;                                                        \
    }                                                                       \
                                                                            \
    return false;                                                           \
}
#endif
