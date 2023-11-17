#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/export-internal.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

#ifdef CONFIG_UNWINDER_ORC
#include <asm/orc_header.h>
ORC_HEADER;
#endif

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif



static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xf5b8afeb, "filp_open" },
	{ 0x24ea3736, "inode_init_owner" },
	{ 0x542e9c8e, "try_module_get" },
	{ 0x88db9f48, "__check_object_size" },
	{ 0x13c49cc2, "_copy_from_user" },
	{ 0xc60d0620, "__num_online_cpus" },
	{ 0x668a93d5, "proc_create" },
	{ 0x81288c24, "new_inode" },
	{ 0x593c53a6, "perf_event_create_kernel_counter" },
	{ 0xf6df7783, "fs_dax_get_by_bdev" },
	{ 0xc4f218f2, "unregister_filesystem" },
	{ 0x1350a12d, "reportfs_get_sbi" },
	{ 0x89a376a7, "d_make_root" },
	{ 0xcf2a6966, "up" },
	{ 0xc1000209, "preempt_schedule_irq" },
	{ 0x37a0cba, "kfree" },
	{ 0x8ff75f5b, "seq_lseek" },
	{ 0xb3f7646e, "kthread_should_stop" },
	{ 0x81b66aa5, "register_filesystem" },
	{ 0xb19a5453, "__per_cpu_offset" },
	{ 0x76ab5773, "perf_event_read_value" },
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0x66b684a1, "wake_up_process" },
	{ 0x2d609547, "dax_direct_access" },
	{ 0x65487097, "__x86_indirect_thunk_rax" },
	{ 0x40fb8d99, "kill_block_super" },
	{ 0x122c3a7e, "_printk" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0xe3f5fdc9, "module_put" },
	{ 0x87a21cb3, "__ubsan_handle_out_of_bounds" },
	{ 0x6626afca, "down" },
	{ 0x1edb69d6, "ktime_get_raw_ts64" },
	{ 0xc917e655, "debug_smp_processor_id" },
	{ 0x53a1e8d9, "_find_next_bit" },
	{ 0x9ed12e20, "kmalloc_large" },
	{ 0x39c142d, "kthread_stop" },
	{ 0xcefb0c9f, "__mutex_init" },
	{ 0x65929cae, "ns_to_timespec64" },
	{ 0x9e683f75, "__cpu_possible_mask" },
	{ 0xfb578fc5, "memset" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0x17de3d5, "nr_cpu_ids" },
	{ 0xcc041cf, "kthread_bind" },
	{ 0xe2d5255a, "strcmp" },
	{ 0x20c1c065, "kthread_create_on_node" },
	{ 0x1a0ffebb, "seq_read" },
	{ 0x30b60453, "perf_event_enable" },
	{ 0x3c3ff9fd, "sprintf" },
	{ 0xa648e561, "__ubsan_handle_shift_out_of_bounds" },
	{ 0x85df9b6c, "strsep" },
	{ 0x2300d7c4, "mount_bdev" },
	{ 0xa570298, "remove_proc_entry" },
	{ 0x60683339, "seq_printf" },
	{ 0x20000329, "simple_strtoul" },
	{ 0x92b38218, "boot_cpu_data" },
	{ 0xef3bbee0, "single_release" },
	{ 0x41ed3709, "get_random_bytes" },
	{ 0x362f9a8, "__x86_indirect_thunk_r12" },
	{ 0xfeb9ec09, "perf_event_disable" },
	{ 0xf0dfe76a, "kmalloc_trace" },
	{ 0x1b0bc9d, "perf_event_release_kernel" },
	{ 0xf5948628, "single_open" },
	{ 0x349cba85, "strchr" },
	{ 0xf9a482f9, "msleep" },
	{ 0xc4f0da12, "ktime_get_with_offset" },
	{ 0xeb233a45, "__kmalloc" },
	{ 0x5a35e5af, "kmalloc_caches" },
	{ 0xbc314156, "nop_mnt_idmap" },
	{ 0x78d867f, "module_layout" },
};

MODULE_INFO(depends, "repfs");


MODULE_INFO(srcversion, "9C7A584FC6FD9085E21134C");
