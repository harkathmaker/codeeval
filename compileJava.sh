#!/bin/sh

cp $1.java Main.java
javac Main.java
time java Main $2
