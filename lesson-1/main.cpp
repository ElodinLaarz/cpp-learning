#include <expected>
#include <iostream>
#include <limits>

enum class ErrorCode {
	InvalidInput,
	Overflow,
	Underflow,
};

std::expected<int, ErrorCode> doubleInt(int input) {
	if (input > (std::numeric_limits<int>::max() / 2)) {
		return std::unexpected(ErrorCode::Overflow);
	}
	if (input < (std::numeric_limits<int>::min() / 2)) {
		return std::unexpected(ErrorCode::Underflow);
	}
	return input * 2;
}

void printError(ErrorCode error) {
	switch (error) {
		case ErrorCode::InvalidInput:
			std::cout << "Invalid input.\n";
			break;
		case ErrorCode::Overflow:
			std::cout << "Overflow occurred.\n";
			break;
		case ErrorCode::Underflow:
			std::cout << "Underflow occurred.\n";
			break;
	}
}

void printInvalidationReason() {
	printError(ErrorCode::InvalidInput);
	if (!std::cin.fail()) {
		std::cout << "Trailing characters detected after integer input.\n";
	} 
}

int main() {
	int inputNumber{ };
	std::cout << "Please enter an integer: ";
	while (!(std::cin >> inputNumber) || std::cin.peek() != '\n') {
		printInvalidationReason();
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Please enter a valid integer: ";
	}
	// Even in the success case, good practice to clear the rest of the
	// line to ignore any remaining characters.
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << "You entered: " << inputNumber << std::endl;
	std::expected<int, ErrorCode> result{doubleInt(inputNumber)};
	if (!result.has_value()) {
		printError(result.error());
		return 1;
	} 
	std::cout << "Double of the input is: " << result.value() << std::endl;
	return 0;
}
