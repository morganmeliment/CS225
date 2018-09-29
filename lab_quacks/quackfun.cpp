/**
 * @file quackfun.cpp
 * This is where you will implement the required functions for the
 *  stacks and queues portion of the lab.
 */

namespace QuackFun {

/**
 * Sums items in a stack.
 * @param s A stack holding values to sum.
 * @return The sum of all the elements in the stack, leaving the original
 *  stack in the same state (unchanged).
 *
 * @note You may modify the stack as long as you restore it to its original
 *  values.
 * @note You may use only two local variables of type T in your function.
 *  Note that this function is templatized on the stack's type, so stacks of
 *  objects overloading the + operator can be summed.
 * @note We are using the Standard Template Library (STL) stack in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint Think recursively!
 */
template <typename T>
T sum(stack<T>& s) {
    if ((int) s.size() == 0) return T();

    T s1 = s.top();
    s.pop();
    T s2 = s1 + sum(s);
    s.push(s1);

    return s2; // stub return value (0 for primitive types). Change this!
                // Note: T() is the default value for objects, and 0 for
                // primitive types
}

/**
 * Checks whether the given string (stored in a queue) has balanced brackets.
 * A string will consist of
 * square bracket characters, [, ], and other characters. This function will return
 * true if and only if the square bracket characters in the given
 * string are balanced. For this to be true,
 * all brackets must be matched up correctly, with no extra, hanging, or unmatched
 * brackets. For example, the string "[hello][]" is balanced, "[[][[]a]]" is balanced,
 * "[]]" is unbalanced, "][" is unbalanced, and "))))[cs225]" is balanced.
 *
 * For this function, you may only create a single local variable of type stack<char>!
 * No other stack or queue local objects may be declared. Note that you may still
 * declare and use other local variables of primitive types.
 *
 * @param input The queue representation of a string to check for balanced brackets in
 * @return Whether the input string had balanced brackets
 */
bool isBalanced(queue<char> input) {
    int toClose = 0;
    stack<char> rev = stack<char>();

    for (int i = 0; i < (int) input.size();) {
        char a = input.front();
        if (a == '[') {
            toClose++;
        } else if (a == ']') {
            if (toClose < 1) {
                return false;
            }
            toClose--;
        }
        input.pop();
    }

    if (toClose == 0) return true;
    return false;
}

/**
 * Reverses even sized blocks of items in the queue. Blocks start at size
 * one and increase for each subsequent block.
 * @param q A queue of items to be scrambled
 *
 * @note Any "leftover" numbers should be handled as if their block was
 *  complete.
 * @note We are using the Standard Template Library (STL) queue in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint You'll want to make a local stack variable.
 */
template <typename T>
void scramble(queue<T>& q) {
    stack<T> s = stack<T>();
    queue<T> q2 = queue<T>();

    int i = 0;
    while (!q.empty()) {
        i++;

        if (i % 2 == 0) {
            for (int j = 0; j < i && !q.empty(); j++) {
                s.push(q.front());
                q.pop();
            }

            while (!s.empty()) {
                q2.push(s.top());
                s.pop();
            }
        } else {
            for (int j = 0; j < i && !q.empty(); j++) {
                q2.push(q.front());
                q.pop();
            }
        }
    }

    while (!q2.empty()) {
        q.push(q2.front());
        q2.pop();
    }
}

/**
 * @return true if the parameter stack and queue contain only elements of
 *  exactly the same values in exactly the same order; false, otherwise.
 *
 * @note You may assume the stack and queue contain the same number of items!
 * @note The back of the queue corresponds to the top of the stack!
 * @note There are restrictions for writing this function.
 * - Your function may not use any loops
 * - In your function you may only declare ONE local boolean variable to use in
 *   your return statement, and you may only declare TWO local variables of
 *   parametrized type T to use however you wish.
 * - No other local variables can be used.
 * - After execution of verifySame, the stack and queue must be unchanged. Be
 *   sure to comment your code VERY well.
 */
template <typename T>
bool verifySame(stack<T>& s, queue<T>& q) {
    // Check if the stack or queue are empty.
    // Return false unless they are both empty.
    if (s.empty()) return q.empty();
    else if (q.empty()) return false;

    // Store if s and q were proven to be unequal
    // at any step.
    bool retval = true;

    // Take apart the stack in order to compare
    // element by element.
    T sval = s.top();
    s.pop();

    // Recursively dig deeper until the end of
    // the stack.
    if (!s.empty()) retval = verifySame(s, q);

    // Swap the top queue element and store its
    // value for comparison. +Rebuild the stack.
    T qval = q.front();
    q.pop();
    q.push(qval);
    s.push(sval);

    // Return comparison result unless we already
    // have found that s and q are not equal.
    if (retval) return qval == sval;
    return false;
}

}
