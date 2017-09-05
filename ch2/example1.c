#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/slab.h>


typedef struct birthday {
    int day;
    int month;
    int year;
    struct list_head list;
} birthday;


static LIST_HEAD(birthday_list);


int example1_init(void) {
    int i;
    static birthday *person;

    for(i=1; i<=5; ++i) {
        person = kmalloc(sizeof(*person), GFP_KERNEL);
        person->day = i;
        person->month = 6+i;
        person->year = 2000+i;
        INIT_LIST_HEAD(&person->list);
    }

    printk("List creation finished");
    return 0;
}


void example1_exit(void) {
    struct birthday *person;

    list_for_each_entry(person, &birthday_list, list) {
        printk("%d %d %d\n", person->day, person->month, person->year);
        list_del(&person->list);
        kfree(person);
    }
}


module_init(example1_init);
module_exit(example1_exit);


MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("List Traversal");
MODULE_AUTHOR("sTux");

