int sum_to(int n) {
    int acc = 0;
    for (int i = 0; i <= n; i++) {
        acc += i;
    }
    return acc;
}

int main(int argc, char const *argv[])
{
    sum_to(5);
    return 0;
}
