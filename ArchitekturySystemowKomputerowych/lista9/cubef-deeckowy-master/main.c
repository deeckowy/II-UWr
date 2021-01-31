#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdnoreturn.h>
#include <string.h>
#include <sys/time.h>

#define __noinline __attribute__((noinline))
#define DBL(x) ((double)*((float *)&(x)))

#define MASK_EXP 0x7F800000
#define SIGN 0x80000000
 
static bool infinity_p(uint32_t val) {
  return (val & MASK_EXP) == MASK_EXP;
}

static bool denormalized_p(uint32_t val) {
  return (val | SIGN) != SIGN && (val & MASK_EXP) == 0;
}

extern uint32_t cubef(uint32_t);

/* https://en.wikipedia.org/wiki/Xorshift#xorshift* */
static uint64_t random_u64(uint64_t *seed) {
  uint64_t x = *seed;
  x ^= x >> 12;
  x ^= x << 25;
  x ^= x >> 27;
  *seed = x;
  return x * 0x2545F4914F6CDD1DUL;
}

/* Only for testing. Such solution would get -100 points. */
static __noinline uint32_t cubef_illegal(uint32_t x) {
  float y = *(float *)&x;
  long double d = y;
  d = d * d * d;
  y = d;
  return *(uint32_t *)&y;
}

typedef union caller_regs {
  struct {
    uint64_t rbx;
    uint64_t r12;
    uint64_t r13;
    uint64_t r14;
    uint64_t r15;
    uint64_t rbp;
  };
  uint64_t reg[6];
} caller_regs_t;

#define save_caller_regs(regs)                                                 \
  asm volatile("mov %%rbx,  0(%0);"                                            \
               "mov %%r12,  8(%0);"                                            \
               "mov %%r13, 16(%0);"                                            \
               "mov %%r14, 24(%0);"                                            \
               "mov %%r15, 32(%0);"                                            \
               "mov %%rbp, 40(%0);"                                            \
               : /* no outputs */                                              \
               : "r"(regs)                                                     \
               : "memory", "rbx", "r12", "r13", "r14", "r15", "rbp")

static void run(uint32_t arg) {
  uint32_t user, correct;

  caller_regs_t before, after;
  save_caller_regs(&before);
  user = cubef(arg);
  save_caller_regs(&after);

  for (int i = 0; i < sizeof(caller_regs_t) / sizeof(uint64_t); i++) {
    if (before.reg[i] != after.reg[i]) {
      printf("cubef(...) does not adhere to ABI calling convention!\n");
      exit(EXIT_FAILURE);
    }
  }

  correct = cubef_illegal(arg);
  if (user != correct) {
    printf("cubef(%e [0x%08X]) = %e [0x%08X] (your answer: %e [0x%08X])\n",
           DBL(arg), arg, DBL(correct), correct, DBL(user), user);
    exit(EXIT_FAILURE);
  }
}

int main(int argc, char *argv[]) {
  if (argc == 2) {
    uint64_t arg = strtoul(argv[1], NULL, 16);
    if (errno)
      goto fail;
    run(arg);
    return EXIT_SUCCESS;
  }

  if (argc == 3) {
    if (strcmp("-r", argv[1]))
      goto fail;

    int times = strtol(argv[2], NULL, 10);
    if (times < 0)
      goto fail;

    struct timeval tv;
    gettimeofday(&tv, NULL);

    uint64_t seed = tv.tv_sec + tv.tv_usec * 1e6;

    for (int i = 0; i < times; i++) {
      uint32_t val, res;
      do {
        do {
          val = random_u64(&seed);
          if (random_u64(&seed) & 7)
            val &= 0xffff8000;
        } while (infinity_p(val));
        res = cubef_illegal(val);
      } while (denormalized_p(res));
      run(val);
    }

    return EXIT_SUCCESS;
  }

fail:
  fprintf(stderr, "Usage: %s [-r TIMES] [NUMBER]\n", argv[0]);
  return EXIT_FAILURE;
}
