#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include "hello1.h"

MODULE_AUTHOR("Andrii Chaika");
MODULE_DESCRIPTION("Hello2 ak lab5");
MODULE_LICENSE("Dual BSD/GPL");

static uint print_count = 1;
module_param(print_count, uint, 0644);
MODULE_PARM_DESC(print_count, "Number of times to call print_hello");

static int __init hello2_init(void) {
    unsigned int i;

    pr_info("Hello2 module loaded with print_count=%u\n", print_count);

    if (print_count == 0 || (print_count >= 5 && print_count <= 10)) {
        pr_warn("Warning: print_count=%u\n", print_count);
    }

    if (print_count > 10) {
        pr_err("Error: print_count=%u exceeds the limit\n", print_count);
        return -EINVAL;
    }

    for (i = 0; i < print_count; i++) {
        print_hello();
    }

    return 0;
}

static void __exit hello2_exit(void) {
    pr_info("Hello2 module unloaded\n");
}

module_init(hello2_init);
module_exit(hello2_exit);