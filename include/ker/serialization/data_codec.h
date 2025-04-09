#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <algorithm>
#include <numeric>

namespace ker {
namespace serialization {
class data_codec {
   public:
    template <typename T>
    data_codec& operator<<(const T& value) {
        const std::uint8_t* bytes = reinterpret_cast<const std::uint8_t*>(&value);
        buffer_.insert(buffer_.end(), bytes, bytes + sizeof(T));
        return *this;
    }

    template <typename T>
    data_codec& operator>>(T& value) {
        std::memcpy(&value, buffer_.data() + pos_, sizeof(T));
        pos_ += sizeof(T);
        return *this;
    }
    const std::uint8_t* data() const { return buffer_.data(); }
    std::size_t size() const { return buffer_.size(); }

   private:
    std::vector<std::uint8_t> buffer_;
    std::size_t pos_{0};

    /* data */
};
}
}