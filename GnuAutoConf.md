> # Introduction #
  * Autoconf is a tool for producing shell scripts that automatically configure software source code packages to adapt to many kinds of Posix-like systems.
  * The configuration scripts produced by Autoconf require no manual user intervention when run; they do not normally even need an argument specifying the system type.
  * The configuration scripts consists of a set of check macros.
  * Before each check, they print a one-line message stating what they are checking for, so the user doesn't get too bored while waiting for the script to finish. After the check they record the result.


> # Results of Tests #
Configure will record the results once it has determined whether a feature exists or not. It would do that
  * DefiningC Preprocessor Symbols:
  * Setting Output Variables: Replacing the value of the shell/environment variables used in output files
  * Special Chars in Variables:
  * Caching Results: Used by the following macros to speed up the process.
  * Printing Messages: Notifying the user.

> # Reference #

[GNU AutoConf](http://www.gnu.org/software/autoconf/manual/html_node/index.html#Top)