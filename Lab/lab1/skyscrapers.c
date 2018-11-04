#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define N_MAX 1000000

// better input parsing than simple scanf(), taken from courses' moodle 
#define BSIZE 1<<15
char buffer[BSIZE];
long bpos = 0L, bsize = 0L;
long long readlong()
{
        long long d = 0L, x = 0L;
        char c;

        while (1)  {
                if (bpos >= bsize) {
                        bpos = 0;
                        if (feof(stdin)) return x;
                        bsize = fread(buffer, 1, BSIZE, stdin);
                }
                c = buffer[bpos++];
                if (c >= '0' && c <= '9') { x = x*10 + (c-'0'); d = 1; }
                else if (d == 1) return x;
        }
        return -1;
}

// A structure to represent a stack, with stuff from the slightly dark web
struct Stack
{
    int top;
    unsigned capacity;
    int* array;
};

// function to create a stack of given capacity. It initializes size of
// stack as 0
struct Stack* createStack(unsigned capacity)
{
    struct Stack* stack = (struct Stack*) malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*) malloc(stack->capacity * sizeof(int));
    return stack;
}

// Stack is full when top is equal to the last index
int isFull(struct Stack* stack)
{   return stack->top == stack->capacity - 1; }

// Stack is empty when top is equal to -1
int isEmpty(struct Stack* stack)
{   return stack->top == -1;  }

// Empties stack I DID THIS
void reset(struct Stack* stack)
{   stack->top = -1;}

// Function to add an item to stack.  It increases top by 1
void push(struct Stack* stack, int item)
{
    if (isFull(stack))
        return;
    stack->array[++stack->top] = item;
}

// Function to remove an item from stack.  It decreases top by 1
int pop(struct Stack* stack)
{
    if (isEmpty(stack))
        return INT_MIN;
    return stack->array[stack->top--];
}

// Function to peek the top item. I made this myself
int peek(struct Stack* stack)
{
    if (isEmpty(stack))
        return INT_MIN;
    return stack->array[stack->top];
}

// init arrays
long long Height[N_MAX], Left[N_MAX], Right[N_MAX],
    HL[N_MAX], HR[N_MAX];

int main() {

    // Read input & fill Heght
    int i, N;
    N = (int) readlong();
    for (i = 0; i < N; i++) {
        Height[i] = readlong();
    }

    // Create Stack
    struct Stack* mystack = createStack(N);
    // Fill HL
    for (i = 0; i < N; i++) {
        // O(2n), in - out 1 time at most
        while (!isEmpty(mystack) && Height[i] > Height[peek(mystack)]) {
            pop(mystack);
        }
        if (!isEmpty(mystack)) HL[i] = peek(mystack); else HL[i] = -1;
        push(mystack, i);
    }

    // Emptied stack for reuse, as array HL is ready.
    reset(mystack);
    // Fill HR.
    for (i = N-1; i >= 0; i--) {
        // O(2n), in - out 1 time at most
        while (!isEmpty(mystack) && Height[i] > Height[peek(mystack)]) {
            pop(mystack);
        }
        if (!isEmpty(mystack)) HR[i] = peek(mystack); else HR[i] = -1;
        push(mystack, i);
    }

    // Parse from left
    for (i = 0; i < N; i++) {
        // No higher from left
        if (HL[i] == -1) {
            Left[i] = (i+1)*Height[i];
        } else {
            Left[i] = Left[HL[i]] + (i-HL[i]) * Height[i];
        }
    }

    // Parse from right
    for (i = N-1; i >= 0; i--) {
        // No higher from right
        if (HR[i] == -1) {
            Right[i] = (N-i) * Height[i];
        } else {
            Right[i] = Right[HR[i]] + (HR[i]-i) * Height[i];
        }
    }

    // Calculate total cost & find min
    long long min = Left[0] + Right[0] - Height[0];
    for (i = 1; i < N; i++) {
        long long cost = Left[i] + Right[i] - Height[i];
        if (cost < min) min = cost;
    }

    //print min
    printf("%lld", min);
    return 0;
}
