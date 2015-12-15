# Upvotes

This is my solution to one of Quora's programming challenges, available [here](https://www.quora.com/challenges#upvotes).


#### Time Complexity ####
Runs in *O(n)* time, where *n* is the size of the upvotes array.

#### Approach ####

I used a list of runs to keep track of consecutive runs of non-decreasing or 
non-increasing runs within each window, using their indices. For example, if my 
window contains {1, 1, 0, 1, 2}, then I will have two runs, [0, 1) and [2, 4) in my
non-decreasing list and one run [0, 1) in my non-increasing list. Note that runs 
represent the start and end indices, and not the actual upvotes themselves. To count
the total number of frames, we can calculate a summation over the number of frames
within each run. We use:

  ``` FRAMES = SUM(SIZE * (SIZE + 1) / 2)```,

where SIZE represents the size of a specific run. We can do this because there are
exactly 1 + 2 + 3 + ... + SIZE frames per run. We then subtract the total number of 
non-increasing frames from the total number of non-decreasing frames, to get an
output value.

The first window requires the most work, and the formula above is used. As we
increment our window indices, however, we simply recalculate the number of frames that
can be formed prior to incrementing our window indices--only looking at the first run
in the current window, and then add the number of frames that can be formed after
incrementing our window indices--only looking at the last run in the current window.
This way, we don't have to recalculate everything we calculated in the first window.
