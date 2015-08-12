/**
 * Solution to the Quora coding challenge titled "Upvotes". 
 *
 * Runs in O(n) time, where:
 * n is the size of the upvotes array, 
 *
 * Approach:
 *
 * I used a list of runs to keep track of consecutive runs of non-decreasing or 
 * non-increasing runs within each window, using their indices. For example, if my 
 * window contains {1, 1, 0, 1, 2}, then I will have two runs, [0, 1) and [2, 4) in my
 * non-decreasing list and one run [0, 1) in my non-increasing list. Note that runs 
 * represent the start and end indices, and not the actual upvotes themselves. To count
 * the total number of frames, we can calculate a summation over the number of frames
 * within each run. We use:
 *
 *     FRAMES = SUM(SIZE * (SIZE + 1) / 2),
 *
 * where SIZE represents the size of a specific run. We can do this because there are
 * exactly 1 + 2 + 3 + ... + SIZE frames per run. We then subtract the total number of 
 * non-increasing frames from the total number of non-decreasing frames, to get an
 * output value.
 *
 * The first window requires the most work, and the formula above is used. As we
 * increment our window indices, however, we simply recalculate the number of frames that
 * can be formed prior to incrementing our window indices--only looking at the first run
 * in the current window, and then add the number of frames that can be formed after
 * incrementing our window indices--only looking at the last run in the current window.
 * This way, we don't have to recalculate everything we calculated in the first window.
 *
 * @author Hugh Han
 * @email HughHan1@Gmail.com
 */

#include <iostream>
#include <list>
#include <set>

using std::cin;
using std::cout;
using std::endl;
using std::list;
using std::set;

/** 
 * Struct representing the start and end indicies of a consecutive set of non-decreasing 
 * or non-increasing integers in the array.
 */
struct run {	
	int start;
	int end;

	run(int i) { 
		this->start = i;
		this->end = i+1; 
	}

	int size() {
		return this->end - this->start;
	}
};

int main() {

	int n, k;
	cin >> n;
	cin >> k;

	int upvotes[n];
	for (int i = 0; i < n; ++i) {
		cin >> upvotes[i];
	}

	// If k == 1, then we have all 0s.
	if (k == 1) {
		while (n--) {
			cout << 0 << endl;
		}
	} else {

		// List of non-decreasing and non-increasing runs within the current k-window.
		list<run> ndRuns, niRuns;

		// Number of non-decreasing and non-increasing frames within the current k-window.
		int ndNum = 0;
		int niNum = 0;

		// Temporary size value to reduce function calls.
		int sz;

		// Denote increasing (1), decreasing (-1), or neither (0). Used to track changes.
		int direction;

		// Pass through the first k-window in the array.
		for (int i = 0; i < k-1; ++i) {
			if (upvotes[i+1] >= upvotes[i]) {
				// If direction changed, created new run. Otherwise append to previous run.
				if (direction == -1 || ndRuns.empty()) {
					ndRuns.push_back(run(i));
				} else {
					ndRuns.back().end = i+1;
				}
			} 
			if (upvotes[i+1] <= upvotes[i]) {
				// If direction changed, created new run. Otherwise append to previous run.
				if (direction == 1 || niRuns.empty()) {
					niRuns.push_back(run(i));
				} else {
					niRuns.back().end = i+1;
				}
			}

			// Set current direction.
			if (upvotes[i+1] == upvotes[i]) {
				direction = 0;
			} else if (upvotes[i+1] < upvotes[i]) {
				direction = -1;
			} else {
				direction = 1;
			}

		}

		// Sum up the total frames from all of the runs in the first k-window.
		for (auto it = ndRuns.begin(); it != ndRuns.end(); ++it) {
			sz = it->size();
			ndNum += sz * (sz + 1) / 2;
		}
		for (auto it = niRuns.begin(); it != niRuns.end(); ++it) {
			sz = it->size();
			niNum += sz * (sz + 1) / 2;
		}

		cout << ndNum - niNum << endl;

		// Pass through the rest of the k-windows, one element at a time.
		for (int i = k-1; i < n-1; ++i) {
			if (!ndRuns.empty() && i-k+1 == ndRuns.front().start) {
				ndNum -= ndRuns.front().size();
				if (ndRuns.front().size() == 1) {
					ndRuns.pop_front();
				} else {
					ndRuns.front().start += 1;
				}
			}
			if (!niRuns.empty() && i-k+1 == niRuns.front().start) {
				niNum -= niRuns.front().size();
				if (niRuns.front().size() == 1) {
					niRuns.pop_front();
				} else {
					niRuns.front().start += 1;
				}
			}

			if (upvotes[i+1] >= upvotes[i]) {
				if (direction == -1 || ndRuns.empty()) {
					ndRuns.push_back(run(i));
				} else {
					ndRuns.back().end = i+1;
				}
				ndNum += ndRuns.back().size();
			} 
			if (upvotes[i+1] <= upvotes[i]) {
				if (direction == 1 || niRuns.empty()) {
					niRuns.push_back(run(i));
				} else {
					niRuns.back().end = i+1;
				}
				niNum += niRuns.back().size();
			}

			// Set current direction.
			if (upvotes[i+1] == upvotes[i]) {
				direction = 0;
			} else if (upvotes[i+1] < upvotes[i]) {
				direction = -1;
			} else {
				direction = 1;
			}

			cout << ndNum - niNum << endl;
		}

	}

	return 0;
}