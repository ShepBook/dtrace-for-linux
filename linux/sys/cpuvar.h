# if !SYS_CPUVAR_H
# define	SYS_CPUVAR_H

#define CPU_CACHE_COHERENCE_SIZE        64

# define	kmutex_t mutex_t

/*
 * The cpu_core structure consists of per-CPU state available in any context.
 * On some architectures, this may mean that the page(s) containing the
 * NCPU-sized array of cpu_core structures must be locked in the TLB -- it
 * is up to the platform to assure that this is performed properly.  Note that
 * the structure is sized to avoid false sharing.
 */
#define CPUC_SIZE               (sizeof (uint16_t) + sizeof (uintptr_t) + \
                                sizeof (kmutex_t))
#define CPUC_PADSIZE            CPU_CACHE_COHERENCE_SIZE - CPUC_SIZE

typedef struct {
        int             cpuid;
        struct cyc_cpu *cpu_cyclic;
        unsigned	cpu_flags;
        unsigned int	cpu_intr_actv;
        uintptr_t       cpu_profile_pc;
        uintptr_t       cpu_profile_upc;
        uintptr_t       cpu_dtrace_caller;      /* DTrace: caller, if any */
        hrtime_t        cpu_dtrace_chillmark;   /* DTrace: chill mark time */
        hrtime_t        cpu_dtrace_chilled;     /* DTrace: total chill time */
} cpu_t;

typedef struct cpu_core {
        uint16_t        cpuc_dtrace_flags;      /* DTrace flags */
        uint8_t         cpuc_pad[CPUC_PADSIZE]; /* padding */
        uintptr_t       cpuc_dtrace_illval;     /* DTrace illegal value */
        kmutex_t        cpuc_pid_lock;          /* DTrace pid provider lock */
} cpu_core_t;

# endif
