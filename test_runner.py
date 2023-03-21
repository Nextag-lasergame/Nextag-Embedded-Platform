import subprocess
import sys

argc = len(sys.argv)
if argc != 4:
    print("test_runner.py must be run using the following arguments: testrunner.py <.elf file> <mcu> <frequency>", file=sys.stderr)
    sys.exit(-1)

file_to_test = str(sys.argv[1])
mcu = str(sys.argv[2])
freq = str(sys.argv[3])

process = subprocess.Popen(["simavr", "-v", "-v", "-v", "-f", freq, "-m", mcu, file_to_test],
                     stdout=subprocess.PIPE, 
                     stderr=subprocess.PIPE)
stdout_bytes, stderr_bytes = process.communicate()

stdout_string = stdout_bytes.decode("utf-8")
stderr_string = stderr_bytes.decode("utf-8")

if stdout_string.startswith("Loaded"):
    result = stdout_string + stderr_string
else:
    result = stderr_string + stdout_string

if "OK.." in result:
    print(result)
    sys.exit(0)
else:
    print(result)
    sys.exit(1)
