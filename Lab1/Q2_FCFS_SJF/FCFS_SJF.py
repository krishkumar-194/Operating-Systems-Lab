def calculate_fcfs(burst_times):
    n = len(burst_times)

    waiting_time = [0] * n
    turnaround_time = [0] * n
    completion_time = [0] * n

    for i in range(n):
        if i == 0:
            completion_time[i] = burst_times[i]
        else:
            completion_time[i] = completion_time[i - 1] + burst_times[i]

        turnaround_time[i] = completion_time[i]
        waiting_time[i] = turnaround_time[i] - burst_times[i]

    return waiting_time, turnaround_time, completion_time


def calculate_sjf(burst_times):
    n = len(burst_times)

    processes = list(range(n))
    processes.sort(key=lambda i: burst_times[i])

    waiting_time = [0] * n
    turnaround_time = [0] * n
    completion_time = [0] * n

    current_time = 0

    for i in processes:
        waiting_time[i] = current_time
        current_time += burst_times[i]
        completion_time[i] = current_time
        turnaround_time[i] = completion_time[i]

    return processes, waiting_time, turnaround_time, completion_time


def display_result(title, burst_times, waiting_time,
                   turnaround_time, completion_time, order=None):

    print("\n" + "=" * 65)
    print(title)
    print("=" * 65)

    if order is not None:
        print("Execution Order:",
              " -> ".join(f"P{i + 1}" for i in order))

    print("\nProcess\tBurst\tWaiting\tTurnaround\tCompletion")
    print("-" * 55)

    total_wt = 0
    total_tat = 0

    for i in range(len(burst_times)):
        print(
            f"P{i + 1}\t{burst_times[i]}\t"
            f"{waiting_time[i]}\t{turnaround_time[i]}"
            f"\t\t{completion_time[i]}"
        )

        total_wt += waiting_time[i]
        total_tat += turnaround_time[i]

    print("-" * 55)

    print(f"Average Waiting Time    : {total_wt / len(burst_times):.2f}")
    print(f"Average Turnaround Time : {total_tat / len(burst_times):.2f}")


def main():
    print("=" * 65)
    print("CPU SCHEDULING - FCFS AND SJF")
    print("=" * 65)

    n = int(input("\nEnter number of processes: "))

    burst_times = []

    for i in range(n):
        burst = int(input(f"Enter burst time for P{i + 1}: "))

        if burst <= 0:
            print("Burst time must be greater than 0.")
            return

        burst_times.append(burst)

    # FCFS
    fcfs_wt, fcfs_tat, fcfs_ct = calculate_fcfs(burst_times)

    display_result(
        "FCFS SCHEDULING",
        burst_times,
        fcfs_wt,
        fcfs_tat,
        fcfs_ct,
        list(range(n))
    )

    # SJF
    sjf_order, sjf_wt, sjf_tat, sjf_ct = calculate_sjf(burst_times)

    display_result(
        "SJF SCHEDULING",
        burst_times,
        sjf_wt,
        sjf_tat,
        sjf_ct,
        sjf_order
    )


if __name__ == "__main__":
    main()