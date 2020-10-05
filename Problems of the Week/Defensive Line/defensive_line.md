#Defensive Line

First we save an array with T[i] = index of sequence with sum k starting in i, or -1 if such a sequence does not exist

DP[m][p] := "points" with still m attackers available and considering the defenders from 1 to p
