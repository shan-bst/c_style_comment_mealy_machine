#include <stdio.h>

// Mealy machine over {s, b, *, /} -- marks where a C-style comment begins and ends.
// States : q0 = outside a comment
//          q1 = outside, just read '/'
//          q2 = inside a comment
//          q3 = inside a comment, just read '*'
// Output : 1 on the move that begins a comment (the '*' after an opening '/')
//              and on the move that ends it    (the '/' after a closing '*')
//          0 on every other move
// There is no trap state: every state has a move for every symbol.


int main() {
    char input[100], output[100];
    int state = 0, i, col;

    /* columns: 0 = s, 1 = b, 2 = *, 3 = / */
    int delta[4][4] = {
        {0, 0, 0, 1},   /* q0 */
        {0, 0, 2, 1},   /* q1 */
        {2, 2, 3, 2},   /* q2 */
        {2, 2, 3, 0}    /* q3 */
    };
    char lambda[4][4] = {
        {'0', '0', '0', '0'},   /* q0 */
        {'0', '0', '1', '0'},   /* q1 */
        {'0', '0', '0', '0'},   /* q2 */
        {'0', '0', '0', '1'}    /* q3 */
    };

    printf("Enter a string (over s, b, *, /): ");
    scanf("%99s", input);

    for (i = 0; input[i] != '\0'; i++) {
        char c = input[i];
        if (c == 's') col = 0;
        else if (c == 'b') col = 1;
        else if (c == '*') col = 2;
        else if (c == '/') col = 3;
        else {
            printf("INVALID SYMBOL '%c' (alphabet is {s, b, *, /})\n", c);
            return 1;
        }
        output[i] = lambda[state][col];
        printf("d(q%d,%c) = q%d   lambda(q%d,%c) = %c\n",
               state, c, delta[state][col], state, c, output[i]);
        state = delta[state][col];
    }
    output[i] = '\0';

    printf("Output string : %s\n", output);
    printf("Final state   : q%d\n", state);
    return 0;
}
