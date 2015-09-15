'use strict'
exports = module.exports = kill
var native = require('bindings')('binding.node')

var errors = {
  EPERM: 'Permission denied',
  ESRCH: 'No such process'
}

var codes = {}
for (var key in native.errnos) {
  codes[-native.errnos[key]] = key
}

function kill (pid, signal) {
  if (typeof pid !== 'number' || (pid | 0) !== pid) {
    throw new TypeError('pid must be an integer')
  }

  if (typeof signal !== 'string' && signal !== undefined) {
    throw new TypeError('signal must be a string')
  }

  var signum = signal === undefined
    ? native.signals.SIGTERM
    : native.signals[signal]

  if (typeof signum !== 'number') {
    throw new TypeError('unknown signal ' + signal)
  }

  var errno = native.kill(pid, signum)
  if (errno !== 0) {
    var code = codes[errno]
    var err = new Error(errors[code] || 'Unknown error')
    err.syscall = 'kill'
    err.code = code
    err.errno = errno
    err.pid = pid
    throw err
  }
}
