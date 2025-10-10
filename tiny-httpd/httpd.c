/****************************/
/*                          */
/*     原作者：J. David     */
/*     修改人：刘云宾       */
/*                          */
/****************************/
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ctype.h>
#include <strings.h>
#include <string.h>
#include <sys/stat.h>
#include <pthread.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdbool.h>

#define SERVER_STRING "Server: Tinyhttpd/0.1.0\r\n"
#define MAX_STRING_LENGTH 1024

void* accept_request(void*);
void bad_request(int);
void cannot_execute(int);
void error_die(const char *);
void execute_cgi(int, const char *, const char *, const char *);
int  get_line_from_sock(int, char *, int);
void headers(int);
void not_found(int);
void serve_file(int, const char *);
int  get_server_socket(u_short *);
void unimplemented(int);

/***************************************/
/*                                     */
/*      线程函数，处理与客户端的交互   */
/*                                     */
/***************************************/
void* accept_request(void* client_sock) {
    int     client = *(int*)client_sock;
    char    buf[MAX_STRING_LENGTH];     /**********************/
    char    *method;                    /* 请求方法           */
    char    *url;                       /* 请求资源           */
    char    path[MAX_STRING_LENGTH];    /* 请求资源实际路径   */
    size_t  i;                          /**********************/
    struct  stat st;
    int     cgi = 0;                    /* becomes true if server decides this is a CGI program */
    char    *query_string = NULL;

    free(client_sock);
    pthread_detach(pthread_self());     /* 将线程设置为游离态  */

    get_line_from_sock(client, buf, sizeof(buf));

    method = buf;
    for (i = 0; !isspace(buf[i]) && buf[i] != '\0'; ++i)
        ;
    buf[i++] = '\0';
    /* 请求资源未实现  */
    if (strcasecmp(method, "GET") && strcasecmp(method, "POST")) {
        unimplemented(client);
        return NULL;
    }

    while (isspace(buf[i]) && buf[i] != '\0')
        ++i;
    url = buf + i;
    while (!isspace(buf[i]) && buf[i] != '\0')
        ++i;
    buf[i] = '\0';

    if (strcasecmp(method, "GET") == 0) {
        query_string = url;
        while (*query_string != '?' && *query_string != '\0')
            ++query_string;
        if (*query_string == '?') {
            cgi = 1;
            *query_string = '\0';
            ++query_string;
        }
    }

    snprintf(path, sizeof(path), "htdocs%s", url);
    if (path[strlen(path) - 1] == '/')
        strcat(path, "index.html");
    /* 请求资源未找到  */
    if (stat(path, &st) == -1) {
        while (get_line_from_sock(client, buf, sizeof(buf)) > 0 && strcmp("\n", buf))  /* read & discard headers */
            ;
        not_found(client);
    }
    else {
        /* 查看文件是否有可执行权限  */
        if ((st.st_mode&S_IXUSR) || (st.st_mode&S_IXGRP) || (st.st_mode&S_IXOTH))
            cgi = 1;
        if (!cgi)
            serve_file(client, path); /* 发送静态页面  */
        else
            execute_cgi(client, path, method, query_string); /* 执行 cgi 脚本  */
    }

    close(client);
    return NULL;
}

/**************************************/
/*                                    */
/*        请求报文格式错误            */
/*                                    */
/***************************×**********/
void bad_request(int client) {
     char buf[MAX_STRING_LENGTH];

     snprintf(buf, sizeof(buf), "HTTP/1.0 400 BAD REQUEST\r\n");
     send(client, buf, sizeof(buf), 0);
     snprintf(buf, sizeof(buf), "Content-type: text/html\r\n");
     send(client, buf, sizeof(buf), 0);
     snprintf(buf, sizeof(buf), "\r\n");
     send(client, buf, sizeof(buf), 0);
     snprintf(buf, sizeof(buf), "<P>Your browser sent a bad request, ");
     send(client, buf, sizeof(buf), 0);
     snprintf(buf, sizeof(buf), "such as a POST without a Content-Length.\r\n");
     send(client, buf, sizeof(buf), 0);
}

/***************************************/
/*                                     */
/*              服务器错误             */
/*                                     */
/***************************************/
void cannot_execute(int client) {
    char buf[MAX_STRING_LENGTH];

    snprintf(buf, sizeof(buf), "HTTP/1.0 500 Internal Server Error\r\n");
    send(client, buf, strlen(buf), 0);
    snprintf(buf, sizeof(buf), "Content-type: text/html\r\n");
    send(client, buf, strlen(buf), 0);
    snprintf(buf, sizeof(buf), "\r\n");
    send(client, buf, strlen(buf), 0);
    snprintf(buf, sizeof(buf), "<P>Error prohibited CGI execution.\r\n");
    send(client, buf, strlen(buf), 0);
}

void error_die(const char *sc) {
    perror(sc);
    exit(1);
}

/******************************************/
/*                                        */
/*               执行 cgi 脚本            */
/*                                        */
/******************************************/
void execute_cgi(int client, const char *path, const char *method, const char *query_string) {
    char buf[MAX_STRING_LENGTH];
    int child_to_parent[2]; /* 子进程向父进程发送信息的管道  */
    int parent_to_child[2]; /* 父进程向子进程发送信息的管道  */
    pid_t pid;
    int i;
    char c;
    int content_length = -1;

    if (strcasecmp(method, "GET") == 0) {
        while (get_line_from_sock(client, buf, sizeof(buf)) > 0 && strcmp("\n", buf) != 0)
            ;
    }
    else {
        while (get_line_from_sock(client, buf, sizeof(buf)) > 0 && strcmp("\n", buf)) {
            buf[15] = '\0';
            if (strcasecmp(buf, "Content-Length:") == 0)
                content_length = atoi(buf + 16);
        }
        if (content_length == -1) {
            bad_request(client);
            return ;
        }
    }

    /* 发送状态行   */
    snprintf(buf, sizeof(buf), "HTTP/1.0 200 OK\r\n");
    send(client, buf, strlen(buf), 0);


    if (pipe(child_to_parent) < 0 || pipe(parent_to_child) < 0 || (pid=fork()) < 0) {
        cannot_execute(client);
        return ;
    }
    if (pid == 0)  {
        char meth_env[MAX_STRING_LENGTH];          /*************************************************/
        char query_env[MAX_STRING_LENGTH];         /*                                               */
        char length_env[MAX_STRING_LENGTH];        /*               子进程                          */
                                                   /*                                               */   
        dup2(child_to_parent[1], 1);               /* 将标准输出重定向到管道 child_to_parent 的输入 */
        dup2(parent_to_child[0], 0);               /* 将标准输入重定向到管道 parent_to_child 的输出 */
        close(child_to_parent[0]);                 /* 关闭管道 child_to_parent 的输出               */
        close(parent_to_child[1]);                 /* 关闭管道 parent_to_child 的输入               */
                                                   /*                                               */
                                                   /*************************************************/

        /* 设置环境变量，供 perl 脚本使用  */
        snprintf(meth_env, sizeof(meth_env), "REQUEST_METHOD=%s", method);
        putenv(meth_env);
        if (strcasecmp(method, "GET") == 0) {
            snprintf(query_env, sizeof(query_env), "QUERY_STRING=%s", query_string);
            putenv(query_env);
        }
        else {
            snprintf(length_env, sizeof(length_env), "CONTENT_LENGTH=%d", content_length);
            putenv(length_env);
        }
        execl(path, query_string, NULL);
        exit(0);
    } 
    else {    
        close(child_to_parent[1]);                /* 关闭管道 child_to parent 的输出 */
        close(parent_to_child[0]);                /* 关闭管道 parent_to_child 的输入 */
        if (strcasecmp(method, "POST") == 0)
            for (i = 0; i < content_length; i++) {
                recv(client, &c, 1, 0);
                write(parent_to_child[1], &c, 1);
            }
            while (read(child_to_parent[0], &c, 1) > 0)
                send(client, &c, 1, 0);

            close(child_to_parent[0]);
            close(parent_to_child[1]);
            waitpid(pid, NULL, 0);
    }
}

/******************************************************/
/*                                                    */
/* 从指定套接字读取一行字符，将 \r\n 或 \r 换成 \n    */
/*                                                    */
/******************************************************/
int get_line_from_sock(int sock, char *buf, int size) {
    int i = 0;
    char c;

    while (i < size - 1 && recv(sock, &c, 1, 0) > 0 && c != '\n' && c != '\r')
        buf[i++] = c;
    /* MSG_PEEK 表示数据并未从缓存中删除,下一次读取的还是该字符 */
    if (c == '\r' && recv(sock, &c, 1, MSG_PEEK) > 0 && c == '\n')
        recv(sock, &c, 1, 0);
    if (c == '\n')
        buf[i++] = c;
    buf[i] = '\0';
 
    return i;
}

/****************************************************************/
/*                                                              */
/*             发送状态行，响应头部和空行                       */
/*                                                              */
/****************************************************************/
void headers(int client) {
    char buf[MAX_STRING_LENGTH];

    snprintf(buf, sizeof(buf), "HTTP/1.0 200 OK\r\n");
    send(client, buf, strlen(buf), 0);
    snprintf(buf, sizeof(buf), SERVER_STRING);
    send(client, buf, strlen(buf), 0);
    snprintf(buf, sizeof(buf), "Content-Type: text/html\r\n");
    send(client, buf, strlen(buf), 0);
    snprintf(buf, sizeof(buf), "\r\n");
    send(client, buf, strlen(buf), 0);
}

/*******************************/
/*                             */
/*  请求资源未找到 404 错误    */
/*                             */
/*******************************/
void not_found(int client) {
    char buf[MAX_STRING_LENGTH];

    snprintf(buf, sizeof(buf), "HTTP/1.0 404 NOT FOUND\r\n");
    send(client, buf, strlen(buf), 0);
    snprintf(buf, sizeof(buf), SERVER_STRING);
    send(client, buf, strlen(buf), 0);
    snprintf(buf, sizeof(buf), "Content-Type: text/html\r\n");
    send(client, buf, strlen(buf), 0);
    snprintf(buf, sizeof(buf), "\r\n");
    send(client, buf, strlen(buf), 0);
    snprintf(buf, sizeof(buf), "<HTML><TITLE>Not Found</TITLE>\r\n");
    send(client, buf, strlen(buf), 0);
    snprintf(buf, sizeof(buf), "<BODY><P>The server could not fulfill\r\n");
    send(client, buf, strlen(buf), 0);
    snprintf(buf, sizeof(buf), "your request because the resource specified\r\n");
    send(client, buf, strlen(buf), 0);
    snprintf(buf, sizeof(buf), "is unavailable or nonexistent.\r\n");
    send(client, buf, strlen(buf), 0);
    snprintf(buf, sizeof(buf), "</BODY></HTML>\r\n");
    send(client, buf, strlen(buf), 0);
}

/*************************************/
/*                                   */ 
/*    向客户端传送文件               */
/*                                   */
/*************************************/
void serve_file(int client_sock, const char *filename) {
    FILE *resource;
    char buf[MAX_STRING_LENGTH];

    /* 读取并忽略请求头部  */
    while (get_line_from_sock(client_sock, buf, sizeof(buf)) > 0 && strcmp("\n", buf))
        ;

    resource = fopen(filename, "r");
    if (resource == NULL) {
        not_found(client_sock);
        return ;
    }
    headers(client_sock);
    
    while (fgets(buf, sizeof(buf), resource) != NULL)
        send(client_sock, buf, strlen(buf), 0);
    fclose(resource);
}

/************************************************/
/*                                              */
/* 返回监听套接字，参数为指向端口号的指针       */
/*                                              */
/************************************************/
int get_server_socket(u_short *server_port) {
    int server_httpd;
    struct sockaddr_in server_name;

    server_httpd = socket(PF_INET, SOCK_STREAM, 0);
    if (server_httpd == -1)
        error_die("socket");
    memset(&server_name, 0, sizeof(server_name));
    server_name.sin_family = AF_INET;
    server_name.sin_port = htons(*server_port);
    server_name.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(server_httpd, (struct sockaddr *)&server_name, sizeof(server_name)) < 0)
        error_die("bind");
    if (*server_port == 0) {
        /* int namelen = sizeof(name); */
        socklen_t server_name_len = sizeof(server_name);
        if (getsockname(server_httpd, (struct sockaddr *)&server_name, &server_name_len) == -1)
            error_die("getsockname");
        *server_port = ntohs(server_name.sin_port);
    }
    if (listen(server_httpd, 5) < 0)
        error_die("listen");
    return server_httpd;
}

/************************************/
/*                                  */
/*  客户端所请求的方法并未实现      */
/*                                  */
/************************************/
void unimplemented(int client) {
    char buf[MAX_STRING_LENGTH];

    snprintf(buf, sizeof(buf), "HTTP/1.0 501 Method Not Implemented\r\n");
    send(client, buf, strlen(buf), 0);
    snprintf(buf, sizeof(buf), SERVER_STRING);
    send(client, buf, strlen(buf), 0);
    snprintf(buf, sizeof(buf), "Content-Type: text/html\r\n");
    send(client, buf, strlen(buf), 0);
    snprintf(buf, sizeof(buf), "\r\n");
    send(client, buf, strlen(buf), 0);
    snprintf(buf, sizeof(buf), "<HTML><HEAD><TITLE>Method Not Implemented\r\n");
    send(client, buf, strlen(buf), 0);
    snprintf(buf, sizeof(buf), "</TITLE></HEAD>\r\n");
    send(client, buf, strlen(buf), 0);
    snprintf(buf, sizeof(buf), "<BODY><P>HTTP request method not supported.\r\n");
    send(client, buf, strlen(buf), 0);
    snprintf(buf, sizeof(buf), "</BODY></HTML>\r\n");
    send(client, buf, strlen(buf), 0);
}

int main(void) {
    int         server_sock;
    u_short     server_port = 0;
    int         *client_sock;
    pthread_t   newthread;

    server_sock = get_server_socket(&server_port);
    printf("httpd running on port %d\n", server_port);

    while (true) {
        /* 为避免多线程竞争问题，使用动态分配内存，在线程函数中释放  */
        client_sock = (int*)malloc(sizeof(int));
        if (client_sock == NULL)
            error_die("malloc");
        *client_sock = accept(server_sock, NULL, NULL);
        if (*client_sock == -1)
            error_die("accept");
        if (pthread_create(&newthread, NULL, accept_request, client_sock) != 0)
            perror("pthread_create");
    }

    close(server_sock);

    return 0;
}

