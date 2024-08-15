
#include "../SimpleConfig.hpp"
using namespace SimpleConfig;

int main(int argc, char** argv) {
    Config cfg;
    cfg.setString("foo", "bar");
    cfg.setBool("true", true);
    cfg.setUnsigned("TheAnswer", 42);
    cfg.setUnsigned("Runs", 1);
    cfg.setFloat("Position.x", 0.0f);
    cfg.setFloat("Position.y", 1.0f);
    cfg.setFloat("Position.z", 0.0);
    cfg.deserialize("configtest.dat");

    cfg.setUnsigned("Runs", cfg.getUnsigned("Runs")+1);

    cfg.serialize("configtest.dat");
    return 0;
}
