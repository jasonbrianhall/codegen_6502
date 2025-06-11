s/a:_/_/g
s/a:\$/\$/g

s/_//g

s/Y/y/g

s/X/x/g

s/\.word/\.dw/g

s/\.byte/\.db/g

# Replace .pad with .db for padding
s/\.pad/\.db/g

# Replace .base with a label
#s/\.base \$FFFA/InterruptVectors:/g

# Fix the .dw directives to be one instruction with comma-separated values
#s/\.dw NMI\n\.dw Reset\n\.dw Reset/\.dw NMI, Reset, Reset/g


