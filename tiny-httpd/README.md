## 问题
### 2017-09-15
* 发现：同一服务器，在本机的 chrome 浏览器中，只能测试两次，第三次会失败，在手机上则正常
* 测试环境：ubuntu 16.04  chrome 60.0.3112.113 64 位

## 修改日志
### 2017-10-23
1. change `#!/usr/bin/perl` to `#!/usr/bin/env perl`

### 2017-09-14
1. 去掉 `httpd.c` 中的魔法数字
2. 将 `httpd.c` 线程设置为游离态

### 2017-09-01
1. 在 `httpd.c` 添加注释，修改部分结构

### 2017-08-30
#### 修改以便在 ubuntu 下运行
1. 将 `README.md` 改为 `README.md`
1. 修改 `httpd.c` 代码风格，使用TAB(四个空格)进行缩进--------吐槽一下源代码使用一个空格进行缩进
2. 去掉 `Makefile` 里的 `-lsocket`, 将 `-lpthread` 改为 `-pthread`
3. 将 `htdocs` 中的 `check.cgi` 和 `color.cgi` 中的 `perl` 路径改为: `/usr/bin/perl`
4. 添加 `color.cgi` 的可执行权限，`chmod +x color.cgi`
#### 修改源码，去除了编译的警告
1. 将函数 `int startup(u_short *port)` 中的 `int namelen = sizeof(name);` 改为 `socklen_t namelen = sizeof(name);`
2. 将函数 `int main(void)` 中的 `int client_name_len = sizeof(client_name);` 改为 `socklen_t client_name_len = sizeof(client_name);`
3. 将函数声明 `void accept_request(int);` 改为 `void* accept_request(void*);`
4. 将函数定义 `void accept_request(int client)` 改为 `void* accept_request(void* client_sock)`
5. 在函数 `void* accept_request(void* client_sock)` 中添加定义 `int client = *(int*)client_sock;`
6. 在函数 `void* accept_request(void* client_sock)` 中添加返回值 `return NULL;`
7. 将函数 `void* accept_request(void* client_sock)` 中的 `return ;`  改为 `return NULL;`
8. 将函数 `int main(void)` 中的 `if (pthread_create(&newthread , NULL, accept_request, client_sock) != 0)` 改为`if (pthread_create(&newthread , NULL, accept_request, (void*)(&client_sock)) != 0)`
                    

## 原项目 README
This software is copyright 1999 by J. David Blackstone.  Permission
is granted to redistribute and modify this software under the terms of
the GNU General Public License, available at http://www.gnu.org/ .

  If you use this software or examine the code, I would appreciate
knowing and would be overjoyed to hear about it at
jdavidb@sourceforge.net .

  This software is not production quality.  It comes with no warranty
of any kind, not even an implied warranty of fitness for a particular
purpose.  I am not responsible for the damage that will likely result
if you use this software on your computer system.

  I wrote this webserver for an assignment in my networking class in
1999.  We were told that at a bare minimum the server had to serve
pages, and told that we would get extra credit for doing "extras."
Perl had introduced me to a whole lot of UNIX functionality (I learned
sockets and fork from Perl!), and O'Reilly's lion book on UNIX system
calls plus O'Reilly's books on CGI and writing web clients in Perl got
me thinking and I realized I could make my webserver support CGI with
little trouble.

  Now, if you're a member of the Apache core group, you might not be
impressed.  But my professor was blown over.  Try the color.cgi sample
script and type in "chartreuse."  Made me seem smarter than I am, at
any rate. :)

  Apache it's not.  But I do hope that this program is a good
educational tool for those interested in http/socket programming, as
well as UNIX system calls.  (There's some textbook uses of pipes,
environment variables, forks, and so on.)

  One last thing: if you look at my webserver or (are you out of
mind?!?) use it, I would just be overjoyed to hear about it.  Please
email me.  I probably won't really be releasing major updates, but if
I help you learn something, I'd love to know!

  Happy hacking!

                                   J. David Blackstone
