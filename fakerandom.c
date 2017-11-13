/*

  Copyright (c) 2017 Samuel Lidén Borell <samuel@kodafritt.se>

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.

*/

#include <fcntl.h>
#include <linux/random.h>
#include <sys/ioctl.h>
#include <stdio.h>

int main(int argc, const char **argv)
{
    int fd, res, ent;

    (void) argv;
    if (argc > 1) {
        printf("usage: fakerandom\n\n"
               "Increases the entropy counter, without actually adding any entropy.\n"
               "Obviously this is NOT secure. Do not use on production systems!\n\n");
        return 0;
    }

    fd = open("/dev/random", O_WRONLY);
    if (fd < 0) {
        perror("failed to open /dev/random");
        return 1;
    }

    ent = 0x1000000;
    res = ioctl(fd, RNDADDTOENTCNT, &ent);
    if (res < 0) {
        perror("failed to add fake entropy");
        return 1;
    }
    return 0;
}

