
#ifndef DEFCORE_CONST_H
#define DEFCORE_CONST_H

#ifndef OOO_ISSUE_WIDTH
#define OOO_ISSUE_WIDTH 4
#endif

#ifndef OOO_MAX_PHYS_REG_FILE_SIZE
#define OOO_MAX_PHYS_REG_FILE_SIZE 256
#endif

#ifndef OOO_PHYS_REG_FILE_SIZE
#define OOO_PHYS_REG_FILE_SIZE 256
#endif

#ifndef OOO_BRANCH_IN_FLIGHT
#define OOO_BRANCH_IN_FLIGHT 24
#endif

#ifndef OOO_LOAD_Q_SIZE
#define OOO_LOAD_Q_SIZE 48
#endif

#ifndef OOO_STORE_Q_SIZE
#define OOO_STORE_Q_SIZE 48
#endif

#ifndef OOO_FETCH_Q_SIZE
#define OOO_FETCH_Q_SIZE 48
#endif

#ifndef OOO_ISSUE_Q_SIZE
#define OOO_ISSUE_Q_SIZE 64
#endif

#ifndef OOO_ROB_SIZE
#define OOO_ROB_SIZE 128
#endif

#ifndef OOO_FETCH_WIDTH
#define OOO_FETCH_WIDTH 4
#endif

#ifndef OOO_FRONTEND_WIDTH
#define OOO_FRONTEND_WIDTH 4
#endif

#ifndef OOO_FRONTEND_STAGES
#define OOO_FRONTEND_STAGES 4
#endif

#ifndef OOO_DISPATCH_WIDTH
#define OOO_DISPATCH_WIDTH 4
#endif

#ifndef OOO_WRITEBACK_WIDTH
#define OOO_WRITEBACK_WIDTH 4
#endif

#ifndef OOO_COMMIT_WIDTH
#define OOO_COMMIT_WIDTH 4
#endif

#ifndef OOO_ITLB_SIZE
#define OOO_ITLB_SIZE 32
#endif

#ifndef OOO_DTLB_SIZE
#define OOO_DTLB_SIZE 32
#endif

namespace OOO_CORE_MODEL {

    static const int MAX_THREADS_BIT = 4; // up to 16 threads
    static const int MAX_ROB_IDX_BIT = 12; // up to 4096 ROB entries

    //
    // Operand formats
    //
    static const int MAX_OPERANDS = 4;
    static const int RA = 0;
    static const int RB = 1;
    static const int RC = 2;
    static const int RS = 3; // (for stores only)

    //
    // Uop to functional unit mappings
    //
    static const int FU_COUNT = 8;
    static const int LOADLAT = 2;

    static const int LOAD_FU_COUNT = 2;

    //
    // Global limits
    //

    const int MAX_ISSUE_WIDTH = OOO_ISSUE_WIDTH;

    // Largest size of any physical register file or the store queue:
    const int MAX_PHYS_REG_FILE_SIZE = OOO_MAX_PHYS_REG_FILE_SIZE;
    //  const int PHYS_REG_FILE_SIZE = 256;
    const int PHYS_REG_FILE_SIZE = OOO_PHYS_REG_FILE_SIZE;
    const int PHYS_REG_NULL = 0;

    enum { PHYSREG_NONE, PHYSREG_FREE, PHYSREG_WAITING, PHYSREG_BYPASS,
        PHYSREG_WRITTEN, PHYSREG_ARCH, PHYSREG_PENDINGFREE, MAX_PHYSREG_STATE };

    //
    // IMPORTANT! If you change this to be greater than 256, you MUST
    // #define BIG_ROB below to use the correct associative search logic
    // (16-bit tags vs 8-bit tags).
    //
    // SMT always has BIG_ROB enabled: high 4 bits are used for thread id
    //
#define BIG_ROB

    const int ROB_SIZE = OOO_ROB_SIZE;
    //  const int ROB_SIZE = 64;

    // Maximum number of branches in the pipeline at any given time
    const int MAX_BRANCHES_IN_FLIGHT = OOO_BRANCH_IN_FLIGHT;

    // Set this to combine the integer and FP phys reg files:
    // #define UNIFIED_INT_FP_PHYS_REG_FILE

#ifdef UNIFIED_INT_FP_PHYS_REG_FILE
    // unified, br, st
    const int PHYS_REG_FILE_COUNT = 3;
#else
    // int, fp, br, st
    const int PHYS_REG_FILE_COUNT = 4;
#endif

    //
    // Load and Store Queues
    //
    const int LDQ_SIZE = OOO_LOAD_Q_SIZE;
    const int STQ_SIZE = OOO_STORE_Q_SIZE;

    //
    // Fetch
    //
    const int FETCH_QUEUE_SIZE = OOO_FETCH_Q_SIZE;
    const int FETCH_WIDTH = OOO_FETCH_WIDTH;

    //
    // Frontend (Rename and Decode)
    //
    const int FRONTEND_WIDTH = OOO_FRONTEND_WIDTH;
    const int FRONTEND_STAGES = OOO_FRONTEND_STAGES;

    //
    // Dispatch
    //
    const int DISPATCH_WIDTH = OOO_DISPATCH_WIDTH;

    //
    // Writeback
    //
    const int WRITEBACK_WIDTH = OOO_WRITEBACK_WIDTH;

    //
    // Commit
    //
    const int COMMIT_WIDTH = OOO_COMMIT_WIDTH;

    // #define MULTI_IQ

    // #ifdef ENABLE_SMT
    //   //
    //   // Multiple issue queues are currently only supported in
    //   // the non-SMT configuration, due to ambiguities in the
    //   // ICOUNT SMT heuristic when multiple queues are active.
    //   //
    // #undef MULTI_IQ
    // #endif

#ifdef MULTI_IQ
    const int MAX_CLUSTERS = 4;
    //
    // Clustering, Issue Queues and Bypass Network
    //
    const int MAX_FORWARDING_LATENCY = 2;

    static const int ISSUE_QUEUE_SIZE = 16;
#else
    const int MAX_CLUSTERS = 1;

    const int MAX_FORWARDING_LATENCY = 0;

    static const int ISSUE_QUEUE_SIZE = OOO_ISSUE_Q_SIZE;
#endif

    // TLBs
    const int ITLB_SIZE = OOO_ITLB_SIZE;
    const int DTLB_SIZE = OOO_DTLB_SIZE;

    // How many bytes of x86 code to fetch into decode buffer at once
    static const int ICACHE_FETCH_GRANULARITY = 16;
    // Deadlock timeout: if nothing dispatches for this many cycles, flush the pipeline
    static const int DISPATCH_DEADLOCK_COUNTDOWN_CYCLES = 4096; //256;
    // Size of unaligned predictor Bloom filter
    static const int UNALIGNED_PREDICTOR_SIZE = 4096;

    // String names used in stats labels
    static const char* physreg_state_names[MAX_PHYSREG_STATE] = {"none", "free",
        "waiting", "bypass", "written", "arch", "pendingfree"};
    static const char* short_physreg_state_names[MAX_PHYSREG_STATE] = {"-",
        "free", "wait", "byps", "wrtn", "arch", "pend"};

#ifdef MULTI_IQ
    static const char* cluster_names[MAX_CLUSTERS] = {"int0", "int1", "ld", "fp"};
#else
    static const char* cluster_names[MAX_CLUSTERS] = {"all"};
#endif

    static const char* phys_reg_file_names[PHYS_REG_FILE_COUNT] = {"int", "fp", "st", "br"};

};

#endif // DEFCORE_CONST_H
