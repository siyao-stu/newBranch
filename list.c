
#include <stdio.h>

typedef struct list_head list_head_t;
struct list_head{
    struct list_head *prev;
    struct list_head *next;
};

typedef struct single_list_head{
    struct list_head *next;
} single_list_head_t;

int list_init(list_head_t *head)
{
    head->prev = head;
    head->next = head;
}

int list_add(list_head_t *head, list_head_t *new)
{
    new->prev = head;
    new->next = head->next;

    new->prev->next = new;
    new->next->prev = new;
}

int list_del(list_head_t *old)
{
    old->prev->next = old->next;
    old->next->prev = old->prev;

    old->next = NULL;
    old->prev = NULL;
}

#define list_entry(ptr, type, member)                    \
    ((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))

int single_list_init(single_list_head_t *head)
{
    head->next = head;
}

int single_list_add(single_list_head_t *head, single_list_head_t *new)
{

}

int main()
{
    list_head_t head;
    struct test_data{
        int obj1;
        int obj2;
        unsigned long unl;
        list_head_t node;
    };
    struct test_data data = {0};
    struct test_data *data_find;

    data.obj1 = 25;
    list_init(&head);
    list_add(&head, &data.node);

    unsigned long aa = (unsigned long)&((typeof(data) *)0)->node;
    unsigned long bb = (unsigned long)&((typeof(data) *)0)->obj1;
    unsigned long cc = (unsigned long)&((typeof(data) *)0)->obj2;
    unsigned long dd = (unsigned long)&((typeof(data) *)0)->unl;
    size_t s = sizeof(data.node);
    size_t ul = sizeof(unsigned long);
    size_t uint_len = sizeof(unsigned int);
    size_t char_len = sizeof(unsigned char);
    size_t data_len = sizeof(data);

    unsigned long tmp = (unsigned long)(&((typeof(data) *)0)->node);

    char *node_addr = (char *)(&data.node);

    data_find = (typeof(data) *)((char *)(&data.node)-(unsigned long)(&((typeof(data) *)0)->node));
    data_find = list_entry(&data.node, typeof(data), node);

    printf("%d\n", data_find->obj1);
}