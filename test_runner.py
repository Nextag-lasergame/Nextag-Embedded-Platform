import subprocess
import sys


argc = len(sys.argv)
if argc == 1:
    print("test_runner.py must be run with the .elf file to test", file=sys.stderr)
    sys.exit(-1)

file_to_test = str(sys.argv[1])

process = subprocess.Popen(["simavr", "-v", "-v", "-v", "-f", "16000000", "-m", "atmega328p", file_to_test],
                     stdout=subprocess.PIPE, 
                     stderr=subprocess.PIPE)
stdout_bytes, stderr_bytes = process.communicate()

stderr_string = stderr_bytes.decode("utf-8")

if "OK.." in stderr_string:
    sys.exit(0)
else:
    print(stderr_string)
    sys.exit(1)
