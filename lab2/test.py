import json
import os


def cmd_read(script_name):
    a = os.popen(script_name)
    res = a.read()
    a.close()
    return str(res)


n_max = 6500000000
n_curr = 5900000
done = 0
number = 1
res = {}
opt_levels = ["0", "1", "2", "3", "s", "fast", "g"]
while n_curr < n_max:
    res[number] = {}
    res[number]["N"] = n_curr
    for level in opt_levels:
        name = f'main_{level}'
        comp_cmd = f'gcc main.c -O{level} -lm -o {name}'
        os.system(comp_cmd)
        tmp = cmd_read(f"./{name} {n_curr}")
        res[number][name] = tmp.split('\n')[1].strip()
        os.remove(name)
        done += 1
        print(f"Done: {done}")
    number += 1
    n_curr *= 2

with open("data.json", "w", encoding="utf-8") as file:
    file.write(json.dumps(res, ensure_ascii=False, indent=4))
