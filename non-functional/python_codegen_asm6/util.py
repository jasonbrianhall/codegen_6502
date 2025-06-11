#!/usr/bin/env python3
"""
Python implementation of utility functions
Converted from original util.hpp/util.cpp files
"""

# Maps to store comments and newlines
comment_map = {}
newline_set = set()

def map_comment(line, comment):
    """
    Map a comment to a line number
    """
    comment_map[line] = comment
    
def map_newline(line):
    """
    Record an empty line at the given line number
    """
    newline_set.add(line)
    
def lookup_comment(line):
    """
    Look up a comment for a given line number
    If found, remove it from the map so it's only claimed once
    """
    if line in comment_map:
        # Get the comment
        comment = comment_map[line]
        # Remove from the map so it can't be claimed again
        del comment_map[line]
        return comment
    return None
    
def duplicate_string(s):
    """
    Duplicate a string (equivalent to the DUP_YYTEXT macro)
    In Python this isn't strictly necessary, but kept for API consistency
    """
    return s
