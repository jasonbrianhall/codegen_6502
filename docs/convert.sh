#!/bin/bash

INPUT="chr.bin"
OUTPUT="chr.inc"

if [ ! -f "$INPUT" ]; then
    echo "File '$INPUT' not found."
    exit 1
fi

# Write label and empty line
{
    echo
    echo "CHRGraphics:"
} > "$OUTPUT"

# Dump each 16-byte block as a .db line with 6 spaces indent
xxd -c 16 -p "$INPUT" | while read -r line; do
    echo -n "      .db " >> "$OUTPUT"
    echo "$line" | sed 's/../\$& /g' | sed 's/ $//' | sed 's/ /, /g' >> "$OUTPUT"
done

echo "CHR formatted as x816-style data under label 'CHRGraphics:' in $OUTPUT"
