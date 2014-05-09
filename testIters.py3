import time

def timeFunc(func, times):
    t1 = time.time()
    for n in range(times):
        r = func()
    t2 = time.time()
    return t2 - t1

def iter():
    l = range(1,100000)
    s = 0
    for idx, val in enumerate(l):
        s += val
#    print(s)

def noiter():
    l = range(1,100000)
    s = 0
    for val in l:
        s += val
#    print(s)

def printjoin():
    l = '8,33,21,0,16,50,37,0,melon,7,apricot,peach,pineapple,17,21'.split(',')
    p = (' '.join(l))
    

def printfor():
    l = '8,33,21,0,16,50,37,0,melon,7,apricot,peach,pineapple,17,21'.split(',')
    for e in l:
        p = (','+ e)

t1 = timeFunc(printjoin,100000)
t2 = timeFunc(printfor,100000)

print(t1)
print(t2)
