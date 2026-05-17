#include <iostream>
#include "../include/UserProfile.h"

using namespace std;

int main() {
    UserProfile user(
        "Alex",
        17,
        "Male",
        178,
        72,
        "Moderate",
        "Build muscle"
    );

    user.showProfile();

    return 0;
}