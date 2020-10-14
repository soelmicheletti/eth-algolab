The problem is similar to the optimal interval problem
However, we have to visualize the situation as a clock. Some intervals go from the "end" of the clock back to the "begin"
We do the following: 

- We compute the best result without considering the intervals that pass midnight
- We compute the best result by considering the interval that passes midnight with shortest length
- We compute the best result by considering the interval that passes midnight with smallest value of a
- We compute the best result by considering the interval that passes midnight with smallest value of b

We return the best between this four options
