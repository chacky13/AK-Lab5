#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/ktime.h>
#include "hello1.h"

MODULE_AUTHOR("Andrii Chaika");
MODULE_DESCRIPTION("Hello1 ak lab5");
MODULE_LICENSE("Dual BSD/GPL");

struct event_item {
    struct list_head list;
    ktime_t start_time;
    ktime_t end_time;
};

static LIST_HEAD(event_list);

void print_hello(void) {
    struct event_item *item;
    item = kmalloc(sizeof(*item), GFP_KERNEL);
    if (!item) {
        pr_err("Failed to allocate memory for event_item\n");
        return;
    }

    item->start_time = ktime_get();
    pr_info("Hello, world!\n");
    item->end_time = ktime_get();
    list_add_tail(&item->list, &event_list);
}
EXPORT_SYMBOL(print_hello);

static void print_event_times(void) {
    struct event_item *item, *tmp;
    list_for_each_entry_safe(item, tmp, &event_list, list) {
        pr_info("Start: %llu ns, End: %llu ns, Duration: %llu ns\n",
                ktime_to_ns(item->start_time),
                ktime_to_ns(item->end_time),
                ktime_to_ns(ktime_sub(item->end_time, item->start_time)));
        list_del(&item->list);
        kfree(item);
    }
}

static int __init hello1_init(void) {
    pr_info("Hello1 module loaded\n");
    return 0;
}

static void __exit hello1_exit(void) {
    print_event_times();
    pr_info("Hello1 module unloaded\n");
}

module_init(hello1_init);
module_exit(hello1_exit);