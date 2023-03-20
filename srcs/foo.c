#include <unistd.h>
int main() {
    char buff[16];
    for (int i = 0; i < 3; ++i) {
        read(0, buff, sizeof(buff));
    }
    return 0;
}