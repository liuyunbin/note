{
    arr["a"] = "a"
    arr["b"] = "b"
    arr["c"] = "c"
    arr["d"] = "d"
    arr["e"] = "e"

    printf "\n before: \n"
    for (i in arr) {
        print i, " => ", arr[i]
    }

    asort(arr, b)
    printf "\n after: \n"

    for (i in arr) {
        print i, " => ", arr[i]
    }

    for (i in b) {
        print i, " => ", arr[i]
    }
}
