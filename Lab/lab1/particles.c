#include <stdio.h>
#include <stdlib.h>

// Better input parsing than simple scanf(), taken from courses' moodle
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

// read important input numbers
N = scanf();
L = scanf();
K = scanf();

// read time, velocity of i-est a particle
int i = 0;
for (i = 0; i < N; i++) {
    ta[i] = scanf();
    ua[i] = scanf();
}

// read time, velocity of i-est b particle
for (i = 0; i < N; i++) {
    tb[i] = scanf();
    ub[i] = scanf();
}

// Όταν το πρώτο δεν συγκρούεται με κανένα, απλά συνεχίζω
// Όταν έχω σύγκρουση όμως, κάνω επανεκκίνηση, αφαιρώντας τα 2
// που συμμετείχαν στην σύγκρουση

// find first, ignore whichever leaves bounds withought interacting
while (ia < N && ib < N) {
    if (ta[ia] <= tb[ib]) {
        // if a reaches L distance after b appears
        if (L/ua[ia] + ta[ia] < tb[ib]) {
            // Lower bound: time in which b appears
            low = tb[ib];
            break;
        } else {
            ia++;
        }
    } else {
        // if b reaches L distance after a appears
        if (L/ub[ib] + tb[ib] < ta[ia]) {
            // Lower bound: time in which a appears
            low = ta[ia];
            break;
        }
        else {
            ib++;
        }
    }
}

/* Binary Search @time to find colliding pairs*/
// Upper bound: min time in which one of two travels L distance,
high = min(L/ua[ia] + ta[ia], L/ub[ib] + tb[ib]);
// initial mid:

//
while (low <= high) {
    mid = low + (high - low) / 2;

    // find a that traveled max distance in mid time
    maxa = ia;
    for (i = ia; i < N; i++) {
        // if i-est traveled further than max, replace
        if (ua[maxa]*(mid - ta[maxa]) < ua[i]*(mid - ta[i])) {
            maxa = i;
        }
    }

    // find b that traveled max distance in mid time
    maxb = ib;
    for (i = ib; i < N; i++) {
        // if i-est traveled further than max, replace
        if (ub[maxb]*(mid - tb[maxb]) < ub[i]*(mid - tb[i])) {
            maxb = i;
        }
    }

    // calculate max dists
    dist_maxa = ua[maxa]*(mid - ta[maxa]);
    dist_maxb = ub[maxb]*(mid - tb[maxb]);

    if (dist_maxa + dist_maxb < L) {
        low = mid;
    } else {
        high = mid;
    }
}

// print maxa, maxb
printf("%d %d\n", maxa, maxb);

// delete maxa, maxb from arrays
for (i = maxa; i < N; i++) {
    ta[i] = ta[i+1];
    ua[i] = ua[i+1];
}

for (i = maxb; i < N; i++) {
    tb[i] = tb[i+1];
    ba[i] = ub[i+1];
}

// decrease N
N--;
