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

KSYMTAB_FUNC(reportfs_get_sbi, "", "");

SYMBOL_CRC(reportfs_get_sbi, 0x1350a12d, "");

static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0x24ea3736, "inode_init_owner" },
	{ 0xc60d0620, "__num_online_cpus" },
	{ 0x81288c24, "new_inode" },
	{ 0xf6df7783, "fs_dax_get_by_bdev" },
	{ 0xc4f218f2, "unregister_filesystem" },
	{ 0x89a376a7, "d_make_root" },
	{ 0x81b66aa5, "register_filesystem" },
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0x2d609547, "dax_direct_access" },
	{ 0x40fb8d99, "kill_block_super" },
	{ 0x122c3a7e, "_printk" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0x65929cae, "ns_to_timespec64" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0x2300d7c4, "mount_bdev" },
	{ 0x92b38218, "boot_cpu_data" },
	{ 0xf0dfe76a, "kmalloc_trace" },
	{ 0xc4f0da12, "ktime_get_with_offset" },
	{ 0x5a35e5af, "kmalloc_caches" },
	{ 0xbc314156, "nop_mnt_idmap" },
	{ 0x78d867f, "module_layout" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "4C05698B79A6C53A9D8ACED");
