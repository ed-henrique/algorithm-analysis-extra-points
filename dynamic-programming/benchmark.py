#!/usr/bin/python3

from os import walk
import os
import os.path
import shlex
import subprocess
import sys
import logging

formatter = logging.Formatter('%(process)d - [%(asctime)s] : %(levelname)s -> %(message)s')
csvFormatter = logging.Formatter('%(message)s')

file_logger = logging.getLogger('file_logger')
file_logger.setLevel(logging.DEBUG)

stdout_logger = logging.getLogger('stdout_logger')
stdout_logger.setLevel(logging.DEBUG)

stdout_handler = logging.StreamHandler(sys.stdout)
stdout_handler.setLevel(logging.DEBUG)
stdout_handler.setFormatter(formatter)

stdout_logger.addHandler(stdout_handler)

BINARY_PROGRAM = ["memo", "no_memo"]
TIMES_RUN = 13

def run_code():
    file_handler = logging.FileHandler("results.csv")
    file_handler.setLevel(logging.DEBUG)
    file_handler.setFormatter(csvFormatter)
    file_logger.addHandler(file_handler)

    file_logger.debug(f"Algoritmo;Tempo")

    for binary in BINARY_PROGRAM:
        cmd = shlex.split("./" + binary)
        times = []

        for count_time in range(TIMES_RUN):
            stdout_logger.debug(f"Binary: {binary} - Time {count_time+1}")            

            process = subprocess.Popen(cmd,
                    stdout=subprocess.PIPE, 
                    stderr=subprocess.PIPE,
                    universal_newlines=True)
            stdout, stderr = process.communicate()            

            if not stderr:
                stdout_logger.debug(f"Time elapsed: {stdout}-----------------------------------------------------------------")
                times.append(float(stdout))
            else:
                print(stderr)

        time_average = sum(times) / len(times)
        file_logger.debug(f"{binary};{time_average}")

def main():
    run_code()

if __name__ == "__main__":
    main()
