#ifndef __TRACING_PLUGIN_HPP__
#define __TRACING_PLUGIN_HPP__

#include <ostream>

#include "util/MemoryMap.hpp"
#include "util/ProtoStream.hpp"
#include "efw/ExperimentFlow.hpp"
#include "config/FailConfig.hpp"

#include "TracePlugin.pb.h"

// Check if configuration dependencies are satisfied:
#if !defined(CONFIG_EVENT_BREAKPOINTS) || !defined(CONFIG_EVENT_MEMREAD) || !defined(CONFIG_EVENT_MEMWRITE)
	#warning The tracing plugin may (depending on its use) need breakpoints and/or read/write memory access events. Enable these in the cmake configuration tool.
#endif

/**
 * \class TracingPlugin
 *
 * \brief Plugin to record instruction traces and memory accesses.
 *
 * This plugin is supposed to be instantiated, configured and run by
 * experiments needing instruction or memory access traces.	 Tracing can be
 * restricted to a memory or instruction address map; the restrictions are
 * applied together, i.e., a memory access is only logged if neither its
 * instruction address nor its memory address is restricted.
 *
 * TODO: document usage by example
 * FIXME: handle configuration changes after tracing start properly
 * FIXME: more explicit startup/shutdown; listener-based event interface needed?
 *		  -> should simulator.removeFlow make sure all remaining active events
 *			 are delivered?
 * FIXME: destructor -> removeFlow?
 */
class TracingPlugin : public fail::ExperimentFlow
{
private:
	fail::MemoryMap *m_memMap; //!< address restriction for memory accesses
	fail::MemoryMap *m_ipMap; //!< instruction address restriction
	//! trace nothing / instructions / mem accesses / both (can be bitwise ORed)
	enum { TRACE_NONE = 0, TRACE_IP, TRACE_MEM, TRACE_BOTH } m_tracetype;
	bool m_full_trace; //!< do a full trace (more information for the events)
	bool m_full_trace_ips; //!< do a full trace for every ip event (more information for the events)
	std::ostream *m_protoStreamFile;
	std::ostream *m_os; //!< ostream to write human-readable trace into
	fail::ProtoOStream *ps;

public:
	TracingPlugin(bool full_trace = false, bool full_trace_ips = false)
	 : m_memMap(0), m_ipMap(0), m_tracetype(TRACE_BOTH),
	   m_full_trace(full_trace), m_full_trace_ips(full_trace_ips),
       m_protoStreamFile(0), m_os(0) { }
	bool run();
	/**
	 * Restricts tracing to memory addresses listed in this MemoryMap.	An
	 * access wider than 8 bit *is* logged if *one* of the bytes it
	 * reads/writes is listed.
	 */
	void restrictMemoryAddresses(fail::MemoryMap *mm) { m_memMap = mm; }
	/**
	 * Restricts tracing to instruction addresses listed in this MemoryMap.
	 * This restriction currently silently assumes instructions are only
	 * one byte wide; make sure your memory map covers this first byte of
	 * the instructions you want to trace.
	 */
	void restrictInstructionAddresses(fail::MemoryMap *mm) { m_ipMap = mm; }
	/**
	 * If invoked with memonly=true, instructions are only logged if they
	 * conducted a memory access.  Defaults to false: All instructions are
	 * logged.
	 */
	void setLogMemOnly(bool memonly = true) { m_tracetype = memonly ? TRACE_MEM : TRACE_BOTH; }
	/**
	 * If invoked with iponly=true, only instruction addresses are logged.
	 */
	void setLogIPOnly(bool iponly = true) { m_tracetype = iponly ? TRACE_IP : TRACE_BOTH; }
	/**
	 * If invoked with fulltrace=true, a extended (full) trace is done.
	 */
	void setFullTrace(bool fulltrace) { m_full_trace = fulltrace; }
	/**
	 * If invoked with fulltrace_ips=true, a extended (full) trace for every ip event is done.
	 */
	void setFullTraceIps(bool fulltrace_ips) { m_full_trace_ips = fulltrace_ips; }
	/**
	 * ostream to trace into (human-readable)
	 */
	void setOstream(std::ostream *os) { m_os = os; }
	/**
	 * ProtoStream file to trace into (trace.proto instance)
	 */
	void setTraceFile(std::ostream *os) { m_protoStreamFile = os; }
};

#endif // __TRACING_PLUGIN_HPP__
