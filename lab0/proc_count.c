#include <linux/module.h>
#include <linux/printk.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/sched.h>

static struct proc_dir_entry *de;

static int show(struct seq_file *s, void *v)
{
	int i = 0;
	struct task_struct *task_list;

	for_each_process(task_list) i++;
	seq_printf(s, "%d\n", i);
	return 0;
}

static int __init proc_count_init(void)
{
	de = proc_create_single("count", 0444, NULL, &show);
	pr_info("proc_count: init\n");
	return 0;
}

static void __exit proc_count_exit(void)
{
	proc_remove(de);
	// remove_proc_entry("count", NULL);
	pr_info("proc_count: exit\n");
}

module_init(proc_count_init);
module_exit(proc_count_exit);

MODULE_AUTHOR("Andrew Bai");
MODULE_DESCRIPTION("Count the number of processes in /proc/count");
MODULE_LICENSE("GPL");
