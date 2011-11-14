#ifndef PRIVILEGE_H
#define PRIVILEGE_H

typedef enum privilege_t {
  // NOTE:
  //   - Values must be a power of 2 between 0x1 and 0x80000000 inclusive, since they will be used
  //     to form a bit set.
  //   - These values cannot change in the future because they will be encoded into the generated
  //     modules in order to identify their required privilege level now and in the future.
  pr_none    = 0x00000000,  // No privileges
  pr_unknown = 0x00000001,  // Unknown privileges
  pr_stapusr = 0x00000002,  // Member of stapusr
  pr_stapsys = 0x00000004,  // Member of stapsys
  pr_stapdev = 0x00000008,  // Member of stapdev
  // These are used for iterating
  pr_begin = pr_stapusr,
  pr_end   = pr_unknown,
  // Predefined sets
  pr_all = pr_stapusr | pr_stapsys | pr_stapdev
} privilege_t;

// Privilege management.
privilege_t pr_next (privilege_t p);
const char *pr_name (privilege_t p);
int pr_contains (privilege_t actual, privilege_t required);
#if defined(c_plusplus) || defined(__cplusplus)
extern "C" {
#endif
privilege_t get_privilege_credentials (void);
#if defined(c_plusplus) || defined(__cplusplus)
}
#endif

#endif // PRIVILEGE_H
