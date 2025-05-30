#ifndef CPPTRACE_VERSION_HPP
#define CPPTRACE_VERSION_HPP

#define CPPTRACE_VERSION_MAJOR 2
#define CPPTRACE_VERSION_MINOR 1
#define CPPTRACE_VERSION_PATCH 5

#define CPPTRACE_TO_VERSION(MAJOR, MINOR, PATCH) ((MAJOR) * 10000 + (MINOR) * 100 + (PATCH))
#define CPPTRACE_VERSION CPPTRACE_TO_VERSION(CPPTRACE_VERSION_MAJOR, CPPTRACE_VERSION_MINOR, CPPTRACE_VERSION_PATCH)

#endif
