#include <expected>
#include <iostream>
#include <limits>

enum class DoublingError {
	Overflow,
	Underflow,
};

void printDoublingError(int input, DoublingError error) {
	switch (error) {
	case DoublingError::Overflow:
		std::cout << "Overflow occurred while doubling the integer " << input << std::endl;
		break;
	case DoublingError::Underflow:
		std::cout << "Underflow occurred while doubling the integer" << input << std::endl;
		break;
	}
};

enum class ParsingError {
	NotAnInteger,
	InvalidTrailingCharacters,
};

void printParsingError(ParsingError error) {
	switch (error) {
	case ParsingError::NotAnInteger:
		std::cout << "Input is not a valid integer." << std::endl;
		break;
	case ParsingError::InvalidTrailingCharacters:
		std::cout << "Trailing characters detected after integer input." << std::endl;
		break;
	}
};

void invalidInputError() {
	switch (std::cin.fail()) {
	case true:
		printParsingError(ParsingError::NotAnInteger);
		break;
	case false:
		printParsingError(ParsingError::InvalidTrailingCharacters);
		break;
	}
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::expected<int, DoublingError> doubleInt(int input) {
	if (input > (std::numeric_limits<int>::max() / 2)) {
		return std::unexpected(DoublingError::Overflow);
	}
	if (input < (std::numeric_limits<int>::min() / 2)) {
		return std::unexpected(DoublingError::Underflow);
	}
	return input * 2;
}

int main() {
	int inputNumber{ };
	std::cout << "Please enter an integer: ";
	while (!(std::cin >> inputNumber) || std::cin.peek() != '\n') {
		invalidInputError();
		std::cout << "Please enter a valid integer: ";
	}
	std::cout << "You entered: " << inputNumber << std::endl;
	std::expected<int, DoublingError> result{doubleInt(inputNumber)};
	if (!result.has_value()) {
		printDoublingError(inputNumber, result.error());
		return 1;
	} 
	std::cout << "Double of the input is: " << result.value() << std::endl;
	return 0;
}
