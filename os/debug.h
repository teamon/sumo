#ifndef _DEBUG_H_
#define _DEBUG_H_

void debug_init();
void debug_console();
void debug_parse_package();
void dbg(const char * label, ...);

extern char DEBUG_OPTS[5];

#define DEBUG_DO_SEND_STATE 0
#define DEBUG_AUTO_ESCAPE 1
#define DEBUG_AUTO_SEARCH 2
#define DEBUG_AUTO_SEARCH_SPEED_0 3
#define DEBUG_AUTO_SEARCH_SPEED_1 4

#endif
