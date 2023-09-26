#!/bin/bash
if [ $# -ge 2 ]; then
  cal $1 $2
fi
if [ $# -ge 4 ]; then
  cal $3 $4
fi
if [ $# -ge 6 ]; then
  cal $5 $6
fi
if [ $# -ge 8 ]; then
  cal $7 $8
fi
