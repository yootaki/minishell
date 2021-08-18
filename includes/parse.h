#ifndef PARSE_H
#define PARSE_H

#include "input.h"

/* ./parse/parse.c */
t_bool	parse_complete_command(t_token **tokens);
t_bool	parse_separator(t_token **tokens);

#endif
