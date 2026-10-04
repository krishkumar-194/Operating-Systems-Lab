def priority_scheduling(processes):
    # Higher priority number = higher priority
    order = sorted(processes, key=lambda p: p[2], reverse=True)

    current_time = 0
    results = []

    for pid, burst, priority in order:
        waiting = current_time
        current_time += burst
        turnaround = current_time

        results.append(
            (pid, burst, priority, waiting, turnaround)
        )

    return results


def round_robin(processes, quantum):
    remaining = {p[0]: p[1] for p in processes}
    waiting = {p[0]: 0 for p in processes}
    turnaround = {}

    queue = [p[0] for p in processes]
    burst = {p[0]: p[1] for p in processes}

    current_time = 0

    while queue:
        pid = queue.pop(0)

        if remaining[pid] <= quantum:
            current_time += remaining[pid]
            remaining[pid] = 0
            turnaround[pid] = current_time
            waiting[pid] = turnaround[pid] - burst[pid]
        else:
            current_time += quantum
            remaining[pid] -= quantum
            queue.append(pid)

    results = []

    for pid, burst_time, priority in processes:
        results.append(
            (
                pid,
                burst_time,
                priority,
                waiting[pid],
                turnaround[pid]
            )
        )

    return results


def display(title, results):
    print("\n" + "=" * 70)
    print(title)
    print("=" * 70)

    print(
        "Process\tBurst\tPriority\tWaiting\tTurnaround"
    )
    print("-" * 70)

    total_waiting = 0
    total_turnaround = 0

    for pid, burst, priority, waiting, turnaround in results:
        print(
            f"P{pid}\t{burst}\t{priority}\t\t"
            f"{waiting}\t{turnaround}"
        )

        total_waiting += waiting
        total_turnaround += turnaround

    n = len(results)

    print("-" * 70)
    print(
        f"Average Waiting Time    : "
        f"{total_waiting / n:.2f}"
    )
    print(
        f"Average Turnaround Time : "
        f"{total_turnaround / n:.2f}"
    )


def main():
    print("=" * 70)
    print("CPU SCHEDULING - PRIORITY AND ROUND ROBIN")
    print("=" * 70)

    n = int(input("\nEnter number of processes: "))

    processes = []

    for i in range(1, n + 1):
        burst = int(
            input(f"Enter burst time for P{i}: ")
        )

        priority = int(
            input(f"Enter priority for P{i}: ")
        )

        if burst <= 0:
            print("Burst time must be greater than 0.")
            return

        processes.append(
            (i, burst, priority)
        )

    quantum = int(
        input("\nEnter time quantum for Round Robin: ")
    )

    if quantum <= 0:
        print("Time quantum must be greater than 0.")
        return

    priority_result = priority_scheduling(processes)
    rr_result = round_robin(processes, quantum)

    display(
        "PRIORITY SCHEDULING",
        priority_result
    )

    display(
        "ROUND ROBIN SCHEDULING",
        rr_result
    )


if __name__ == "__main__":
    main()