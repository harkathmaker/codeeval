# https://www.codeeval.com/open_challenges/19/

import sys

def bitsAreEqual(n, p1, p2):
   return (n & 1<<(p1-1) != 0) == (n & 1<<(p2-1) != 0)

def main():
    f = open(sys.argv[1],'r')
    for line in f:
        s = line.split(',')
        if len(s) < 3:
            continue
        if bitsAreEqual(int(s[0]), int(s[1]), int(s[2])):
            print('true')
        else:
            print('false')
    f.close()

if __name__ == '__main__':
    main()
