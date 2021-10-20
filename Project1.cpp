// NumericOverflows.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>     // std::cout
#include <limits>       // std::numeric_limits

/// <summary>
/// Template function to abstract away the logic of:
///   start + (increment * steps)
/// </summary>
/// <typeparam name="T">A type that with basic math functions</typeparam>
/// <param name="start">The number to start with</param>
/// <param name="increment">How much to add each step</param>
/// <param name="steps">The number of steps to iterate</param>
/// <returns>start + (increment * steps)</returns>
template <typename T>
T add_numbers(T const& start, T const& increment, unsigned long int const& steps)
{
    // steps is an unsigned long, and our loop variable is also an unsigned long.
    // result is a T type, and starting point for T type is 0.
    // The increment is std::numeric_limits<T>::max()/5, we step 6 times to trigger overflow.

    // COMMENT:  Overflow and underflow wrapping must be accounted for:
    // signed integers: char, wchar_t, short int, int, long, long long
    // unsigned integers: unsigned char, unsigned short int, unsigned int, unsigned long, unsigned long long
    // real numbers: float, double, long double

    // Create a result equal to the start, 0. We shall increment result by numeric_limits<T>::max()/5 for each iteration.
    T result = start;
    T maxNumericLimit = std::numeric_limits<T>::max();
    T errorSignal = std::numeric_limits<T>::min();

    for (unsigned long int i = 0; i < steps; ++i)
    {
        // Result needs to be protected from incrementing over the numeric_limits<T>::max()
        // regardless of respective type.
        // NOTE: Iteration 0, 1, 2, 3, 4 are safe. 4th iteration: numeric_limits<T>::max() reached
        //          result = numeric_limits<T>::max()
        // Iteration 5:  numeric_limits<T>::max() exceeded
        //   Precondition TEST FOR OVERFLOW:  numeric_limits<T>::max() - increment < result
        // Example (iteration 5):  32767 - 6553 < 32765
        if (maxNumericLimit - increment < result) {
            // C++ has no inherent overflow protection
            // Overflow has occurred, propagate signal to caller
            return errorSignal;
        }

        result += increment;
    }

    // Success, return result to caller
    return result;
}

/// <summary>
/// Template function to abstract away the logic of:
///   start - (increment * steps)
/// </summary>
/// <typeparam name="T">A type that with basic math functions</typeparam>
/// <param name="start">The number to start with</param>
/// <param name="increment">How much to subtract each step</param>
/// <param name="steps">The number of steps to iterate</param>
/// <returns>start - (increment * steps)</returns>

template <typename T>
T subtract_numbers(T const& start, T const& decrement, unsigned long int const& steps)
{

    T result = start;
    T errorSignal = std::numeric_limits<T>::max();
    // Implementation assumes 0 as generic minimum
    T minNumericLimit = 0;

    // Iteration 5:  numeric_limits<T>::min() exceeded
        //   TEST FOR UNDERFLOW:  MIN - increment > result
        // Example (iteration 5):  0 - (-6553) > 2
        // 

    for (unsigned long int i = 0; i < steps; ++i)
    {
        // Precondition TEST FOR UNDERFLOW
        if (minNumericLimit + decrement > result) {
            return errorSignal;
        }
        result -= decrement;
    }

    return result;
}


//  NOTE:
//    You will see the unary ('+') operator used in front of the variables in the test_XXX methods.
//    This forces the output to be a number for cases where cout would assume it is a character. 

template <typename T>
void test_overflow()
{
    // TODO: The add_numbers template function will overflow in the second method call
    //        You need to change the add_numbers method to:
    //        [x] 1. Detect when an overflow will happen
    //        [x] 2. Prevent it from happening
    //        [x] 3. Return the correct value when no overflow happened or
    //        [x] 4. Return something to tell test_overflow the addition failed
    //        NOTE: The add_numbers method must remain a template in the NumericFunctions header.
    //
    //        You need to change the test_overflow method to:
    //        [x] 1. Detect when an add_numbers failed
    //        [x] 2. Inform the user the overflow happened
    //        3. A successful result displays the same result as before you changed the method
    //        NOTE: You cannot change anything between START / END DO NOT CHANGE
    //              The test_overflow method must remain a template in the NumericOverflows source file
    //
    //  There are more than one possible solution to this problem. 
    //  The solution must work for all of the data types used to call test_overflow() in main().

    // START DO NOT CHANGE
    //  how many times will we iterate
    const unsigned long int steps = 5;
    // how much will we add each step (result should be: start + (increment * steps))
    const T increment = std::numeric_limits<T>::max() / steps;
    // whats our starting point
    const T start = 0;

    std::cout << "Overflow Test of Type = " << typeid(T).name() << std::endl;
    // END DO NOT CHANGE

    std::cout << "\tAdding Numbers Without Overflow (" << +start << ", " << +increment << ", " << steps << ") = ";
    T result = add_numbers<T>(start, increment, steps);
    std::cout << +result << std::endl;
    

    // After running add_numbers, it returns either result of summation, or -1 for Overflow failure detection
    std::cout << "\tAdding Numbers With Overflow (" << +start << ", " << +increment << ", " << (steps + 1) << ") = ";
    // Postcondition checks for unsafe operation, steps + 1 causes start to keep incrementing until overflow in the last step.
    result = add_numbers<T>(start, increment, steps + 1);
 
    if (result == std::numeric_limits<T>::min()) {
        // Check for overflow by picking up signal from subtract_numbers
        std::cout << "Numeric limits exceeded. Overflow detected." << std::endl;
        // Display a message
    }
    else {
        std::cout << +result << std::endl;
    }

}

template <typename T>
void test_underflow()
{
    // TODO: The subtract_numbers template function will underflow in the second method call
    //        You need to change the subtract_numbers method to:
    //        [x] 1. Detect when an underflow will happen
    //        [x] 2. Prevent it from happening
    //        [x] 3. Return the correct value when no underflow happened or
    //        [x] 4. Return something to tell test_underflow the subtraction failed
    //        NOTE: The subtract_numbers method must remain a template in the NumericFunctions header.
    //
    //        You need to change the test_underflow method to:
    //        [x] 1. Detect when an subtract_numbers failed
    //        [x] 2. Inform the user the underflow happened
    //        [x] 3. A successful result displays the same result as before you changed the method
    //        NOTE: You cannot change anything between START / END DO NOT CHANGE
    //              The test_underflow method must remain a template in the NumericOverflows source file
    //
    //  There are more than one possible solution to this problem. 
    //  The solution must work for all of the data types used to call test_overflow() in main().

    // START DO NOT CHANGE
    //  how many times will we iterate
    const unsigned long int steps = 5;
    // how much will we subtract each step (result should be: start - (increment * steps))
    const T decrement = std::numeric_limits<T>::max() / steps;
    // whats our starting point
    const T start = std::numeric_limits<T>::max();

    std::cout << "Underflow Test of Type = " << typeid(T).name() << std::endl;
    // END DO NOT CHANGE


    std::cout << "\tSubtracting Numbers Without Overflow (" << +start << ", " << +decrement << ", " << steps << ") = ";
    auto result = subtract_numbers<T>(start, decrement, steps);
    std::cout << +result << std::endl;

    std::cout << "\tSubtracting Numbers With Overflow (" << +start << ", " << +decrement << ", " << (steps + 1) << ") = ";
    result = subtract_numbers<T>(start, decrement, steps + 1);

    // Postcondition check reads signal from result
    if (result == std::numeric_limits<T>::max()) {
        // Check for overflow by picking up signal from subtract_numbers
        std::cout << "Numeric limits exceeded. Underflow detected." << std::endl;
        // Display a message
    }
    else {
        std::cout << +result << std::endl;
    }
}


void do_overflow_tests(const std::string& star_line)
{
    std::cout << std::endl << star_line << std::endl;
    std::cout << "*** Running Overflow Tests ***" << std::endl;
    std::cout << star_line << std::endl;

    // Testing C++ primative times see: https://www.geeksforgeeks.org/c-data-types/
    // signed integers
    test_overflow<char>();
    test_overflow<wchar_t>();
    test_overflow<short int>();
    test_overflow<int>();
    test_overflow<long>();
    test_overflow<long long>();

    // unsigned integers
    test_overflow<unsigned char>();
    test_overflow<unsigned short int>();
    test_overflow<unsigned int>();
    test_overflow<unsigned long>();
    test_overflow<unsigned long long>();

    // real numbers
    test_overflow<float>();
    test_overflow<double>();
    test_overflow<long double>();
}

void do_underflow_tests(const std::string& star_line)
{
    std::cout << std::endl << star_line << std::endl;
    std::cout << "*** Running Undeflow Tests ***" << std::endl;
    std::cout << star_line << std::endl;

    // Testing C++ primative times see: https://www.geeksforgeeks.org/c-data-types/
    // signed integers
    test_underflow<char>();
    test_underflow<wchar_t>();
    test_underflow<short int>();
    test_underflow<int>();
    test_underflow<long>();
    test_underflow<long long>();

    // unsigned integers
    test_underflow<unsigned char>();
    test_underflow<unsigned short int>();
    test_underflow<unsigned int>();
    test_underflow<unsigned long>();
    test_underflow<unsigned long long>();

    // real numbers
    test_underflow<float>();
    test_underflow<double>();
    test_underflow<long double>();
}

/// <summary>
/// Entry point into the application
/// </summary>
/// <returns>0 when complete</returns>
int main()
{
    //  create a string of "*" to use in the console
    const std::string star_line = std::string(50, '*');

    std::cout << "Starting Numeric Underflow / Overflow Tests!" << std::endl;

    // run the overflow tests
    do_overflow_tests(star_line);

    // run the underflow tests
    do_underflow_tests(star_line);

    std::cout << std::endl << "All Numeric Underflow / Overflow Tests Complete!" << std::endl;

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
