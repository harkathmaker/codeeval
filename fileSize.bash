#!/bin/bash
# https://www.codeeval.com/open_challenges/26/

wc -c $1 | awk {'print $1'}
