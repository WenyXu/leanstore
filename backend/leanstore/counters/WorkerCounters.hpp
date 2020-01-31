#pragma once
#include "Units.hpp"
// -------------------------------------------------------------------------------------
#include <tbb/enumerable_thread_specific.h>
// -------------------------------------------------------------------------------------
#include <atomic>
#include <unordered_map>
// -------------------------------------------------------------------------------------
namespace leanstore
{
struct WorkerCounters {
  static constexpr u64 researchy_counters = 10;
  // -------------------------------------------------------------------------------------
  atomic<u64> t_id = 9999;          // used by tpcc
  atomic<u64> hot_hit_counter = 0;  // TODO: give it a try ?
  atomic<u64> cold_hit_counter = 0;
  atomic<u64> read_operations_counter = 0;
  atomic<u64> allocate_operations_counter = 0;
  atomic<u64> restarts_counter = 0;
  atomic<u64> tx = 0;
  // -------------------------------------------------------------------------------------
  atomic<u64> dt_misses_counter[20] = {0};
  atomic<u64> dt_restarts_update_same_size[20] = {0};   // without structural change
  atomic<u64> dt_restarts_structural_change[20] = {0};  // includes insert, remove, update with different size
  atomic<u64> dt_restarts_read[20] = {0};
  atomic<u64> dt_researchy[researchy_counters][20] = {};  // temporary counter used to track some value for an idea in my mind
  // -------------------------------------------------------------------------------------
  WorkerCounters() { t_id = workers_counter++; }
  // -------------------------------------------------------------------------------------
  u64 variable_for_workload = 0;  // Used by tpcc
  // -------------------------------------------------------------------------------------
  static atomic<u64> workers_counter;
  static tbb::enumerable_thread_specific<WorkerCounters> worker_counters;
  static tbb::enumerable_thread_specific<WorkerCounters>::reference myCounters() { return worker_counters.local(); }
};
}  // namespace leanstore
// -------------------------------------------------------------------------------------
