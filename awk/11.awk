{
    cmd = "date +\"%Y-%m-%d %H:%M:%S %z\""
    cmd | getline time
    close(cmd)
    printf("时间为: %s\n", time)
}
