delays = [1, 15, 33]
tick_frequency = 1000000000

for delay in delays:
    print()
    print(delay)
    print()
    data = {}
    with open(f"data {delay} ms.txt", "r") as file:
        for line in file:
            splited = line.split()
            if int(splited[1]) not in data:
                data[int(splited[1])] = {splited[2][0:-1]: int(splited[-2])}
            else:
                data[int(splited[1])].update({splited[2][0:-1]: int(splited[-2])})

    read = 0
    modify = 0
    show = 0
    delay = 0

    for item in data:
        read += data[item]["read"]
        modify += data[item]["modify"]
        show += data[item]["show"]
        delay += data[item]["delay"]

    amount = len(data)

    min_read = min([key['read'] for key in data.values()])
    min_modify = min([key['modify'] for key in data.values()])
    min_show = min([key['show'] for key in data.values()])
    min_delay = min([key["delay"] for key in data.values()])

    max_read = max([key['read'] for key in data.values()])
    max_modify = max([key['modify'] for key in data.values()])
    max_show = max([key['show'] for key in data.values()])
    max_delay = max([key["delay"] for key in data.values()])

    print(f"read average: {read / amount} ticks\n"
          f"modify average {modify / amount} ticks\n"
          f"show average {show / amount} ticks\n"
          f"delay average {delay / amount}\n")

    print(f"read min: {min_read} ticks\n"
          f"modify min {min_modify} ticks\n"
          f"show min {min_show} ticks\n"
          f"delay min {min_delay}\n")

    print(f"read max: {max_read} ticks\n"
          f"modify max {max_modify} ticks\n"
          f"show max {max_show} ticks\n"
          f"delay max {max_delay}\n")

    print(f"fps min: {10**9 / ((min_show + min_modify + min_read + min_delay))}")
    print(f"fps max: {10**9 / ((max_show + max_modify + max_read + max_delay))}")
    print(f"fps avg: {10**9 / (((show + modify + read + delay) / amount))}")

    a = [[sum(list(list(data[item].values()))), item] for item in data]
    a.sort()
    print(1 / (a[0][0] / 10**9))
    print(data[a[0][1]])
