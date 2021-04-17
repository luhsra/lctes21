#ifndef __FAIL_CONFIG_HPP__
#define __FAIL_CONFIG_HPP__

// #define / #undef the following configuration macros to enable/disable the
// various event sources, fault injection sinks, and miscellaneous other
// features.

// Event sources
#define CONFIG_EVENT_BREAKPOINTS
#define CONFIG_EVENT_BREAKPOINTS_RANGE
#define CONFIG_EVENT_MEMREAD
#define CONFIG_EVENT_MEMWRITE
#define CONFIG_EVENT_GUESTSYS
#define CONFIG_EVENT_IOPORT
#define CONFIG_EVENT_INTERRUPT
#define CONFIG_EVENT_TRAP
/* #undef CONFIG_EVENT_JUMP */

// Performance options
#define CONFIG_FAST_BREAKPOINTS
#define CONFIG_FAST_WATCHPOINTS
/* #undef CONFIG_INJECTIONPOINT_HOPS */

// Save/restore functionality
#define CONFIG_SR_RESTORE
#define CONFIG_SR_SAVE
#define CONFIG_SR_REBOOT

// Fail configuration
/* #undef CONFIG_BOCHS_NON_VERBOSE */
#define CONFIG_BOCHS_NO_ABORT
#define CONFIG_BOCHS_COMPRESS_STATE
#define CONFIG_SUPPRESS_INTERRUPTS
#define CONFIG_FIRE_INTERRUPTS
/* #undef CONFIG_DISABLE_KEYB_INTERRUPTS */
/* #undef SERVER_PERFORMANCE_MEASURE */
#define SERVER_COMM_HOSTNAME            "localhost"
#define SERVER_COMM_TCP_PORT            1111
#define SERVER_OUT_QUEUE_SIZE           0
#define SERVER_PERF_LOG_PATH            "perf.log"
#define SERVER_PERF_STEPPING_SEC        1
#define CLIENT_RAND_BACKOFF_TSTART      3
#define CLIENT_RAND_BACKOFF_TEND        8
#define CLIENT_RETRY_COUNT              3
#define CLIENT_JOB_REQUEST_SEC          30
#define CLIENT_JOB_LIMIT                1000
#define CLIENT_JOB_INITIAL              1
#define PROJECT_VERSION                 "1.0.1"
#define FAIL_VERSION PROJECT_VERSION

#endif // __FAIL_CONFIG_HPP__
