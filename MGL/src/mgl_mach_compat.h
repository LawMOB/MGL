/*
 * mgl_mach_compat.h
 *
 * Drop-in replacement for <mach/mach_vm.h>, <mach/mach_init.h>, and
 * <mach/vm_map.h> when building for iOS.  Those headers are blocked by
 * the iPhoneOS SDK ("mach_vm.h unsupported"), but the underlying kernel
 * functions (vm_allocate, vm_deallocate, mach_task_self) ARE available
 * in libSystem on iOS — only the headers are withheld.
 *
 * On macOS we simply include the real headers as before.
 */

#ifndef MGL_MACH_COMPAT_H
#define MGL_MACH_COMPAT_H

#include <stdint.h>

#if TARGET_OS_IPHONE || TARGET_OS_SIMULATOR
/* ---- iOS / Simulator: declare only what MGL actually uses ---- */
#include <mach/kern_return.h>   /* kern_return_t, KERN_SUCCESS — public iOS API */
#include <mach/port.h>          /* mach_port_t               — public iOS API   */

typedef uintptr_t   vm_address_t;
typedef uintptr_t   vm_size_t;
typedef mach_port_t vm_map_t;

#ifndef VM_FLAGS_ANYWHERE
#  define VM_FLAGS_ANYWHERE 1
#endif

/* These symbols live in libSystem.dylib on every iOS version. */
extern kern_return_t vm_allocate(vm_map_t   target,
                                 vm_address_t *address,
                                 vm_size_t  size,
                                 int        flags);

extern kern_return_t vm_deallocate(vm_map_t   target,
                                   vm_address_t address,
                                   vm_size_t  size);

extern mach_port_t mach_task_self(void);
extern mach_port_t mach_host_self(void);

#else
/* ---- macOS: use the real SDK headers ---- */
#include <mach/mach_vm.h>
#include <mach/mach_init.h>
#include <mach/vm_map.h>
#endif /* TARGET_OS_IPHONE */

#endif /* MGL_MACH_COMPAT_H */
