#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/smp.h>

#define CM_SIZE 64

static char cpuname[CM_SIZE] = "WhiteHat CPU v0.2 @ E5-2650 2.00GHz";

void set_cpu_name(struct cpuinfo_x86 *c) {
	strncpy(c->x86_model_id, cpuname, CM_SIZE-1);
	c->x86_model_id[CM_SIZE-1] = '\0';
}

void set_all_names(void) {
    loff_t i;
    for (i=0; i < nr_cpu_ids; i++) {
	set_cpu_name(&cpu_data(i));
    }
}

static int zmeu_set_name(const char *buffer, struct kernel_param *kp) {
    int len = strlen(strncpy(cpuname,buffer,CM_SIZE-1));
    cpuname[CM_SIZE-1] = '\0';
    set_all_names();
    return len;
}

static int zmeu_get_name(char *buffer, struct kernel_param *kp) {
    return strlen(strcpy(buffer, cpuname));
}

int init_module() {
    printk(KERN_INFO "ZmEu <zmeu@whitehat.ro> @ Loaded.\n");
    set_all_names();
    return 0;
}

void cleanup_module() {
    printk(KERN_INFO "ZmEu <zmeu@whitehat.ro> @ Unloaded.\n");
}

MODULE_AUTHOR("Creator: ZmEu <zmeu@whitehat.ro> of WhiteHat Security (www.whitehat.ro)");
MODULE_DESCRIPTION("this idea originally came from dreams, i dont believe its know until now that evince is also there.");
MODULE_LICENSE("WHITEHAT");

module_param_call(cpuname, zmeu_set_name, zmeu_get_name, NULL, S_IRUSR | S_IWUSR);
__MODULE_PARM_TYPE(cpuname, "string");
MODULE_PARM_DESC(cpuname, "Name of CPU");
