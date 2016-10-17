// C++ standard library includes
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

// CAF includes
#include "caf/all.hpp"
#include "caf/io/all.hpp"

// Boost includes
CAF_PUSH_WARNINGS
#include <boost/multiprecision/cpp_int.hpp>
CAF_POP_WARNINGS

// Own includes
#include "is_probable_prime.hpp"
#include "int512_serialization.hpp"

using std::cout;
using std::cerr;
using std::endl;
using std::vector;
using std::string;
using std::unordered_map;

using boost::multiprecision::int512_t;

using namespace caf;

namespace {

struct config : actor_system_config {
  string host = "localhost";
  uint16_t port = 0;
  size_t num_workers = 0;
  string mode;
  config() {
    add_message_type<int512_t>("int512_t");
    add_message_type<vector<int512_t>>("vector<int512_t>");
    opt_group{custom_options_, "global"}
    .add(host, "host,H", "server host (ignored in server mode)")
    .add(port, "port,p", "port")
    .add(num_workers, "num-workers,w", "number of workers (in manager mode)")
    .add(mode, "mode,m", "one of 'server', 'manager' or 'client'");
  }
};

void run_server(actor_system& sys, const config& cfg) {
  cout << "run_server: implement me" << endl;
}

void run_manager(actor_system& sys, const config& cfg) {
  cout << "run_manager: implement me" << endl;
}

void run_client(actor_system& sys, const config& cfg) {
  cout << "run_client: implement me" << endl;
}

// dispatches to run_* function depending on selected mode
void caf_main(actor_system &sys, const config &cfg) {
  using map_t = unordered_map<string, void (*)(actor_system &, const config &)>;
  map_t modes{
      {"server", run_server},
      {"manager", run_manager},
      {"client", run_client}
  };
  auto i = modes.find(cfg.mode);
  if (i != modes.end())
    (i->second)(sys, cfg);
  else
    cerr << "*** invalid mode specified" << endl;
}

} // namespace <anonymous>

CAF_MAIN(io::middleman)
