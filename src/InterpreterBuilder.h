#pragma once

class Parser;
class Interpreter;

class InterpreterBuilder
{
public:


public:
    InterpreterBuilder(const Parser *parser, Interpreter *interpreter);

    const Parser *getParser() const { return parser_; }
    Interpreter *getInterpreter() const { return interpreter_; }



private:
    const Parser *parser_{};
    Interpreter *interpreter_{};
};
