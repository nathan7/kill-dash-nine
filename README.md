# kill-dash-nine

  Ye olde `kill(3)` wrapped in a native node module.

  > KILL DASH NINE,
  >
  > No more CPU time.
  >
  > I run KILL DASH NINE,
  >
  > And your process is mine.
  >
  > I run KILL DASH NINE,
  >
  > 'Cause it's MY time to shine
  >
  > So don't step outta line or else it's
  >
  > KILL DASH NINE!
  >
  > — "Kill Dash Nine" by Monzy

## API

  `var kill = require('kill')`

### kill(pid, signal = 'SIGTERM')

  Kill the process with the given PID.

  Returns undefined.

  If the arguments are of the wrong types, an appropriate TypeError will be thrown.

  If `kill(3)` returns an error, an error annotated with `syscall`, `code`, `errno` and `pid` will be thrown.
  Commonly, it'll return the codes `EPERM` (permission denied) and `ESRCH` (no such process).
