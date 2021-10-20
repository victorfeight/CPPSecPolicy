// Exceptions.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>


// myexception extends from std::exception, allowing a custom message to be returned
struct myexception : public std::exception {
    virtual const char* what() const throw() {
        return "LOG: A Custom Exception Has Occured!";
    }
};


bool do_even_more_custom_application_logic()
{
    // TODO: Throw any standard exception
    // use throw to throw an exception
    throw std::exception();

    std::cout << "Running Even More Custom Application Logic." << std::endl;

    return true;
}
void do_custom_application_logic()
{
    // TODO: Wrap the call to do_even_more_custom_application_logic()
    //  with an exception handler that catches std::exception, displays
    //  a message and the exception.what(), then continues processing
    std::cout << "Running Custom Application Logic." << std::endl;

    try {
        if (do_even_more_custom_application_logic())
        {
            std::cout << "Even More Custom Application Logic Succeeded." << std::endl;
        }
    }
    // catch standard exception and display message
    catch (const std::exception& exception) {
        std::cerr << "do_custom_application_logic: Error message from exception: " << exception.what() << std::endl;
    }
    

    // TODO: Throw a custom exception derived from std::exception
    //  and catch it explictly in main
    throw myexception();
    std::cout << "Leaving Custom Application Logic." << std::endl;

}

float divide(float num, float den)
{
    // TODO: Throw an exception to deal with divide by zero errors using
    //  a standard C++ defined exception
    if (den == 0) {
        throw std::runtime_error("Error division by zero!");    
    }
    return (num / den);
}

void do_division() noexcept
{
    //  TODO: create an exception handler to capture ONLY the exception thrown
    //  by divide.

    float numerator = 10.0f;
    float denominator = 0;

    // handle division by zero possibility by catching exception
    try {
        auto result = divide(numerator, denominator);
        std::cout << "divide(" << numerator << ", " << denominator << ") = " << result << std::endl;
    }
    catch (const std::exception& exception) {
        std::cerr << "do_division(): Exception message: " << exception.what() << std::endl;
    }
    
}

int main()
{
    try {
        std::cout << "Exceptions Tests!" << std::endl;
        // TODO: Create exception handlers that catch (in this order):
        //  your custom exception
        //  std::exception
        //  uncaught exception 
        //  that wraps the whole main function, and displays a message to the console.
        do_division();
        do_custom_application_logic();
    }
    // catch custom exception and display
    catch (const myexception& exception) {
        std::cerr << "main: Custom Exception has occurred: " << exception.what() << std::endl;
    }
    catch (const std::exception& exception) {
        std::cerr << "main: Standard Exception has occurred: " << exception.what() << std::endl;
    }
    // catch any unhandled exceptions in post-mortem
    catch (...) {
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
