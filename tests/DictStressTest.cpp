
#include "../Dictionary.hpp"
#include <chrono>
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <thread>

char* randomstring(unsigned int amt) {
	char* rv = new char[amt+1];
	for (unsigned int i=0; i<amt; i++) {
		rv[i] = (rand() % (0x7E - 0x20)) + 0x20;
	}
	rv[amt] = 0;
	return rv;
}

int main() {
	Dictionary<char*> the_big_one;

	time_t start = time(nullptr);

	for (size_t i=0; i<1024*1024; i++) {
		the_big_one.append(randomstring(16), randomstring(10));
	}

	time_t end = time(nullptr);
	printf("Took %llu seconds to add 1024*1024 random key:value pairs\n", end-start);

	printf("Sleeping for 5 seconds...\n");
	std::this_thread::sleep_for(std::chrono::seconds(5));

	return 0;
}


