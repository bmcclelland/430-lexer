#pragma once

// GCC complains about reaching the end of a function with no return
//  after a switch where every enum case is handled but there is no default. 
// Putting this after it shuts it up with the least impact.
// If the switch ever becomes non-total, a separate warning will tell you so.
#define UNREACHABLE std::abort()

