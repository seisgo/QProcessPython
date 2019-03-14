import time
import sys

print('Today is %s' %time.ctime(time.time()), flush=True)
time1 = time.time();

print('Python sys path: ', sys.path)
print('Python sys version: ', sys.version)
print('Python sys info: ', sys.version_info)
sys.stdout.flush()

sumVal = 0
for i in range(10000):
    sumVal += i
    if i%1000==0:
        time.sleep(1)
        print(i, sumVal, flush=True)
        
time2 = time.time()
print('The process last %d seconds' % (time2-time1))