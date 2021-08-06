# Shared Mutexes

Shared Mutexes protect critical sections that should be accessed by only one process at a time.

If a user spawns two processes that take the same shared mutex, one of the two will wait until such mutex times out, or the alternate process releases it.
