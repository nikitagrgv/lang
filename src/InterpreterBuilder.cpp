#include "InterpreterBuilder.h"

#include "Interpreter.h"
#include "Parser.h"


InterpreterBuilder::InterpreterBuilder(const Parser *parser, Interpreter *interpreter)
    : parser_(parser)
    , interpreter_(interpreter)
{}




