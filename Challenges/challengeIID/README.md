Challenge IID: Morphing Words

A word morph is a transformation from one word X to another word Y such that X and Y are words in the dictionary, and X can be transformed to Y by adding, deleting, or changing one letter. For instance, the transformations from dig to dog and from dog to dig are both word morphs.
A word morph sequence is a lexicographically ordered sequence of words w1, w2, ..., wn such that the transformation from wi to wi+1 is a word morph for all i from 1 to n - 1.
For a given dictionary, you are to compute the longest word morph sequence and output the length of the sequence and the words in the sequence.

Input:            Output:
cat                5
dig                dig
dog                fig
fig                fin
fin                fine
fine               wine
fog
log
wine

