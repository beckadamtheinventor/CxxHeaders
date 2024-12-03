
#include "../Array2D.hpp"
#include "../Dictionary.hpp"
#include "../Registry.hpp"
#include <chrono>
#include <cstdlib>
#include <thread>


struct RegisteredValue {
	int values[4];
};

int main() {
	Array2D<int> mat(100, 100);
	for (size_t y=0; y<mat.height(); y++) {
		for (size_t x=0; x<mat.width(); x++) {
			mat[{x, y}] = x*y;
		}
	}
	for (size_t i=0; i<8; i++) {
		size_t x = rand() % mat.width();
		size_t y = rand() % mat.height();
		printf("Value at %llu,%llu = %d\n", x, y, mat[{x, y}]);
	}

	Dictionary<const char*> dict;
	dict["Hello"] = "World";
	dict["Foo"] = "Bar";
	dict["Bar"] = "Foo";
	dict["Funny Joke"] = "Among us is sus haha";
	dict["Funny Joke"] = "<redacted>";
	for (size_t i=0; i<dict.length(); i++) {
		printf("(%llu) %s = %s\n", i, dict.keys(i), dict.values(i));
	}

	Registry<RegisteredValue> reg;
	RegisteredValue* val = reg.create("default:empty");
	val->values[0] = 12345;
	val->values[1] = 6789;
	val->values[2] = 1011;
	val->values[3] = 12;
	reg.add("default:A", new RegisteredValue{0});
	reg.add("something:B", new RegisteredValue{1});
	reg.add("another:C", new RegisteredValue{2});
	reg.add("namespace:D", new RegisteredValue{3});
	reg.create("just a string");
	for (size_t i=0; i<reg.length(); i++) {
		RegisteredValue* v = reg.get(i);
		printf("(%llu) %s = %d %d %d %d\n", i, reg.keys(i), v->values[0], v->values[1], v->values[2], v->values[3]);
	}

	printf("Sleeping for 5 seconds...\n");
	std::this_thread::sleep_for(std::chrono::seconds(5));

	return 0;
}


