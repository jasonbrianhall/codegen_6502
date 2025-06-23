#!/bin/bash
# Convert Characters to x816 format


# Input and output filenames
INPUT="chr.bin"
OUTPUT="chr.inc"

# Ensure input exists
if [ ! -f "$INPUT" ]; then
    echo "Input file '$INPUT' not found."
    exit 1
fi

# Write .segment header
echo '.segment "CHARS"' > "$OUTPUT"

# Convert binary to .byte-formatted assembly data
xxd -c 16 -p "$INPUT" | while read -r line; do
    echo -n ".byte " >> "$OUTPUT"
    echo "$line" | sed 's/../\$& /g' | sed 's/ $//' | sed 's/ /, /g' >> "$OUTPUT"
done

echo "CHR data converted to '$OUTPUT'"
