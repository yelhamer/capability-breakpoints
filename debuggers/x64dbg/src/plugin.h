#pragma once

#include "datastructure.h"
#include "pluginmain.h"
#include "pluginsdk/bridgemain.h"
#include "x64dbg-debugger.h"

#include <memory>
#include <string>
#include <unordered_map>

// functions
bool pluginInit(PLUG_INITSTRUCT* initStruct);
void pluginStop();
void pluginSetup();
