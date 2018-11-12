#include <stdio.h>
#include <stdlib.h>

#define N_MAX 200000

#define min(X,Y) (X<Y)?X:Y

int namea[N_MAX], nameb[N_MAX];
double ta[N_MAX], ua[N_MAX], tb[N_MAX], ub[N_MAX];
int main() {


    int N, L, K;
    // read important input numbers
    scanf("%d", &N);
    scanf("%d", &L);
    scanf("%d", &K);

    // read time, velocity of i-est a particle
    int i = 0;
    for (i = 0; i < N; i++) {
        scanf("%lf", &ta[i]);
        scanf("%lf", &ua[i]);
        namea[i] = i+1;
    }

    // read time, velocity of i-est b particle
    for (i = 0; i < N; i++) {
        scanf("%lf", &tb[i]);
        scanf("%lf", &ub[i]);
        nameb[i] = i+1;
    }

    //initiate collided particles
    int ia = 0, ib = 0;
    // repeat for K iterations
    int k;
    for (k = 0; k < K; k++) {

        // find first, ignore whichever leaves bounds withought interacting
        double low, high, mid;
        while (ia < N && ib < N) {
            if (ta[ia] <= tb[ib]) {
                // if a reaches L distance after b appears
                if (L/ua[ia] + ta[ia] >= tb[ib]) {
                    // Lower bound: time in which b appears
                    low = tb[ib];
                    break;
                } else {
                    ia++;
                }
            } else {
                // if b reaches L distance after a appears
                if (L/ub[ib] + tb[ib] >= ta[ia]) {
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

        //begin binary search
        int maxa, maxb;
        double dist_maxa, dist_maxb;
        //search till high and low moments are 10^-9s away
        while (high - low > 0.000000001) {
            mid = low + (high - low) / 2.0;

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

        // Search for final maxes in high time :P
        // inside binary search we don't find the final ones,
        // we just use them to find the lowest high
        maxa = ia;
        for (i = ia; i < N; i++) {
            // if i-est traveled further than max, replace
            if (ua[maxa]*(high - ta[maxa]) < ua[i]*(high - ta[i])) {
                maxa = i;
            }
        }

        maxb = ib;
        // find b that traveled max distance in mid time
        for (i = ib; i < N; i++) {
            // if i-est traveled further than max, replace
            if (ub[maxb]*(high - tb[maxb]) < ub[i]*(high - tb[i])) {
                maxb = i;
            }
        }

        // print maxa, maxb
        printf("%d %d\n", namea[maxa], nameb[maxb]);

        // delete maxa, maxb from arrays
        for (i = maxa; i < N-1; i++) {
            ta[i] = ta[i+1];
            ua[i] = ua[i+1];
            namea[i] = namea[i+1];
        }

        for (i = maxb; i < N-1; i++) {
            tb[i] = tb[i+1];
            ub[i] = ub[i+1];
            nameb[i] = nameb[i+1];
        }

        // decrease N
        N--;
    }
    return 0;
}
