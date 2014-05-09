# https://www.codeeval.com/open_challenges/103/

import sys

def main():
    with open(sys.argv[1],'r') as f:
        for line in f:
            tallies = {}
            nums = [int(n) for n in line.split(' ')]
            for n in nums:
                if n in tallies:
                    tallies[n] += 1
                else:
                    tallies[n] = 1

            winner = float("+inf")
            for k,v in tallies.items():
                if v == 1 and k < winner:
                    winner = k

            try:
                winnerPos = nums.index(winner)+1
                print(winnerPos)
            except ValueError:
                print(0)

if __name__ == '__main__':
    main()
