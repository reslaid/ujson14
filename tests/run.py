import os
import re
import subprocess

valgrind: str = 'valgrind'

def test_memory_leak(path: str):
    try:
        process = subprocess.Popen([valgrind, '--leak-check=full', path], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    except FileNotFoundError:
        print("To run tests you need to install {}!".format(valgrind))
        exit(2)

    stdout, stderr = process.communicate()

    stdout = stdout.decode()
    stderr = stderr.decode()
    
    output = stdout + stderr

    noleaks: bool = 'no leaks are possible' in output
    if noleaks:
        print(f'=== No memory leaks detected, target: {path}')
    else:
        print(f'=== Memory leaks detected, target: {path}')

    pattern = r'(\d+) errors from (\d+) contexts'
    match = re.search(pattern, output)
    if match:
        num_errors: int = int(match.group(1))

    print(f'=== {num_errors} erros found, target: {path}')

    if noleaks and num_errors == 0: 
        print(f'=== Test passed, target: {path}\n')
    else:
        print(f'=== Test failed, target: {path}\n')

if __name__ == "__main__":
    for filename in os.listdir('./build'):
        if filename.startswith('ujson') and filename.endswith('.out'):
            test_memory_leak('./build/' + filename)
