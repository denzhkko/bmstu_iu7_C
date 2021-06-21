#ifndef __LIST_EXTENSION_H__
#define __LIST_EXTENSION_H__

#include "stddef.h"
#include "list.h"

#define TWO_LIST_FOR_EACH_ENTRY(pos1, pos2, head1, head2, member, type) \
    for (pos1 = LIST_ENTRY((head1)->next, type, member), \
         pos2 = LIST_ENTRY((head2)->next, type, member); \
         &pos1->member != (head1) && \
         &pos2->member != (head2); \
         pos1 = LIST_ENTRY(pos1->member.next, type, member), \
         pos2 = LIST_ENTRY(pos2->member.next, type, member))

size_t list_len(struct list_head *head);

#endif // __LIST_EXTENSION_H__
