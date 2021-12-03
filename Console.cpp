#include "Console.h"

Console::Console(string _name, bool _enable) : name(_name), enable(_enable) {}
Console::~Console() {}

bool Console::isEnable() { return enable; }

void Console::setEnable(bool _enable) { enable = _enable; }