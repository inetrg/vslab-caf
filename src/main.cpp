#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/miller_rabin.hpp>

#include "caf/all.hpp"
#include "caf/io/all.hpp"

using std::cout;
using std::endl;
using std::vector;
using std::string;

using boost::multiprecision::int512_t;
using boost::multiprecision::miller_rabin_test;

using namespace caf;

inline bool is_probable_prime(const int512_t& value) {
  // increase 25 to a higher value for higher accuracy
  return miller_rabin_test(value, 25);
}

void run_server(long port) {
  cout << "run_server: implement me" << endl;
}

void run_manager(long workers, const string& host, long port) {
  cout << "run_manager: implement me" << endl;
}
void run_client(const string& host, long port) {
  cout << "run_client: implement me" << endl;
}

// projection: string => long
optional<long> long_arg(const string& arg) {
  char* last = nullptr;
  auto res = strtol(arg.c_str(), &last, 10);
  if (last == (arg.c_str() + arg.size())) {
    return res;
  }
  return none;
}

// tell CAF how to serialize int512_t
class int512_t_uti : public caf::detail::abstract_uniform_type_info<int512_t> {
 protected:
  void serialize(const void* vptr, caf::serializer* sink) const override {
    std::ostringstream oss;
    oss << *reinterpret_cast<const int512_t*>(vptr);
    sink->write(oss.str());
  }
  void deserialize(void* vptr, caf::deserializer* source) const override {
    std::istringstream iss{source->read<string>()};
    iss >> *reinterpret_cast<int512_t*>(vptr);
  }
};


int main(int argc, char** argv) {
  // allow int512_t and vector<int512_t> to be used in messages
  announce(typeid(int512_t), uniform_type_info_ptr{new int512_t_uti});
  announce<vector<int512_t>>();
  // parse command line arguments
  message_builder{argv + 1, argv + argc}.apply({
    on("-s", long_arg) >> run_server,
    on("-m", long_arg, val<string>, long_arg) >> run_manager,
    on("-c", val<string>, long_arg) >> run_client,
    others() >> [] {
      cout << "usage:" << endl
           << "  server:  -s <PORT>" << endl
           << "  manager: -m <NUM_WORKERS> <SERVER_HOST> <SERVER_PORT>" << endl
           << "  client:  -c <SERVER_HOST> <SERVER_PORT>" << endl
           << endl;
    }
  });
  await_all_actors_done();
  shutdown();
}
