flux-sched version 0.4.0 - 2017-08-24
-------------------------------------

### Fixes
 * Fix allocation of cores unevenly across nodes (#226)
 * Fixes and updates to track latest libflux-core API changes
   (#255, #253, #246, #238, #234)
 * simulator: fix and re-enable sim integration tests (#250)
 * Fix autoreconf when using side-installed autotools (#243)
 * flux-waitjob: fixes to avoid flux-core issue #1027 (#244)
 * Other fixes (#227, #231)

#### New features
 * simulator: add ISO time parsing to job traces (#260)
 * resrc: add resource API context support (#236)

#### Cleanup
 * simulator: refactor, cleanup, and ensure proper initialization.
   (#240, #250)

flux-sched version 0.3.0 - 2016-10-28
-------------------------------------

#### New features

 * Support resource membership in multiple hierarchies and
   include "flow graphs" for modeling flow resources such as power
   and bandwidh. Enhance find/select of resources to support consideration
   of power, bandwidth, etc.  (#189)

 * Add configurable scheduling optimizations for throughput-oriented workloads
   (#190, #191):

   - `sched-params=queue-depth=<k>`:
       limits the number of jobs to consider per scheduling loop
   - `sched-params=delay-scheduling=true`:
       delays scheduling to batch up individual scheduling events

#### Fixes

 * Updates to track changes in flux-core (#188, #207, #212, #216)

#### Misc

 * Update JSON handling to libjansson (#215, #220)

 * Simulator updates and cleanup (#203, 218, #219)

 * RDL enhancements for multi-hierarchy support (#196)

 * Do not assume kvs path to jobid is in lwj.jobid (#216)


flux-sched version 0.2.0 - 2016-08-13
-------------------------------------

#### New Features

 * Versatile scheduling: replace resource tree list searches
   with tree searches.

 * Runtime selection of backfill algorithm (#159).
   Examples of selecting various algorithms are
   (first remove any loaded sched plugin, e.g., flux module remove sched.fcfs):

  - *Conservative* : `flux module load sched.backfill reserve-depth=-1`
  - *EASY*         : `flux module load sched.backfill reserve-depth=1`
  - *Hybrid*       : `flux module load sched.backfill reserve-depth=4`
  - *Pure*         : `flux module load sched.backfill reserve-depth=0`

#### Fixes

 * Update to latest flux-core logging apis

 * Fix segfaults in simulator during shutdown

 * Small leak fixes in simulator

#### Deprecations

 * Remove `sim_sched` code that ran under simulator. The simulator
   now interfaces directly with sched module.

flux-sched version 0.1.0 - 2016-05-16
-------------------------------------

 * Initial release for build testing only
