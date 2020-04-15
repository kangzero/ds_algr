#ifndef _DLINK_H_
#define _DLINK_H_

#include <stdint.h>
#include <stddef.h>

typedef struct dNode_t {
    void *val; // data pointer
    struct dNode_t *prev;
    struct dNode_t *next;
} dNode;

dNode* dlink_create_node (void *pval);
uint8_t dlink_init (void);
uint8_t dlink_is_empty (void);
uint32_t dlink_size (void);
void* dlink_get (uint32_t index);
uint8_t dlink_insert_first (void *pv);
uint8_t dlink_append_last (void *pv);
uint8_t dlink_insert (uint32_t index, void *pv);
uint8_t dlink_delete (uint32_t index);
uint8_t dlink_delete_first (void);
uint8_t dlink_delete_last (void);
uint8_t dlink_destroy (void);
dNode* dlink_get_first (void);
dNode* dlink_get_last (void);

#endif
