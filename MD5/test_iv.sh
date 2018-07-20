#!/bin/sh

BASEDIR=$(dirname $0)
FAILURES=0

if [ ! -r iv_input.txt ]; then
    echo "Generating iv_input.txt..."
    cat > iv_input.txt <<EOF
’Twas brillig, and the slithy toves
      Did gyre and gimble in the wabe:
All mimsy were the borogoves,
      And the mome raths outgrabe.

“Beware the Jabberwock, my son!
      The jaws that bite, the claws that catch!
Beware the Jubjub bird, and shun
      The frumious Bandersnatch!”

He took his vorpal sword in hand;
      Long time the manxome foe he sought—
So rested he by the Tumtum tree
      And stood awhile in thought.

And, as in uffish thought he stood,
      The Jabberwock, with eyes of flame,
Came whiffling through the tulgey wood,
      And burbled as it came!

One, two! One, two! And through and through
      The vorpal blade went snicker-snack!
He left it dead, and with its head
      He went galumphing back.

“And hast thou slain the Jabberwock?
      Come to my arms, my beamish boy!
O frabjous day! Callooh! Callay!”
      He chortled in his joy.

’Twas brillig, and the slithy toves
      Did gyre and gimble in the wabe:
All mimsy were the borogoves,
      And the mome raths outgrabe.
EOF
fi

if [ ! -r iv_output.map ]; then
    echo "Generating iv_output.map..."
    cat > iv_output.map <<EOF
twas	1
brillig	1
and	1
the	1
slithy	1
toves	1
did	2
gyre	2
and	2
gimble	2
in	2
the	2
wabe	2
all	3
mimsy	3
were	3
the	3
borogoves	3
and	4
the	4
mome	4
raths	4
outgrabe	4
beware	6
the	6
jabberwock	6
my	6
son	6
the	7
jaws	7
that	7
bite	7
the	7
claws	7
that	7
catch	7
beware	8
the	8
jubjub	8
bird	8
and	8
shun	8
the	9
frumious	9
bandersnatch	9
he	11
took	11
his	11
vorpal	11
sword	11
in	11
hand	11
long	12
time	12
the	12
manxome	12
foe	12
he	12
sought	12
so	13
rested	13
he	13
by	13
the	13
tumtum	13
tree	13
and	14
stood	14
awhile	14
in	14
thought	14
and	16
as	16
in	16
uffish	16
thought	16
he	16
stood	16
the	17
jabberwock	17
with	17
eyes	17
of	17
flame	17
came	18
whiffling	18
through	18
the	18
tulgey	18
wood	18
and	19
burbled	19
as	19
it	19
came	19
one	21
two	21
one	21
two	21
and	21
through	21
and	21
through	21
the	22
vorpal	22
blade	22
went	22
snicker-snack	22
he	23
left	23
it	23
dead	23
and	23
with	23
its	23
head	23
he	24
went	24
galumphing	24
back	24
and	26
hast	26
thou	26
slain	26
the	26
jabberwock	26
come	27
to	27
my	27
arms	27
my	27
beamish	27
boy	27
o	28
frabjous	28
day	28
callooh	28
callay	28
he	29
chortled	29
in	29
his	29
joy	29
twas	31
brillig	31
and	31
the	31
slithy	31
toves	31
did	32
gyre	32
and	32
gimble	32
in	32
the	32
wabe	32
all	33
mimsy	33
were	33
the	33
borogoves	33
and	34
the	34
mome	34
raths	34
outgrabe	34
EOF
fi

if [ ! -r iv_output.reduce ]; then
    echo "Generating iv_output.reduce..."
    cat > iv_output.reduce <<EOF
all	3 33
and	1 2 4 8 14 16 19 21 23 26 31 32 34
arms	27
as	16 19
awhile	14
back	24
bandersnatch	9
beamish	27
beware	6 8
bird	8
bite	7
blade	22
borogoves	3 33
boy	27
brillig	1 31
burbled	19
by	13
callay	28
callooh	28
came	18 19
catch	7
chortled	29
claws	7
come	27
day	28
dead	23
did	2 32
eyes	17
flame	17
foe	12
frabjous	28
frumious	9
galumphing	24
gimble	2 32
gyre	2 32
hand	11
hast	26
he	11 12 13 16 23 24 29
head	23
his	11 29
in	2 11 14 16 29 32
it	19 23
its	23
jabberwock	6 17 26
jaws	7
joy	29
jubjub	8
left	23
long	12
manxome	12
mimsy	3 33
mome	4 34
my	6 27
o	28
of	17
one	21
outgrabe	4 34
raths	4 34
rested	13
shun	8
slain	26
slithy	1 31
snicker-snack	22
so	13
son	6
sought	12
stood	14 16
sword	11
that	7
the	1 2 3 4 6 7 8 9 12 13 17 18 22 26 31 32 33 34
thou	26
thought	14 16
through	18 21
time	12
to	27
took	11
toves	1 31
tree	13
tulgey	18
tumtum	13
twas	1 31
two	21
uffish	16
vorpal	11 22
wabe	2 32
went	22 24
were	3 33
whiffling	18
with	17 23
wood	18
EOF
fi

if [ ! -x iv_map.py ]; then
    echo "iv_map.py is not executable!"
    FAILURES=$((FAILURES + 1))
fi

if [ ! -x iv_reduce.py ]; then
    echo "iv_reduce.py is not executable!"
    FAILURES=$((FAILURES + 1))
fi

if ! head -n 1 iv_map.py | grep -q python2.7; then
    echo "iv_map.py is does not have python2.7 in she-bang!"
    FAILURES=$((FAILURES + 1))
fi

if ! head -n 1 iv_reduce.py | grep -q python2.7; then
    echo "iv_reduce.py is does not have python2.7 in she-bang!"
    FAILURES=$((FAILURES + 1))
fi

if ! ./iv_map.py < iv_input.txt | diff -q - iv_output.map ; then
    echo "iv_map.py failed"
    FAILURES=$((FAILURES + 1))
fi

if ! ./iv_map.py < iv_input.txt | diff -q - iv_output.map ; then
    echo "iv_map.py failed"
    FAILURES=$((FAILURES + 1))
fi

if ! ./iv_reduce.py < iv_output.map | sort | diff -q - iv_output.reduce; then
    echo "iv_reduce.py failed"
    FAILURES=$((FAILURES + 1))
fi

if ! ./iv_map.py < iv_input.txt | sort | ./iv_reduce.py | diff -q - iv_output.reduce; then
    echo "iv_map.py | sort | iv_reduce.py failed"
    FAILURES=$((FAILURES + 1))
fi

if [ $FAILURES -eq 0 ]; then
    echo "iv tests successful"
    exit 0
else
    echo "iv tests $FAILURES failures"
    exit 1
fi
