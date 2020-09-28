# From Russia With Love

- Relatively easy to come up with a slow solution
- Observation: when a DP is slow try to think to which parameters you can remove
- Not k players, but a player agains a player that plays k -1 times
- Here it was important to note that the length of the subarray that we consider tells us how many rounds have been played. Hence, it is not required to save M[left][right] for each player (and neither for two players).  
