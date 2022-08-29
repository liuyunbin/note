/*
 * [134] Gas Station
 *
 * https://leetcode.com/problems/gas-station/description/
 *
 * algorithms
 * Medium (29.74%)
 * Total Accepted:    96.1K
 * Total Submissions: 323K
 * Testcase Example:  '[4]\n[5]'
 *
 * 
 * There are N gas stations along a circular route, where the amount of gas at
 * station i is gas[i].
 * 
 * 
 * 
 * You have a car with an unlimited gas tank and it costs cost[i] of gas to
 * travel from station i to its next station (i+1). You begin the journey with
 * an empty tank at one of the gas stations.
 * 
 * 
 * 
 * Return the starting gas station's index if you can travel around the circuit
 * once, otherwise return -1.
 * 
 * 
 * 
 * Note:
 * The solution is guaranteed to be unique.
 * 
 */
int canCompleteCircuit(int* gas, int gasSize, int* cost, int costSize) {
    for (int i = 0; i < gasSize; ++i)
        gas[i] -= cost[i];
    int sum   = 0;
    int current_sum = 0;
    int index = 0;
    for (int i = 0; i < gasSize; ++i) {
        sum += gas[i];
        current_sum += gas[i];
        if (current_sum < 0) {
            index = i + 1;
            current_sum = 0;
        }
    }
    if (sum < 0)
        return -1;
    return index;
}
