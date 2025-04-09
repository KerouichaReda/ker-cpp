#include <ker/serialization/data_codec.h>

struct data {
    std::uint8_t a{};
    std::uint8_t b{};
};

int main(int argc, char const* argv[]) {
    data d1{42, 69};

    data_codec ar;
    ar << d1;
    for (size_t i = 0, size = ar.size(); i < size; i++) {
        std::cout << std::int32_t(ar.data()[i]) << " ";
    }
    std::cout << std::endl;

    data d2;
    std::cout << std::int32_t(d2.a) << " " << std::int32_t(d2.b) << std::endl;
    ar >> d2;
    std::cout << std::int32_t(d2.a) << " " << std::int32_t(d2.b) << std::endl;
    return 0;
}