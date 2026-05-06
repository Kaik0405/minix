# MINIX Systems Engineering Portfolio

## Overview 🚀
This repository showcases targeted, production-style changes on top of MINIX: concurrency fixes, scheduler behavior, and filesystem tooling, plus a clean boot customization. The focus is on practical system engineering and validated behavior, with code modifications that touch both userland and core services.

## Highlights ✨
- Kernel-adjacent and service-level changes with measurable outcomes.
- Userland tooling implemented strictly with POSIX primitives.
- Debugging and correctness under concurrency edge cases.
- Priority management for CPU-bound vs interactive workloads.

## Scope ✅
- MINIX environment setup under Oracle VirtualBox.
- Boot message customization via `/etc/motd`.
- Concurrency fix in pthread compatibility layer.
- New user command: `tree` for recursive directory visualization.
- Scheduler tuning with dynamic priority adjustments.

## Key Changes 🔧
### 1) Environment Setup
- VM configuration in VirtualBox using a stable MINIX release.
- Resource sizing and setup notes documented outside the repository.

### 2) Boot Message (motd)
- Edited `/etc/motd` to present a custom welcome banner at login.
- Verified behavior on interactive login.

### 3) Concurrency: `pthread_mutex_trylock` Fix
- Fix applied in the pthread compatibility layer:
  - [minix/lib/libmthread/pthread_compat.c](minix/lib/libmthread/pthread_compat.c)
- Prevents indefinite blocking when a thread attempts to re-lock the same mutex.
- Expected behavior: first lock returns 0; second returns `EDEADLK` (or `EBUSY`) and allows mutex destruction.

### 4) Filesystem: `tree` Command
- `tree <path>` prints a recursive, indented directory tree.
- Implemented with POSIX syscalls: `opendir`, `readdir`, `closedir`, `stat`/`lstat`.
- Cycles avoided by detecting symbolic links and preventing recursion into them.
- Source location:
  - [minix/commands/tree/tree.c](minix/commands/tree/tree.c)

### 5) Scheduler: CPU Penalty Strategy
- Dynamic priority tuning inside the `sched` server.
- A per-process counter tracks quantum exhaustion.
- When a process exhausts $N$ quantums (e.g., $N=3$), its priority is reduced within user limits.
- During periodic balancing, processes that did not exhaust a quantum regain priority gradually.
- Reference file:
  - [minix/servers/sched/sched.c](minix/servers/sched/sched.c)

## Validation ✅
- Concurrency: `pthread_mutex_trylock` test completes with "PASS".
- Scheduler: `cpu_intensive.c` and `recovering.c` demonstrate priority evolution.
- Filesystem: `tree` tested with absolute/relative paths, current directory, and error handling.

## Tech Stack & Concepts 🧠
- MINIX 3, Oracle VirtualBox
- C (system-level programming)
- Processes, quantums, priorities, and queue balancing
- Threading compatibility (pthread vs mthread)
- Filesystem traversal with POSIX directory APIs

## Repository Pointers 🧭
- Scheduler changes: [minix/servers/sched/](minix/servers/sched/)
- Thread library: [minix/lib/libmthread/](minix/lib/libmthread/)
- `tree` command: [minix/commands/tree/](minix/commands/tree/)

## License 📄
This repository keeps the original MINIX license. See [LICENSE](LICENSE).
