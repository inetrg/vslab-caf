// C++ standard library includes
#include <algorithm>
#include <cstdio>
#include <ctime>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

// CAF includes
#include "caf/all.hpp"
#include "caf/io/all.hpp"

// Boost includes
CAF_PUSH_WARNINGS
#ifdef CAF_CLANG
#pragma clang diagnostic ignored "-Wdeprecated-copy"
#elif defined(CAF_GCC)
#pragma GCC diagnostic ignored "-Wdeprecated-copy"
#endif
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random.hpp>
CAF_POP_WARNINGS

// Own includes
#include "int512_serialization.hpp"
#include "is_probable_prime.hpp"

using std::cerr;
using std::cout;
using std::endl;
using std::string;
using std::unordered_map;
using std::vector;

using boost::multiprecision::gcd;
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
      .add(num_workers, "num-workers,w", "number of workers (in worker mode)")
      .add(mode, "mode,m", "one of 'server', 'worker' or 'client'");
  }
};

// -- SERVER -------------------------------------------------------------------

void run_server(actor_system& sys, const config& cfg) {
  if (auto port = sys.middleman().publish_local_groups(cfg.port))
    cout << "published local groups at port " << *port << '\n';
  else
    cerr << "error: " << sys.render(port.error()) << '\n';
  cout << "press any key to exit" << std::endl;
  getc(stdin);
}

// -- CLIENT -------------------------------------------------------------------

// Client state, keep track of factors, time, etc.
struct client_state {
  // The joined group.
  group grp;
};

behavior client(stateful_actor<client_state>* self, caf::group grp) {
  // Join group and save it to send messages later.
  self->join(grp);
  self->state.grp = grp;
  // TODO: Implement me.
  return {};
}

void run_client(actor_system& sys, const config& cfg) {
  if (auto eg = sys.middleman().remote_group("vslab", cfg.host, cfg.port)) {
    auto grp = *eg;
    sys.spawn(client, grp);
  } else {
    cerr << "error: " << sys.render(eg.error()) << '\n';
  }
}

// -- WORKER -------------------------------------------------------------------

// State specific to each worker.
struct worker_state {
  // The joined group.
  group grp;
};

behavior worker(stateful_actor<worker_state>* self, caf::group grp) {
  // Join group and save it to send messages later.
  self->join(grp);
  self->state.grp = grp;
  // TODO: Implement me.
  // - Calculate rho.
  // - Check for new messages in between.
  return {};
}

void run_worker(actor_system& sys, const config& cfg) {
  if (auto eg = sys.middleman().remote_group("vslab", cfg.host, cfg.port)) {
    auto grp = *eg;
    // TODO: Spawn workers, e.g:
    // sys.spawn(worker, grp);
  } else {
    cerr << "error: " << sys.render(eg.error()) << '\n';
  }
  sys.await_all_actors_done();
}

// -- MAIN ---------------------------------------------------------------------

// dispatches to run_* function depending on selected mode
void caf_main(actor_system& sys, const config& cfg) {
  using map_t = unordered_map<string, void (*)(actor_system&, const config&)>;
  map_t modes{
    {"server", run_server},
    {"worker", run_worker},
    {"client", run_client},
  };
  auto i = modes.find(cfg.mode);
  if (i != modes.end())
    (i->second)(sys, cfg);
  else
    cerr << "*** invalid mode specified" << endl;
}

} // namespace

CAF_MAIN(io::middleman)
