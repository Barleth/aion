![Logo](https://i.imgur.com/JrzhmnV.png)

# aion
A simple C application vulnerable to buffer overflow attacks. For the sake of reality, this application simulates a simple network host management tool.

_This was created for didactic purpose in a **virtualized environment**, is strongly recommended to do so._

## Compiling with GCC
Most GCC compilers apply necessary protections by default. We need to explicitly compile it without stack protector (`-fno-stack-protector`).
We also need to pass to the linker (`-z`) the `execstack` option to mark the application as requiring executable stack.

Makefile is provided:
```
$ make
```
Or you can compile it manually

```
$ gcc -fno-stack-protector -z execstack aion.c -o aion
```

## Setup the environment
This application was made for a machine which has a directory with sudoers permissions for all scripts.
So we got `ALL ALL=(ALL) NOPASSWD: /home` in `/etc/sudoers`

Obviously our binary needs to be owned by the root, so:
```
$ sudo chown root:root aion
```

## Vulnerabilities
The vulnerability relies over the usage of `gets()` deprecated function and its inability to know how many character will read.
Without any input sanitization, it allows to a malicious user to perform a BO attack through a particular vulnerable point.

The 'not-so-good developer' who wrote this made `gets()` his piece de resistance, even if the compiler is screaming to him not to do this through a passive-aggressive warning.

### Exploiting
The exploiting point coincides with the only section where user input is required (Option 3 - Change IP address).

_E.g._
Interface: `eth0 [MALICIOUS CODE CONCATENATION]`

Such as `&& sudo su`

Password: `[EXCESSIVELY LONG STRING]`

Such as `Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.`

## License
```
MIT License

Copyright (c) 2020 Barleth

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

```
