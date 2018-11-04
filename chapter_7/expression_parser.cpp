//
// Created by raleigh on 11/4/18.
//

#include "expression_parser.h"

std::array<std::string, 3> ExpressionParser::possible_right_delimeters = {")", "}", "]"};

std::array<std::string, 3> ExpressionParser::possible_left_delimeters = {"(", "{", "["};

std::map<std::string, int> ExpressionParser::operators = {{"+", 1},
                                                          {"-", 1},
                                                          {"*", 2},
                                                          {"/", 2}};

bool ExpressionParser::is_right_delimeter(const std::string &character) {

    return (std::find(ExpressionParser::possible_right_delimeters.begin(),
                      ExpressionParser::possible_right_delimeters.end(), character) !=
            ExpressionParser::possible_right_delimeters.end());

}

bool ExpressionParser::is_left_delimeter(const std::string &character) {

    return (std::find(ExpressionParser::possible_left_delimeters.begin(),
                      ExpressionParser::possible_left_delimeters.end(), character) !=
            ExpressionParser::possible_left_delimeters.end());
}

bool ExpressionParser::is_operator(const std::string &character) {
    std::array<std::string, 4> operators = {"+", "-", "/", "*"};
    return (std::find(operators.begin(), operators.end(), character) != operators.end());

}

bool ExpressionParser::is_lower_precedence(const std::string &operator1, const std::string &operator2) {

    return (ExpressionParser::operators.find(operator1)->second < ExpressionParser::operators.find(operator2)->second);
}

double ExpressionParser::parse_postfix_expression(const std::string &expression) {
    //std::vector<std::string> splitted_results;

    std::array<std::string, 4> possible_operators = {"+", "-", "/", "*"};

    std::stack<double> expression_stack;

    std::istringstream string_stream(expression);

    for (std::string ch; string_stream >> ch;) {
        if (std::find(possible_operators.begin(), possible_operators.end(), ch) != possible_operators.end()) {
            // all operators are binary operators, so they require two operands

            if (expression_stack.size() >= 2) {

                double operand1 = expression_stack.top();
                expression_stack.pop();

                double operand2 = expression_stack.top();
                expression_stack.pop();

                // C++ doesn't have reflection, which would make this a lot easier, and case statements don't support strings..
                double result;

                if (ch == "+") {
                    result = operand2 + operand1;

                } else if (ch == "*") {
                    result = operand2 * operand1;
                } else if (ch == "-") {
                    result = operand2 - operand1;
                } else if (ch == "/") {
                    result = operand2 / operand1;
                } else {
                    std::cout << "The operation you entered ( " << ch << ") is not supported." << std::endl;
                    exit(1);
                }

                expression_stack.push(result);
            }
        } else {
            expression_stack.push(std::stod(ch));
        }
    }

    assert(expression_stack.size() == 1);

    return expression_stack.top();
}

std::string ExpressionParser::convert_parenthesized_infix_to_postfix(
        const std::string &parenthesized_infix_expression) {
    std::string postfix_expression;

    std::array<std::string, 4> possible_operators = {"/", "*", "-", "+"};

    std::array<std::string, 3> possible_left_delimeters = {"(", "{", "["};

    std::array<std::string, 3> possible_right_delimeters = {")", "}", "]"};

    std::stack<std::string> expression_stack;

    std::istringstream string_stream(parenthesized_infix_expression);

    for (std::string ch; string_stream >> ch;) {

        if (std::find(possible_left_delimeters.begin(), possible_left_delimeters.end(), ch) !=
            possible_left_delimeters.end()) {
            expression_stack.push(ch);
        } else if (std::all_of(ch.begin(), ch.end(), ::isalnum)) {
            postfix_expression += ch;
        } else if (std::find(possible_operators.begin(), possible_operators.end(), ch) !=
                   possible_operators.end()) {
            expression_stack.push(ch);
        } else {
            // next symbol should be a right parenthesis
            assert(std::find(possible_right_delimeters.begin(), possible_right_delimeters.end(), ch) !=
                   possible_right_delimeters.end());

            // operation symbol should be on the top of the stack!
            assert(std::find(possible_operators.begin(), possible_operators.end(), expression_stack.top()) !=
                   possible_operators.end());

            postfix_expression += expression_stack.top();

            expression_stack.pop();

            // after the operation symbol got popped, there should be a left parenthesis on the top
            assert(std::find(possible_left_delimeters.begin(), possible_left_delimeters.end(),
                             expression_stack.top()) != possible_left_delimeters.end());

            expression_stack.pop();
        }
    }
    assert(expression_stack.size() == 0);

    return postfix_expression;
}

std::string ExpressionParser::convert_general_infix_to_postfix(const std::string &infix_expression) {
    std::string postfix_expression = "";

    std::array<std::string, 4> possible_operators = {"/", "*", "-", "+"};

    std::stack<std::string> expression_stack;

    std::istringstream string_stream(infix_expression);

    for (std::string ch; string_stream >> ch;) {

        if (is_left_delimeter(ch)) {
            expression_stack.push(ch);
        } else if (std::all_of(ch.begin(), ch.end(), ::isalnum)) {
            postfix_expression += ch;
        } else if (is_operator(ch)) {

           /* failing because the stack is empty at this point.. */ 
            do {
                postfix_expression += expression_stack.top();
                expression_stack.pop();
            } while (!expression_stack.empty() &&
                     !is_left_delimeter(expression_stack.top()) &&
                     !(is_operator(expression_stack.top()) && is_lower_precedence(expression_stack.top(), ch)));


            expression_stack.push(ch);

        } else {
            assert(is_right_delimeter(ch));

            postfix_expression += expression_stack.top();
            expression_stack.pop();

            bool lparenthensis_seen = false;

            if (!is_left_delimeter(expression_stack.top())) {
                postfix_expression += expression_stack.top();
                expression_stack.pop();

            } else {
                lparenthensis_seen = true;

            }

            // you should have seen a left parenthesis by now
            assert(lparenthensis_seen);
            // now that you've seen the left parenthesis, pop it
            expression_stack.pop();
        }
    }

    while (!expression_stack.empty()) {
        assert(is_left_delimeter(expression_stack.top()) == false);

        postfix_expression += expression_stack.top();

        expression_stack.pop();

    }

    return postfix_expression;

}