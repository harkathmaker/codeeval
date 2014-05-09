# https://www.codeeval.com/open_challenges/115/

import sys, re

g_intRegex = re.compile(r"[-+]?\d+(\.0*)?$")

# Int testing code from Shavais on Stack Overflow
def isInt_re2(v):
    return g_intRegex.match(str(v).strip()) is not None

def main():
    with open(sys.argv[1],'r') as f:
        for line in f:
            elements = line[:-1].split(',')
            nums = []
            strs = []
            for e in elements:
                if isInt_re2(e):
                    nums.append(e)
                else:
                    strs.append(e)

            if len(strs) > 0:
                print(",".join(strs),end="")
            if len(strs) > 0 and len(nums) > 0:
                print("|",end="")
            if len(nums) > 0:
                print(",".join(nums),end="")
            print()

if __name__ == '__main__':
    main()
