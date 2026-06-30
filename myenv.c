/*
 *  myenv.c : env コマンドのクローン
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#ifdef __linux__
#include "myputenv.h"
#endif
extern char **environ;

void myPrintenv() {
  for (int i=0; environ[i]!=NULL; i++) {
    printf("%s\n", environ[i]);
  }
}

int main(int argc, char *argv[]) {
  if (argc==1) {
    myPrintenv();
  } else {
    int j=1;
    while ((putenv(argv[j]))!=-1) {
      j++;
    }
    if (argv[j]==NULL) {
      myPrintenv();
    } else {
      execvp(argv[j], &argv[j]);
      perror(argv[j]);
      return 1;
    }
  }
  return 0;
}

/* 実行例
----- コンパイル -----
% make                  
cc -D_GNU_SOURCE -Wall -std=c99 -o myenv myenv.c myputenv.c

----- 実行例1 -----
% ./myenv
TERM_PROGRAM=Apple_Terminal
SHELL=/bin/zsh
TERM=xterm-256color
TMPDIR=/var/folders/f_/66ldd5wj31nb3_61jtvbk6lr0000gn/T/
TERM_PROGRAM_VERSION=464
TERM_SESSION_ID=9503D378-15A3-4202-A4F0-1FED93151352
USER=hiroaki
SSH_AUTH_SOCK=/private/tmp/com.apple.launchd.y7bEHo59XW/Listeners
PATH=/opt/homebrew/opt/openjdk/bin:/opt/homebrew/bin:/opt/homebrew/sbin:/Library/Frameworks
/Python.framework/Versions/3.13/bin:/usr/local/bin:/System/Cryptexes/App/usr/bin:/usr/bin:/bin:
/usr/sbin:/sbin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/local/bin:/var/run
/com.apple.security.cryptexd/codex.system/bootstrap/usr/bin:/var/run/com.apple.security.cryptexd
/codex.system/bootstrap/usr/appleinternal/bin
__CFBundleIdentifier=com.apple.Terminal
PWD=/Users/hiroaki/Documents/システムプログラミング2/SysPro/kadai09-i23kanda
XPC_FLAGS=0x0
XPC_SERVICE_NAME=0
SHLVL=1
HOME=/Users/hiroaki
LOGNAME=hiroaki
OSLogRateLimit=64
COLORTERM=truecolor
OLDPWD=/Users/hiroaki/Documents/システムプログラミング2/SysPro
HOMEBREW_PREFIX=/opt/homebrew
HOMEBREW_CELLAR=/opt/homebrew/Cellar
HOMEBREW_REPOSITORY=/opt/homebrew
FPATH=/opt/homebrew/share/zsh/site-functions:/usr/local/share/zsh/site-functions:/usr/share/zsh/site-functions:
/usr/share/zsh/5.9/functions
INFOPATH=/opt/homebrew/share/info:
CPPFLAGS=-I/opt/homebrew/opt/openjdk/include
LANG=ja_JP.UTF-8
_=/Users/hiroaki/Documents/シスャ??ャ??ャ??ゃ?ャ?クゃ?ャ?ャ??ャ?クゃ?2/SysPro/kadai09-i23kanda/./myenv

-----　　実行例2 -----
% ./myenv LC_TIME=C TZ=Cuba
TERM_PROGRAM=Apple_Terminal
SHELL=/bin/zsh
TERM=xterm-256color
TMPDIR=/var/folders/f_/66ldd5wj31nb3_61jtvbk6lr0000gn/T/
TERM_PROGRAM_VERSION=464
TERM_SESSION_ID=9503D378-15A3-4202-A4F0-1FED93151352
USER=hiroaki
SSH_AUTH_SOCK=/private/tmp/com.apple.launchd.y7bEHo59XW/Listeners
PATH=/opt/homebrew/opt/openjdk/bin:/opt/homebrew/bin:/opt/homebrew/sbin:/Library/Frameworks
/Python.framework/Versions/3.13/bin:/usr/local/bin:/System/Cryptexes/App/usr/bin:/usr/bin:/bin:
/usr/sbin:/sbin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/local/bin:/var
/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/bin:/var/run/com.apple.security.cryptexd
/codex.system/bootstrap/usr/appleinternal/bin
__CFBundleIdentifier=com.apple.Terminal
PWD=/Users/hiroaki/Documents/システムプログラミング2/SysPro/kadai09-i23kanda
XPC_FLAGS=0x0
XPC_SERVICE_NAME=0
SHLVL=1
HOME=/Users/hiroaki
LOGNAME=hiroaki
OSLogRateLimit=64
COLORTERM=truecolor
OLDPWD=/Users/hiroaki/Documents/システムプログラミング2/SysPro
HOMEBREW_PREFIX=/opt/homebrew
HOMEBREW_CELLAR=/opt/homebrew/Cellar
HOMEBREW_REPOSITORY=/opt/homebrew
FPATH=/opt/homebrew/share/zsh/site-functions:/usr/local/share/zsh/site-functions:/usr/share/zsh
/site-functions:/usr/share/zsh/5.9/functions
INFOPATH=/opt/homebrew/share/info:
CPPFLAGS=-I/opt/homebrew/opt/openjdk/include
LANG=ja_JP.UTF-8
_=/Users/hiroaki/Documents/シスャ??ャ??ャ??ゃ?ャ?クゃ?ャ?ャ??ャ?クゃ?2/SysPro/kadai09-i23kanda/./myenv
LC_TIME=C
TZ=Cuba

----- 実行例3 -----
% date
2026年 6月30日 火曜日 14時56分36秒 JST
% ./myenv LC_TIME=C TZ=Cuba date
Tue Jun 30 01:57:18 CDT 2026
% date
2026年 6月30日 火曜日 15時04分52秒 JST

----- 実行例4 -----
% ./myenv A=B printenv A
B

----- 実行例5 -----
 % ./myenv LANG=ru_RU.UTF-8 ls -l
total 384
-rw-r--r--  1 hiroaki  staff     132 30 июня  10:34 Makefile
-rwxr-xr-x  1 hiroaki  staff   33784 30 июня  14:51 myenv
-rw-r--r--  1 hiroaki  staff    4003 30 июня  15:00 myenv.c
-rwxr-xr-x  1 hiroaki  staff     216 30 июня  10:34 myputenv.c
-rw-r--r--  1 hiroaki  staff      93 30 июня  10:34 myputenv.h
-rw-r--r--  1 hiroaki  staff    1268 30 июня  10:34 README.md
-rw-r--r--  1 hiroaki  staff  139098 30 июня  10:34 README.pdf
% ls -l
total 392
-rw-r--r--  1 hiroaki  staff     132  6月 30 10:34 Makefile
-rwxr-xr-x  1 hiroaki  staff   33784  6月 30 14:51 myenv
-rw-r--r--  1 hiroaki  staff    4527  6月 30 15:03 myenv.c
-rwxr-xr-x  1 hiroaki  staff     216  6月 30 10:34 myputenv.c
-rw-r--r--  1 hiroaki  staff      93  6月 30 10:34 myputenv.h
-rw-r--r--  1 hiroaki  staff    1268  6月 30 10:34 README.md
-rw-r--r--  1 hiroaki  staff  139098  6月 30 10:34 README.pdf
*/
